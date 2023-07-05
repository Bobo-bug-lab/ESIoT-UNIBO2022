#pragma once
#include "Task.h"
#include "Timer.h"
#include "GetC2Dms.h"

class SmartLightingTask : public Task {

	//int pin_led, pin_pir, pin_light_sensor;
	//Light* led;
	//Pir* pir;
	//LightDetector* light_detector;
	Timer* timer;
	bool manualControl;
	enum { ON, OFF, SWITCHING_ON, SWITCHING_OFF } state;

private:

	// time when light turned on
	long time_when_light_turned_on;


public:

	SmartLightingTask();
	void init(int period);
	void tick();
	double threshold;

};