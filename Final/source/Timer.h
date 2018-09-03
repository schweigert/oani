#ifndef _TIMER_N_DEF_
#define _TIMER_N_DEF_

#include "Entity.h"

class Timer : public Entity {

private:
  double time,max;
  Entity* obj;

public:
  Timer(double start, Entity* object);

  void OnRender();
  void OnLoop( double deltaTime );

};

#endif
