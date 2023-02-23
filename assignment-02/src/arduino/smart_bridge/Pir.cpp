#include "Pir.h"

Pir::Pir(){

} 
  
void Pir::updateSyncTime(long time){
	lastTimeSync = time;
}

long Pir::getLastSyncTime(){
	return lastTimeSync;
}
