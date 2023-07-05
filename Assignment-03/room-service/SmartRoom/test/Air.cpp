#include "Air.h"
#include "Timer.h"
#include <stdio.h>

Air::Air(){

} 
  
void Air::updateSyncTime(long time){
	lastTimeSync = time;
}

long Air::getLastSyncTime(){
	return lastTimeSync;
}

void Air::sync(){

  (void)printf("Fake Air test Running\r\n");
  updateSyncTime(millis());
}
