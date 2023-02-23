#ifndef __LIGHTDETCTOR__
#define __LIGHTDETCTOR__

class LightDetector {
 
public:
  LightDetector();
  virtual double light_detect();
  virtual void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;

};

#endif
