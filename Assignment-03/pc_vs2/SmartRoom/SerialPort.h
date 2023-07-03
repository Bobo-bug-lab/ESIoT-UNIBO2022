#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include "Timer.h"
#include "parson.h"
#include "LightTask.h"

class SerialPort {
public:
    SerialPort(const char* connectionString);
    ~SerialPort();
    virtual void sync();
    long getLastSyncTime();
    

protected:
    void updateSyncTime(long time);

private:
    HANDLE hSerial;
    bool Read(char* buffer, DWORD bufferSize, DWORD& bytesRead);
    bool Write(ControlMode mode, bool led, int roller);
    // bool Write(char mode, char msg);
};

struct FromArduinoData {
    bool phoneMode = 0;
    bool lightArduino = 0;
    int rollerArduino = 0;
};

