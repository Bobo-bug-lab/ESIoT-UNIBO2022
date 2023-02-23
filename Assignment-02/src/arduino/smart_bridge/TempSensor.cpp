#include "TempSensor.h"

TempSensor::TempSensor(){

} 
  
void TempSensor::updateSyncTime(long time){
	lastTimeSync = time;
}

long TempSensor::getLastSyncTime(){
	return lastTimeSync;
}
