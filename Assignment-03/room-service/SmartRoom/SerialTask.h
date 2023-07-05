#pragma once

#define SERIAL_PORT "\\\\.\\COM5"

#include <iostream>
#include "Task.h"
#include "serialib.h"
#include "Timer.h"
#include "globalSerial.h"

class SerialTask : public Task {

	Timer* timer;

public:

	SerialTask();
	void init(int period);
	void tick();
	void parseInputChar(const char* input);

private:
	char modechar;

};

bool getLightFromSerial();
bool getControlFromSerial();
int getRollerFromSerial();
