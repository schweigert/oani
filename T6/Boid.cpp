#include <GL/glut.h>
#include <stdio.h>

#include "Boid.h"
#include "Entity.h"
#include "Vector3.h"

Boid::Boid(Entity* ent, Entity* flw):Entity()
{
  this->object = ent;
  this->leader = flw;
  this->velocity = 3;
  this->deltaPosition = Vector3(0,-1,-15);
}

float lastDelta = 0;

void Boid::OnLoop(double deltaTime)
{
  this->object->OnLoop(deltaTime);
  Vector3 last = this->vTranslate;
  this->vTranslate = this->vTranslate + ( ( this->leader->getTranslate() - this->vTranslate + this->deltaPosition ) * (deltaTime*this->velocity));
  Vector3 delta = this->vTranslate - last;


}

void Boid::OnRender()
{
  glPushMatrix();


    glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
    glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );
    glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
    glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );
    glScalef( this->vScale.x, this->vScale.y, this->vScale.z );

    this->object->OnRender();

  glPopMatrix();
}
