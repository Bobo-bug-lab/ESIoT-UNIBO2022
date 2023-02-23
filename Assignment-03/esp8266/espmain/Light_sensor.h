#ifndef __LIGHT_SENSOR__
#define __LIGHT_SENSOR__


class Light_sensor{ 
public:
  Light_sensor(int pin);
  //void lightSensorSetup();
  int getLightLevel();    
private:
  int pin;  
};

#endif
