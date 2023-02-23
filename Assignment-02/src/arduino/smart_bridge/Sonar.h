#ifndef __SONAR__
#define __SONAR__

class Sonar {
 
public:
  Sonar();

  virtual void sync();
  long getLastSyncTime();
  double getDistance();

protected: 
  void updateSyncTime(long time);
  double distance;

private:
  long lastTimeSync;


};

#endif
