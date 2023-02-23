#include "LightDetector.h"

LightDetector::LightDetector(){
} 
  
void LightDetector::updateSyncTime(long time){
	lastTimeSync = time;
}

long LightDetector::getLastSyncTime(){
	return lastTimeSync;
}
