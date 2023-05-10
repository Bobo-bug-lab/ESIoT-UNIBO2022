#include "TestTask.h"
#include "Pir.h"
#include "Air.h"

#define MAX_TIME_LIGHT_ON 5000

TestTask::TestTask() {

}

void TestTask::init(int period) {
    //Serial.begin(9600);
    Task::init(period);
    pir = new Pir();
    air = new Air();
    timer = new Timer();
}

void TestTask::tick() {
    pir->sync();
    air->sync();
    
}
    

