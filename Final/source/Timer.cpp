#include "Timer.h"
#include <stdio.h>

Timer::Timer(double start, Entity* object) : Entity()
{
  this->time = 0;
  this->max = start;
  this->obj = object;
}

void Timer::OnRender()
{
    if(this->time > this->max) {
      obj->OnRender();
    }
}

void Timer::OnLoop(double deltaTime)
{
  if(this->time <= this->max){
    time += deltaTime;
  } else {
    obj->OnLoop(deltaTime);
  }
}
