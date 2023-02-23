#include "WaterLevelTask.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 
#include "servo_motor_impl.h"
#include "ButtonImpl.h"

/* Wiring: SDA => A4, SCL => A5 */
/* I2C address of the LCD: 0x27 */
/* Number of columns: 20 rows: 4 */
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 

bool flag;
int count = 0;

WaterLevelTask::WaterLevelTask(int pin_sonar_trigger, int pin_sonar_echo, int pin_temp, int pin_button, int pin_led_b, int pin_led_c, int pin_pot, int pin_servo){
  this->pin_sonar_trigger = pin_sonar_trigger;    
  this->pin_sonar_echo = pin_sonar_echo;
  this->pin_temp = pin_temp;
  this->pin_button = pin_button;
  this->pin_led_b = pin_led_b;
  this->pin_led_c = pin_led_c;
}
  
void WaterLevelTask::init(int period){
  Task::init(period);
  timer = new Timer();
  sonar = new SonarImpl(pin_sonar_trigger, pin_sonar_echo, pin_temp);
  button = new ButtonImpl(pin_button);
  led_green = new Led(pin_led_b);
  led_red = new Led(pin_led_c);
  pMotor = new ServoMotorImpl(3);
  lcd.init();
  lcd.backlight();
  state = SWITCHING_STATE;
  led_state = OFF;
  time_last_sample = 0;
  time_last_blinking = 0;
  flag = 1;
}
  
void WaterLevelTask::tick(){
  sonar->sync();
  button->sync();
  if(button->isPressed()) 
    {
    Serial.println("button pressed!");
    if(state == ALARM){
        state = MANUAL;
        // alpha = map(potenz->getValue() , 0, 1023, 0, 180);
        // Serial.println("Enabling manual mode......");
    }
    else if(state == MANUAL){
        state = ALARM;
        // alpha = sonar->getDistance()*100;
        // alpha = map(alpha, WATER_LEVEL_MAX, WATER_LEVEL_2*100, 0, 180);
        // alpha = 180 - alpha;
        Serial.println("Unenabling manual mode......");
    }
  }

  //led_red->sync();
  //double dist = sonar->getDistance();
  //Serial.println(dist);

  switch (state){
    
    case NORMAL:
      if(isOutOfLimits(SAMPLING_PERIOD_1, 0, WATER_LEVEL_1)){
        state = SWITCHING_STATE;
      }
      Serial.println("fuori normal");
      Serial.println(sonar->getDistance());
      
      char content[30];
      sprintf(content, "%d,%d,%d,%d,%d", state, (int)(sonar->getDistance()*1000),
      0,0,0);
      Serial.println(content);
      break;

    case PRE_ALARM:
    
      if(isOutOfLimits(SAMPLING_PERIOD_2, WATER_LEVEL_1, WATER_LEVEL_2)){
        state = SWITCHING_STATE;
      }

      //red led blinking with 2 seconds period     
      if(timer->check_time_since(time_last_blinking, PERIOD_LED_BLINKING)){
        time_last_sample = millis()/6;
        // if(count<10) count++;
        // else{
        switch (led_state){
            case OFF:
              led_red->switchOn();
              led_state = ON; 
              break;
            case ON:
              led_red->switchOff();
              led_state = OFF;
              break;  
        }
        // count=0;      
        //   }
      }

      //lcd part
      lcd.setCursor(1, 0);  // Set the cursor on the third column and first row.
      lcd.print("fuori pre_alarm! ");
      lcd.setCursor(1, 1);
      lcd.print("Dis: ");
      lcd.print(sonar->getDistance());
      //char content[30];
      sprintf(content, "%d,%d,%d,%d,%d", state, (int)(sonar->getDistance()*1000),
      0,0,0);
      Serial.println(content);
      //lcd.clear();

      Serial.println("fuori pre_alarm");
        Serial.println(sonar->getDistance());
      break;

    case ALARM:
      alpha = sonar->getDistance()*100;
      alpha = map(alpha, WATER_LEVEL_MAX, WATER_LEVEL_2*100, 0, 180);
      alpha = 180 - alpha;
      lcd.setCursor(1, 0);  
      lcd.print("fuori alarm! ");
      lcd.setCursor(1, 1);
      lcd.print("Dis: ");
      lcd.print(sonar->getDistance());
      lcd.clear();

      lcd.setCursor(1, 2);
      lcd.print("v_degrees: ");
      lcd.print(alpha);
      //lcd.clear();

      if(isOutOfLimits(SAMPLING_PERIOD_3, WATER_LEVEL_2, 0)){
        state = SWITCHING_STATE;
      }
 
      Serial.println("fuori alarm");
        Serial.println(sonar->getDistance());
      //char content[30];
      sprintf(content, "%d,%d,%d,%d,%d", state, (int)(sonar->getDistance()*1000),
      0,0,0);
      Serial.println(content);
      break;

      case MANUAL:   //MANUAL state
      alpha = map(potenz->getValue() , 0, 1023, 0, 180);
      lcd.setCursor(1, 0);  
      lcd.print("fuori alarm_man ");
      lcd.setCursor(1, 1);
      lcd.print("Dis: ");
      lcd.print(sonar->getDistance());
      lcd.clear();
      lcd.setCursor(1, 2);
      lcd.print("valve opening degrees: ");
      lcd.print(alpha);
      //lcd.clear();
      Serial.println("fuori alarm & manual mode running on");
      Serial.println(sonar->getDistance());
      //char content[30];
      sprintf(content, "%d,%d,%d,%d,%d", state, (int)(sonar->getDistance()*1000),
      0,0,0);
      Serial.println(content);
        if(alpha < 100){
        lcd.setCursor(17, 2);
        lcd.print(" ");
        if(alpha < 10){
          lcd.setCursor(16, 2);
          lcd.print(" ");
        }
      }
      flag = 0;
      break;

    case SWITCHING_STATE:   //is used to decide state
      //if(state == MANUAL) break;
      //lcd.clear();
      if(sonar->getDistance() > 3){
        state = NORMAL;
        led_green->switchOn();
        led_red->switchOff();
        flag = 1;
      }else if (sonar->getDistance() > 2){
        state = PRE_ALARM;
        led_green->switchOn();
        flag = 1;
      }else{
        state = ALARM;
        led_red->switchOn();
        led_green->switchOff();
        flag = 0;
      }
      
      break;

  }
}
  
//makes sample based on set period and checks if its out of bounds
bool WaterLevelTask::isOutOfLimits(long sampling_period, float upper_limit, float lower_limit){
  int isSet = 0;
  
  if(upper_limit != 0){
    isSet = 1;
  }
  switch (isSet)
  {
  case 0:

    if(timer->check_time_since(time_last_sample, sampling_period)){
      sonar->sync();
      time_last_sample = millis();
      if(sonar->getDistance() < lower_limit) {
        return true;
      }
    }
    return false;
    break;
  
  default:

    if(timer->check_time_since(time_last_sample, sampling_period)){
      sonar->sync();
      time_last_sample = millis();
      if(sonar->getDistance() < lower_limit || sonar->getDistance() > upper_limit) {
        return true;
      }
    }
    return false;

    break;
  }
}

  bool send_flag(){
    return flag;

  }

