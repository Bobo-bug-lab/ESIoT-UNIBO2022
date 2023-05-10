#ifndef __PIR__
#define __PIR__

class Pir {
 
public:
  Pir();
  void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;

};

#endif
