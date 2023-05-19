#pragma once
#include <iostream>
#include "Task.h"
#include "Timer.h"
#include "getC2Dms.h"


class LightTask : public Task {

	IoTHubDevice* IoTDevice;
	//LightDetector* light_detector;
	Timer* timer;
	//bool manualControl;
	//enum { ON, OFF, SWITCHING_ON, SWITCHING_OFF } state;

private:

	// time when light turned on
	long time_when_light_turned_on;


public:

	LightTask();
	void init(int period);
	void tick();
	double threshold;

};