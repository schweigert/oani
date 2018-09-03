#include "GlowCometa.h"

void GlowCometa::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 5;
  this->maxRadious = 10;
  this->pointSize = 3;

  this->gravity = Vector3(0,15,0);
  this->minVelocity = Vector3(-0.3,0,2,-0.3);
  this->maxVelocity = Vector3(0.3,5,0.3);

  this->windAcceleration = Vector3(0,0,0.1);

  this->alphaConstant = 0.7;

  this->minColor = Vector3(1,0,0);
  this->maxColor = Vector3(1,0,0);
  InitialSetup();
}
