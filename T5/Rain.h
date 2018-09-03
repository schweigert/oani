#ifndef _RAIN_N_DEF_
#define _RAIN_N_DEF_

#include "Particle.h"
#include "Vector3.h"

class Rain : public ParticleEmissor {

public:
  inline Rain(int n):ParticleEmissor(n){};

  virtual void Setup();
};


#endif
