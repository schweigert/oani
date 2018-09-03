#ifndef _GLOW_COMETA_N_DEF_
#define _GLOW_COMETA_N_DEF_

#include "Particle.h"
#include "Vector3.h"

class GlowCometa : public ParticleEmissor {

public:
  inline GlowCometa(int n):ParticleEmissor(n){};

  virtual void Setup();
};

#endif
