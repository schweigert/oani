#include "Water.h"

void Water::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 4;
  this->maxRadious = 0.05;
  this->pointSize = 5;

  this->gravity = Vector3(0,0,0);
  this->minVelocity = Vector3(0,-0.3,0);
  this->maxVelocity = Vector3(0,-1,0);

  //this->windAcceleration = Vector3(0,0,0.5);

  this->alphaConstant = 0.3;

  this->minColor = Vector3(0,0,1);
  this->maxColor = Vector3(0,0,1);
  InitialSetup();
}
