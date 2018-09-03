#include "Grass.h"

void GrassParticle::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 15;
  this->maxRadious = 1;
  this->pointSize = 6;

  this->gravity = Vector3(0,-0.3,0);
  this->minVelocity = Vector3(0,0,0);
  this->maxVelocity = Vector3(0,0,0);

  this->windAcceleration = Vector3(0.3,0,0);

  this->alphaConstant = 0.8;

  this->minColor = Vector3(0.29,1,0)*0.3;
  this->maxColor = Vector3(0.6,0.6,0.6);
  InitialSetup();
}
