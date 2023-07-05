#pragma once
#include <iostream>
#include "Task.h"
#include "Timer.h"
#include "getC2Dms.h"
#include "sendD2Cms.h"


class IotTask : public Task {

	IoTHubDevice* IoTDeviceReceive;
	IoTHubDeviceSend* IoTDeviceSend;
	Timer* timer;

public:

	IotTask();
	void init(int period);
	void tick();

};
