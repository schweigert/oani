#ifndef _BOID_NOT_DEF_
#define _BOID_NOT_DEF_


#include "Entity.h"
#include "Vector3.h"

class Boid : public Entity
{

  Entity* leader;
  Entity* object;
  float velocity;

  Vector3 deltaPosition;


public:

  Boid(Entity* obj ,Entity* lead);

  inline void setVelocity(float v) {this->velocity = v;}
  inline void setDeltaPosition(Vector3 v){this->deltaPosition = v;}

  void OnLoop(double);
  void OnRender();

};

#endif
