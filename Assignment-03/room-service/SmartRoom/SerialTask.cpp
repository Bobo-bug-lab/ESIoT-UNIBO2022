#include "SerialTask.h"
using namespace std;

//DataForNode serialData = {0,0,0};

//std::mutex mtx;

bool lightSerial = 0;
bool phoneControl = 0;
int rollerSerial = 0;

SerialTask::SerialTask() {

}

void SerialTask::init(int period) {
    Task::init(period);
    //Serial.begin(115200);
    char errorOpening = globalSerial.openDevice(SERIAL_PORT, 9600);
    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening!=1) printf("Serial Port ERROR %s\n", SERIAL_PORT);
    else printf ("Successful connection to %s\n",SERIAL_PORT);
    
    
    timer = new Timer();

}

void SerialTask::tick() {

    char messageBody[10] = "\0";
    globalSerial.readString(messageBody, '\n', 20, 2000);
    printf("String read: %s\n", messageBody);
    this->parseInputChar(messageBody);


}

void SerialTask::parseInputChar(const char* input) {

    char mode = '\0';
    char inputType = '\0';
    int value = 0;
    int valueDigitCount = 0;
    bool parsingValue = false;

    // Iterate through the input character by character
    for (int i = 0; input[i] != '\0'; i++) {
        char currentChar = input[i];
        std::cout << "Current Char: " << currentChar << std::endl;
        // Check the current character to determine the parsing logic
        if (currentChar == 'S' || currentChar == 'D' || currentChar == 'A') {
            mode = currentChar;
        } else if (currentChar == 'L' || currentChar == 'R') {
            inputType = currentChar;
        } else if (std::isdigit(currentChar)) {
            if (!parsingValue) {
                parsingValue = true;
                value = currentChar - '0';
                valueDigitCount = 1;
            } 
            else {
                value = value * 10 + (currentChar - '0');
                valueDigitCount++;
            }
        } else{
            // Perform operations based on the extracted information
            if (mode == 'S') {
                phoneControl = 1;
            } 
            else {
                phoneControl = 0;
            }
            
            if (inputType == 'R'){
                rollerSerial = value;
            }
            else if(inputType == 'L'){
                lightSerial = value;
            }
            

            // Reset the variables
            mode = '\0';
            inputType = '\0';
            value = 0;
            valueDigitCount = 0;
            parsingValue = false;
        }
    }



}

bool getLightFromSerial(){
    return lightSerial;
}
bool getPhoneControlFromSerial(){
    return phoneControl;
}
int getRollerFromSerial(){
    return rollerSerial;
}
    

