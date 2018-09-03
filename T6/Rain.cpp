#include "Rain.h"

void Rain::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 10;
  this->maxRadious = 4.5;
  this->pointSize = 3;

  this->gravity = Vector3(0,0,0);
  this->minVelocity = Vector3(0,-2,0);
  this->maxVelocity = Vector3(2,-5,0);

  this->windAcceleration = Vector3(0,0,0);

  this->alphaConstant = 0.1;

  this->minColor = Vector3(0,0,0.7f);
  InitialSetup();
}
