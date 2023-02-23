#ifndef __PIR__
#define __PIR__

class Pir {
 
public:
  Pir();
  virtual bool isDetected() = 0;

  virtual void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;

};

#endif
