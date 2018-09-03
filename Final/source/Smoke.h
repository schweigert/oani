#ifndef _SMOKE_N_DEF_
#define _SMOKE_N_DEF_

#include "Particle.h"
#include "Vector3.h"

class Smoke : public ParticleEmissor {

public:
  inline Smoke(int n):ParticleEmissor(n){};

  virtual void Setup();
};


#endif
