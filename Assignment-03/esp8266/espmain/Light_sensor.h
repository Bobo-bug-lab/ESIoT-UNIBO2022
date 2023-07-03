#ifndef __LIGHT_SENSOR__
#define __LIGHT_SENSOR__


class Light_sensor{ 
public:
  Light_sensor(int pin);
  double getLightLevel();    
private:
  int pin;  
};

#endif
