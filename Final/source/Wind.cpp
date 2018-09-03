#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "Wind.h"
#include "Entity.h"

Wind::Wind (): Entity()
{
  timer = 0;
  force = 1;
}

void Wind::OnRender()
{
  glPushMatrix();

  GLfloat deformacao[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    sin(timer)*force + force // Quantidade
    , 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  glMultMatrixf(deformacao);

  glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
  glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );
  glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
  glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );
  glScalef( this->vScale.x, this->vScale.y, this->vScale.z );

  if( this->listOfEntities.size() > 0 )
    for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
      ptrEntity != this->listOfEntities.end(); ptrEntity++ )
      (* ptrEntity )->OnRender();

  glPopMatrix();
}

void Wind::OnLoop(double dDeltaTime)
{

  timer = timer + dDeltaTime;

  if( this->listOfEntities.size() > 0 )
    for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
      ptrEntity != this->listOfEntities.end(); ptrEntity++ )
      (* ptrEntity )->OnLoop( dDeltaTime );
}
