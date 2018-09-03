#ifndef _SKYBOX_N_DEF_
#define _SKYBOX_N_DEF_

#include "Entity.h"
#include "BRep.h"
#include "Camera.h"
class Skybox : public Entity {

private:
  BRep* skybox;
  Camera* cam;
  float rot;

public:
  Skybox(BRep* , Camera* );

  void OnLoop(double);
  void OnRender();
};

#endif
