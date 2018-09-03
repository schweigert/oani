#include "IronTrail.h"

void IronTrail::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 15;
  this->maxRadious = 0.5;
  this->pointSize = 8;

  this->gravity = Vector3(0,-0.8,0);
  this->minVelocity = Vector3(0,1,0);
  this->maxVelocity = Vector3(0,3,0);

  this->windAcceleration = Vector3(0,0,0.1);

  this->alphaConstant = 0.3;

  this->minColor = Vector3(1,1,0.6);
  InitialSetup();
}
