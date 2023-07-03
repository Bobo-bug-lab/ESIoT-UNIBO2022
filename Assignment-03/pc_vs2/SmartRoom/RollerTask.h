#pragma once
#include <iostream>
#include "Task.h"
#include "Timer.h"
#include "Roller.h"
#include "LightTask.h"
#include "SerialPort.h"

class RollerTask : public Task {

	Roller* roller;
	Timer* timer;

public:

	RollerTask();
	void init(int period);
	void tick();

private:
	char modechar;


};
