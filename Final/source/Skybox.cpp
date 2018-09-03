#include "Skybox.h"
#include "Entity.h"
#include "BRep.h"
#include "Vector3.h"
#include "Camera.h"
#include <GL/glut.h>
#include <stdio.h>

Skybox::Skybox(BRep* sky, Camera* camera):Entity()
{
  this->rot = 0;
  this->skybox = sky;
  this->cam = camera;
  this->skybox->setScale(Vector3(5,5,5));
}

void Skybox::OnLoop(double v)
{
  rot += v*3;
  if(rot > 360) rot -= 360;
  skybox->setRotate(Vector3(0,rot,0));
  skybox->setTranslate(cam->getTranslate());
}

void Skybox::OnRender()
{
  glPushMatrix();
    glDisable(GL_LIGHTING);
    glDepthMask(0);
    skybox->OnRender();

    glDepthMask(1);
    glEnable(GL_LIGHTING);
  glPopMatrix();
}
