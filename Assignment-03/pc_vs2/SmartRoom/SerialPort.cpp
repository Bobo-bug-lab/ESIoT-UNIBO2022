#include "SerialPort.h"
#include "Timer.h"

struct FromPhoneData fromPhoneData;

    SerialPort::SerialPort(const char* portName)
    {
        // enable SerialPort
        hSerial = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hSerial == INVALID_HANDLE_VALUE)
        {
            std::cerr << "failed to enable SerialPort\n";
            return;
        }

        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        if (!GetCommState(hSerial, &dcbSerialParams))
        {
            std::cerr << "unable to read SerialParams\n";
            CloseHandle(hSerial);
            return;
        }
        dcbSerialParams.BaudRate = CBR_9600; // BaudRate
        dcbSerialParams.ByteSize = 8; // ByteSize
        dcbSerialParams.StopBits = ONESTOPBIT; // StopBits
        dcbSerialParams.Parity = NOPARITY; // set Parity 校验位 = no

        if (!SetCommState(hSerial, &dcbSerialParams))
        {
            std::cerr << "unable to set SerialParam\n";
            CloseHandle(hSerial);
            return;
        }

        std::cout << "enable SerialPort successfully\n";
    }

    ~SerialPort::SerialPort()
    {
        // shut down SerialPort
        CloseHandle(hSerial);
    }

    bool SerialPort::Write(char modeChar, bool led, int roller)
    {
        
        char message=[];
        DWORD bytesWritten;
        if (!WriteFile(hSerial, message, strlen(message), &bytesWritten, NULL))
        {
            std::cerr << "unable to write SerialPort\n";
            return false;
        }

        std::cout << "write SerialPort successfully, message:"<< message <<std::endl;
        return true;
    }

    bool SerialPort::Read(char* buffer, DWORD bufferSize, DWORD& bytesRead)
    {
        if (!ReadFile(hSerial, buffer, bufferSize, &bytesRead, NULL))
        {
            std::cerr << "failed to read SerialPort\n";
            return false;
        }

        std::cout << "read SerialPort successfully\n";
        //setDataForLight();
        return true;
    }

    void SerialPort::updateSyncTime(long time) {
        lastTimeSync = time;
    }

    long SerialPort::getLastSyncTime() {
        return lastTimeSync;
    }

    

    // void SerialPort::setPhoneData(){
    //     dataforlight.dashboardSwitch = this->getDashboardSwitch();
    //     dataforlight.detectStatus = this->getDetectStatus();
    //     dataforlight.lightSwitchNode = this->getLightSwitchNode();
    //     dataforlight.lightValue = this->getLightValue();
    //     dataforlight.rollerSliderValueNode = this->getRollerSliderValueNode();
    // }

    // struct DataForLight getDataForLight(){
    //     return dataforlight;
    // }