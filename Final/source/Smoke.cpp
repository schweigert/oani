#include "Smoke.h"

void Smoke::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 15;
  this->maxRadious = 0.15;
  this->pointSize = 3;

  this->gravity = Vector3(0,-0.8,0);
  this->minVelocity = Vector3(0,0.3,0);
  this->maxVelocity = Vector3(0.3,2,0);

  this->windAcceleration = Vector3(0,0,0.1);

  this->alphaConstant = 0.1;

  this->minColor = Vector3(0,0,0);
  this->maxColor = Vector3(0.6,0.6,0.6);
  InitialSetup();
}
