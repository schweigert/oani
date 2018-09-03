#include "Entity.h"

class Wind : public Entity {

private:
  double timer;
  double force;


public:
  Wind();


  void OnRender();
  void OnLoop(double);
  inline void setForce(double Force) {this->force = Force;}

};
