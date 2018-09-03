/**
   \file PolynomInterpolator.cpp
   \brief Implementacao dos metodos da classe PolynomInterpolator

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "PolynomInterpolator.h"
#include "PoseAttr.h"
#include "AttrVector3.h"
#include "Matrix.h"
#include <stdio.h>
#include <typeinfo>
#include <string>
#include <math.h>

/**
  \brief Construtor para a classe PolynomInterpolator
*/
PolynomInterpolator::PolynomInterpolator(PoseAttr::AttrName attr,double min, double max): Interpolator()
{
  this->dTmin = min;
  this->dTmax = max;
  this->attrName = attr;
}


double PolynomInterpolator::Px(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsX[j];
  }
  return r;
}


double PolynomInterpolator::Py(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsY[j];
  }
  return r;
}


double PolynomInterpolator::Pz(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsZ[j];
  }
  return r;
}


double PolynomInterpolator::Pw(double t){
  double r = 0;
  for(int j = 0; j < iControlPoints; j++){
    r +=  pow(t,j)*pdCoefficientsW[j];
  }
  return r;
}
/**
  \brief Calcula os valores necessários para a interpolação
*/
void PolynomInterpolator::Setup()
{

  double aux;

  // Número de pontos
  this->iControlPoints = this->listOfPoseAttr.size();

  this->matrixX = new Matrix(this->iControlPoints);
  this->matrixY = new Matrix(this->iControlPoints);
  this->matrixZ = new Matrix(this->iControlPoints);
  this->matrixW = new Matrix(this->iControlPoints);

  // Resolvendo para X
  for(int i = 0; i < iControlPoints; i++){
    matrixX->SetValue(i+1,iControlPoints+1,((AttrVector3*)this->listOfPoseAttr[i])->getValue().x);
    aux = ((AttrVector3*)this->listOfPoseAttr[i])->getTime();

    for(int j = 0; j < iControlPoints; j++){
      matrixX->SetValue(i+1,j+1, pow(aux,j));
    }
  }

  // matrixX->print();
  pdCoefficientsX = matrixX->GaussMethod();
  // matrixX->print();


  // Resolvendo para Y
  for(int i = 0; i < iControlPoints; i++){
    matrixY->SetValue(i+1,iControlPoints+1,((AttrVector3*)this->listOfPoseAttr[i])->getValue().y);
    aux = ((AttrVector3*)this->listOfPoseAttr[i])->getTime();
    for(int j = 0; j < iControlPoints; j++){
      matrixY->SetValue(i+1,j+1, pow(aux,j));
    }
  }
  // matrixX->print();
  pdCoefficientsY = matrixY->GaussMethod();
  // matrixX->print();

  // Resolvendo para Z
  for(int i = 0; i < iControlPoints; i++){
    matrixZ->SetValue(i+1,iControlPoints+1,((AttrVector3*)this->listOfPoseAttr[i])->getValue().z);
    aux = ((AttrVector3*)this->listOfPoseAttr[i])->getTime();
    for(int j = 0; j < iControlPoints; j++){
      matrixZ->SetValue(i+1,j+1, pow(aux,j));
    }
  }
  // matrixX->print();
  pdCoefficientsZ = matrixZ->GaussMethod();
  // matrixX->print();
  // Resolvendo para W
  for(int i = 0; i < iControlPoints; i++){
    matrixW->SetValue(i+1,iControlPoints+1,((AttrVector3*)this->listOfPoseAttr[i])->getValue().w);
    aux = ((AttrVector3*)this->listOfPoseAttr[i])->getTime();
    for(int j = 0; j < iControlPoints; j++){
      matrixW->SetValue(i+1,j+1, pow(aux,j));
    }
  }
  // matrixX->print();
  pdCoefficientsW = matrixW->GaussMethod();
  // matrixX->print();
  printf("\nx value:\n F(x)=");
  for(int i = 0; i < iControlPoints; i++){
    printf("+(%2.2lf)x^%d ",pdCoefficientsX[i],i);
  }

  printf("\ny value:\nG(x)=");
  for(int i = 0; i < iControlPoints; i++){
    printf("+(%2.5lf)x^%d ",pdCoefficientsY[i],i);
  }

  printf("\nz value:\n H(x)=");
  for(int i = 0; i < iControlPoints; i++){
    printf("+(%2.5lf)x^%d ",pdCoefficientsZ[i],i);
  }
  printf("\nw value:\n I(x)=");
  for(int i = 0; i < iControlPoints; i++){
    printf("+(%2.5lf)x^%d ",pdCoefficientsW[i],i);
  }

  printf("\n");




}
/**
   \brief Calcula o proximo valor da interpola��o
   \param dAnimationTime tempo acumulado deste o inicio do processo de anima��o
*/
void PolynomInterpolator::OnLoop( double dAnimationTime )
{

  if(dAnimationTime >= dTmax) return;
  if(dAnimationTime <= dTmin) return;



  AttrVector3 * ptrTweenAttr = new AttrVector3 (
    Vector3 (
      Px(dAnimationTime),
      Py(dAnimationTime),
      Pz(dAnimationTime),
      Pw(dAnimationTime)
    ),
      0.0
     ,
     attrName
    );

  ptrTweenAttr->updateParent( this->ptrOwner );
  delete ptrTweenAttr;

}
