#ifndef _WAVEFRONTOBJECT_NOT_INCLUDED_
#define _WAVEFRONTOBJECT_NOT_INCLUDED_

#include "Object.h"

class Vertex {
public:
  float x,y,z;
};

class Uv {
public:
  float x,y;
};

class Normal {
public:
  float x,y,z;
};

class Face {
public:
  Vertex* v1,v2,v3;
  Uv* vt1,vt2,vt3;
  Normal* vn1, vn2, vn3;
};

class WavefrontObject : public Object
{

private:
  GLuint uiElephant;
  vector<Vertex*> listOfV;
  vector<Uv*> listOfVT;
  vector<Normal*> listOfVN;
  vector<Face*> listOfF;
  void LoadMesh(char*);


public:
  WavefrontObject(char*);
  WavefrontObject( WavefrontObject & );
  WavefrontObject( WavefrontObject* );

  void setElephant(GLuint);
  inline GLuint getElephant(){return this->uiElephant;}

  virtual void Initialize();

  virtual void OnRender();

};

#endif
