#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Particle.h"

ParticleEmissor::ParticleEmissor(int size): Entity()
{
  this->size = size;
  this->particles = (ParticleUnit*)malloc(sizeof(ParticleUnit)*size);
}

void ParticleEmissor::InitialSetup()
{
  // Setup inicial das partículas
  for(int i = 0; i < this->size; i++){
    this->particles[i] = CreateUnit();
  }
}





ParticleUnit ParticleEmissor::CreateUnit ()
{
  ParticleUnit ret;
  ret.lifeTime = 0;
  ret.position = Vector3(Random()*2 - 1,0,Random()*2 -1);
  ret.position.Normalize();
  ret.position = ret.position * (float)this->maxRadious * Random();
  ret.velocity = (this->maxVelocity - this->minVelocity)*Random() + this->minVelocity;

  ret.color = minColor;

  return ret;
}

void ParticleEmissor::OnLoop(double dDeltaTime)
{
  for(int i = 0; i < this->size; i++){
    // Verify LifeTime
    float localLife = (this->maxLife - this->minLife)*Random() + this->minLife;
    if(this->particles[i].lifeTime >= localLife){
      particles[i] = CreateUnit();
      continue;
    }

    particles[i].lifeTime += dDeltaTime;
    particles[i].position = particles[i].position + (particles[i].velocity*dDeltaTime);
    particles[i].position = particles[i].position + (this->windAcceleration * dDeltaTime);
    particles[i].position = particles[i].position + (this->windAcceleration * dDeltaTime);
    particles[i].position = particles[i].position + (this->gravity * dDeltaTime);
  }
}

void ParticleEmissor::OnRender()
{
  glPushMatrix();


    glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
    glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );
    glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
    glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );
    glScalef( this->vScale.x, this->vScale.y, this->vScale.z );

    glEnable( GL_BLEND );
    glDisable(GL_LIGHTING);
    glPointSize(this->pointSize);

    glBegin(GL_POINTS);
      for(int i = 0; i < this->size; i++){
        glColor4f(particles[i].color.x,particles[i].color.y,particles[i].color.z,this->alphaConstant);
        glVertex3f(this->particles[i].position.x,this->particles[i].position.y,this->particles[i].position.z);
      }
    glEnd();

    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);

    glColor4f(1,1,1,1);
  glPopMatrix();
}

float ParticleEmissor::Random()
{
  return (float) rand()/RAND_MAX;
}

void ParticleEmissor::Setup()
{
  // Configure aqui!
  this->minLife = 0;
  this->maxLife = 3;
  this->maxRadious = 1;
  this->pointSize = 9;

  //this->gravity = Vector3(0,-0.8,0);
  this->minVelocity = Vector3(-2,0,-2);
  this->maxVelocity = Vector3(2,0,2);

  this->windAcceleration = Vector3(0,100,0);

  this->alphaConstant = 0.7;

  this->minColor = Vector3(1,1,0.65);
  this->maxColor = Vector3(1,1,0);
  InitialSetup();
}
