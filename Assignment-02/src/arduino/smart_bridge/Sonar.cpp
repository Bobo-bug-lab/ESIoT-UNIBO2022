#include "Sonar.h"

Sonar::Sonar(){

} 
  
void Sonar::updateSyncTime(long time){
	lastTimeSync = time;
}

long Sonar::getLastSyncTime(){
	return lastTimeSync;
}

//gets distance
double Sonar::getDistance(){
  return distance;
}
