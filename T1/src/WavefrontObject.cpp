#include "WavefrontObject.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

WavefrontObject::WavefrontObject(char* filename): Object()
{
  this->LoadMesh(filename);
}

WavefrontObject::WavefrontObject(WavefrontObject& clone): Object(clone)
{
  this->setElephant((GLuint)(clone.getElephant()));
}

WavefrontObject::WavefrontObject(WavefrontObject* clone): Object(clone)
{
  this->setElephant(clone->getElephant());
}

void WavefrontObject::setElephant(GLuint id){
  this->uiElephant = id;
}

void WavefrontObject::Initialize(){}

void WavefrontObject::LoadMesh(char* filename)
{
  FILE *fp;
  int read;
  GLfloat x, y, z;
  char ch;
  this->uiElephant=glGenLists(1);
  fp=fopen(filename,"r");
  if (!fp)
  {
    printf("can't open file %s\n", filename);
  	 exit(1);
  }
  glPointSize(1);
  glNewList(this->uiElephant, GL_COMPILE);
  {
    glPushMatrix();
    glBegin(GL_POINTS);
    while(!(feof(fp)))
     {
      read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
      if(read==4&&ch=='v')
      {
       glVertex3f(x,y,z);
      }
     }
    glEnd();
  }
  glPopMatrix();
  glEndList();
  fclose(fp);
}

/*

void WavefrontObject::LoadMesh(char* filename)
{
  FILE* fp;
  fp = fopen(filename, "r");
  char* aux[5] = {0};
  if(!pf){
    printf("Error on load %s\n", filename);
  }

  Vertex* auxV;
  Uv* auxUv;
  Normal* auxNormal;
  Face* auxFace;

  int v1,v2,v3,
      vt1,vt2,vt3,
      vn1,vn2,vn3;

  while(!(feof(fp))){
    fscanf(fp, "%s", aux);

    if(aux[0]=='v' && aux[1]=='t'){
      auxUv = new Uv();

      fscanf(pf,"%f %f",&(auxUv->x), &(auxUv->y));
      this->listOfVT.push_back(auxUv);
      continue;
    }

    if(aux[0]=='v' && aux[1]=='n'){
      auxNormal = new Normal();

      fscanf(fp, "%f %f %f", &(auxNormal->x),&(auxNormal->y),&(auxNormal->z));
      this->listOfVN.push_back(auxNormal);
    }

    if(aux[0]=='v'){
      auxV = new Vertex();
      fscanf(fp, "%f %f %f", &(auxV->x),&(auxV->y),&(auxV->z));
      this->listOfV.push_back(auxV);
    }

    if(au[0]=='f'){
      auxFace = new Face();
      fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d",
      &v1,&vt1,&vn1,
      &v2,&vt2,&vn2,
      &v3,&vt3,&vn3
    );

    auxFace->v1 = this->listOfV[v1-1];
    auxFace->v2 = this->listOfV[v2-2];
    auxFace->v3 = this->listOfV[v3-3];

    auxFace->vn1 = this->listOfVN[vn1-1];
    auxFace->vn2 = this->listOfVN[vn2-1];
    auxFace->vn3 = this->listOfVN[vn3-1];

    auxFace->vt1 = this->listOfVT[vt1-1];
    auxFace->vt2 = this->listOfVT[vt2-1];
    auxFace->vt3 = this->listOfVT[vt3-1];

    this->listOfF.push_Back(auxFace);

    }

    for(vector<Faces>::interator pointer = this->listOfF.begin(); pointer != this->listOfF.end(); pointer++)
      printf("%f %f %f", *(pointer)->v1->x, *(pointer)->v1->y, *(pointer)->v1->z);
  }



  free(aux);
}

*/

void WavefrontObject::OnRender()
{
  glPushMatrix();

  glCallList(this->uiElephant);

  for( vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++ )
        (* pointer )->OnRender();

  glPopMatrix();
}
