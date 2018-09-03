#ifndef _FIRE_N_DEF_
#define _FIRE_N_DEF_

#include "Particle.h"
#include "Vector3.h"

class Fire : public ParticleEmissor {

public:
  inline Fire(int n):ParticleEmissor(n){};
};


#endif
