#include "Scheduler.h"
#include "SmartLightingTask.h"
#include "WaterLevelTask.h"

#define PIN_LED1 13
#define PIN_PIR 2
#define PIN_LIGHT_SENSOR A0

#define PIN_SONAR_TRIG 7
#define PIN_SONAR_ECHO 8
#define PIN_TEMP_SENSOR A1

#define BUTTON_PIN 4
#define PIN_LED2 9
#define PIN_LED3 10
#define PIN_POT A1
#define PIN_MOTOR 3
/* LCD Wiring: SDA => A4, SCL => A5 */


Scheduler sched;
Timer timer;

void setup(){

  Serial.begin(9600);
  sched.init(100);
 
  Task* t0 = new SmartLightingTask(PIN_LED1,PIN_PIR,PIN_LIGHT_SENSOR);
  t0->init(100);

  Task* t1 = new WaterLevelTask(PIN_SONAR_TRIG, PIN_SONAR_ECHO, PIN_TEMP_SENSOR, BUTTON_PIN, PIN_LED2, PIN_LED3, PIN_POT, PIN_MOTOR );
  t1->init(100);
  
  //sched.addTask(t0);
  sched.addTask(t1);

  timer.setupPeriod(50);
   
}

void loop(){
  timer.waitForNextTick();
  sched.schedule();
}
