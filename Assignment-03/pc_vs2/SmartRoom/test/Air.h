#ifndef __AIR__
#define __AIR__

class Air {
 
public:
  Air();
  void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;

};

#endif
