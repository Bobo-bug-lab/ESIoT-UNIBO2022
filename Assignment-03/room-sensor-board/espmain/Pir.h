#ifndef __PIR__
#define __PIR__


class Pir {
 
public: 
  Pir(int pin);
  bool getPir();

private:
  int pin;
  bool detected;
};

#endif
