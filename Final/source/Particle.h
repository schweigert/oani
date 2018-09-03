#ifndef _PARTICLE_N_DEF_
#define _PARTICLE_N_DEF_

#include "Entity.h"
#include "Vector3.h"

typedef struct {

  float lifeTime;
  Vector3 position;
  Vector3 velocity;
  Vector3 color;

}ParticleUnit;
// Esta merda não funciona, mas já considero pacas

class ParticleEmissor : public Entity {


private:

public:
  ParticleEmissor(int size);

  virtual void Setup();
  void OnLoop(double);
  void OnRender();

  ParticleUnit *particles;
  int size;
  float minLife,maxLife;
  float maxRadious;
  float pointSize;

  Vector3 gravity;
  Vector3 windAcceleration;
  Vector3 minVelocity, maxVelocity;

  float alphaConstant;
  Vector3 minColor,maxColor;

  float Random();
  ParticleUnit CreateUnit();
  void InitialSetup();

};



#endif
