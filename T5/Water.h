#ifndef _WATER_N_DEF_
#define _WATER_N_DEF_

#include "Particle.h"
#include "Vector3.h"

class Water : public ParticleEmissor {

public:
  inline Water(int n):ParticleEmissor(n){};

  virtual void Setup();
};


#endif
