#include "Skybox.h"
#include "Entity.h"
#include "BRep.h"
#include "Vector3.h"
#include "Camera.h"
#include <GL/glut.h>
#include <stdio.h>

Skybox::Skybox(BRep* sky, Camera* camera):Entity()
{
  this->skybox = sky;
  this->cam = camera;
  this->skybox->setScale(Vector3(5,5,5));
}

void Skybox::OnLoop(double v)
{
  skybox->setTranslate(cam->getTranslate());
}

void Skybox::OnRender()
{
  glPushMatrix();
    glDisable(GL_LIGHTING);
    glDepthMask(0);
    //glLoadIdentity();

    skybox->OnRender();

    glDepthMask(1);
    glEnable(GL_LIGHTING);
  glPopMatrix();
}
