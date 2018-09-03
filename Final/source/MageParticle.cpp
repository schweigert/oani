#include "MageParticle.h"

void MageParticle::Setup()
{
  // Configure aqui!
  this->minLife = 3;
  this->maxLife = 15;
  this->maxRadious = 0.05;
  this->pointSize = 4;

  this->gravity = Vector3(0,0,0);
  this->minVelocity = Vector3(0,0.3,0);
  this->maxVelocity = Vector3(0,0.6,0);

  this->windAcceleration = Vector3(0,0,0);

  this->alphaConstant = 0.1;

  this->minColor = Vector3(0,0.5,1);
  this->maxColor = Vector3(0.6,0.6,0.6);
  InitialSetup();
}


void MageCometa::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 15;
  this->maxRadious = 4;
  this->pointSize = 2;

  this->gravity = Vector3(0,9,0);
  this->minVelocity = Vector3(0,5,0);
  this->maxVelocity = Vector3(0,10,0);

  this->windAcceleration = Vector3(0,0,0);

  this->alphaConstant = 1;

  this->minColor = Vector3(0.3,0.3,0.3);
  this->maxColor = Vector3(0.6,0.6,0.6);
  InitialSetup();
}
