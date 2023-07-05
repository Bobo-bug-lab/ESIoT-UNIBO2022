#include "Pir.h"
#include "Timer.h"
#include <stdio.h>

Pir::Pir(){

} 
  
void Pir::updateSyncTime(long time){
	lastTimeSync = time;
}

long Pir::getLastSyncTime(){
	return lastTimeSync;
}

void Pir::sync(){

  (void)printf("Fake Pir test Running\r\n");
  updateSyncTime(millis());
}
