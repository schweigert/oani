#ifndef _MAGEP_N_DEF_
#define _MAGEP_N_DEF_

#include "Particle.h"
#include "Vector3.h"

class MageParticle : public ParticleEmissor {

public:
  inline MageParticle(int n):ParticleEmissor(n){};

  virtual void Setup();
};


class MageCometa : public ParticleEmissor {

public:
  inline MageCometa(int n):ParticleEmissor(n){};

  virtual void Setup();
};


#endif
