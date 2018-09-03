#ifndef _IRONTRAIL_N_DEF
#define _IRONTRAIL_N_DEF

#include "Particle.h"
#include "Vector3.h"

class IronTrail : public ParticleEmissor {

public:
  inline IronTrail(int n):ParticleEmissor(n){};

  virtual void Setup();
};


#endif
