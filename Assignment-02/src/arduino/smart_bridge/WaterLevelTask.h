#ifndef __WATERLEVELTASK__
#define __WATERLEVELTASK__
#define SAMPLING_PERIOD_1 5000
#define SAMPLING_PERIOD_2 2000
#define SAMPLING_PERIOD_3 1000
#define PERIOD_LED_BLINKING 2000

#include "Task.h"
#include "Led.h"
#include "SonarImpl.h"
#include "Timer.h"
#include "Button.h"
#include "ButtonImpl.h"
#include "servo_motor_impl.h"
#include "PotImpl.h"

#define WATER_LEVEL_1 3
#define WATER_LEVEL_2 2
#define WATER_LEVEL_MAX 1

class WaterLevelTask: public Task {

  int pin_sonar_trigger;
  int pin_sonar_echo;
  int pin_temp;
  int pin_button;
  int pin_led_b;
  int pin_led_c;
  int state;
  int led_state;
  long time_last_sample;
  long time_last_blinking;
  int alpha; 
  ServoMotor* pMotor;
  SonarImpl* sonar;
  PotImpl* potenz;
  enum { NORMAL, PRE_ALARM, ALARM, SWITCHING_STATE, MANUAL } WL_state;
  enum { ON, OFF } LED_state;
  Timer* timer;
  Button* button;
  Light* led_green;
  Light* led_red;

public:

  WaterLevelTask(int pin_sonar_trigger, int pin_sonar_echo, int pin_temp, int pin_button, int pin_led_b, int pin_led_c, int pin_pot, int pin_servo);  
  void init(int period);  
  void tick();
  
private:

  bool isOutOfLimits(long sampling_period, float upper_limit, float lower_limit);

};

  bool send_flag();
  //bool receive_flag(bool flag);

#endif
