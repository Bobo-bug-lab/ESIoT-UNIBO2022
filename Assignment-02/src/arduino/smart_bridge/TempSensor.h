#ifndef __TEMPSENSOR__
#define __TEMPSENSOR__

class TempSensor {
 
public:
  TempSensor();

  virtual void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;

};

#endif
