#ifndef _GRASS_N_DEF_
#define _GRASS_N_DEF_

#include "Particle.h"
#include "Vector3.h"

class GrassParticle : public ParticleEmissor {

public:
  inline GrassParticle(int n):ParticleEmissor(n){};

  virtual void Setup();
};

#endif
