/**
   \file Fish.cpp
   \brief Implementacao dos metodos da classe Fish

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include <stdio.h>
#include "Fish.h"
#include "PrimitiveGL.h"
#include "AttrVector3.h"
#include "LinearInterpolator.h"
#include "Animator.h"

/**
  \brief Construtor padrao para a classe Fish
  Cria uma primitiva grafica composta
  \param bDayAnimation flag que indica se o Fisha tem anima�ao do dia
  \param bYearAnimation flag que indica se o Fisha tem ania�ao do ano
*/
Fish::Fish(): Joint()
{
  Initialize();
}
/**
  \brief Construtor de copia para a classe Fish
  Cria uma copia exata de um objeto Fish existente
  \param clone Objeto  da classe Fish a ser clonado
*/
Fish::Fish( const Fish &clone ): Joint( clone )
{
  Initialize();
}
/**
  \brief Construtor de copia para a classe Fish a partir de ponteiros
  Cria uma copia exata de um objeto Fish existente
  \param ptrClone Ponteiro para um objeto Fish a ser clonado
*/
Fish::Fish( Fish* ptrClone ): Joint( ptrClone )
{
  Initialize();
}


/**
   \brief Rotina responsavel pela constru��o do objeto
*/
void Fish::Initialize()
{

  PrimitiveGL * ptrBody = new PrimitiveGL(PrimitiveGL::CUBE);
  ptrBody->setScale(Vector3(0.2,0.2,0.2));
  ptrBody->setRotate(Vector3(45,45,0));
  ptrBody->setTranslate(Vector3(0.0, 0.0, 0.0));
  ptrBody->setColor(Vector3(1,1,1));
  this->listOfEntities.push_back( ptrBody );

  Animator *  ptrAnimator = new Animator( Animator::LOOP );

  AttrVector3* attrRotTail01 = new AttrVector3(Vector3(0,-60,0),0.0f, PoseAttr::ROTATE);
  AttrVector3* attrRotTail02 = new AttrVector3(Vector3(0,60,0),1.0f, PoseAttr::ROTATE);
  AttrVector3* attrRotTail03 = new AttrVector3(Vector3(0,-60,0),2.0f, PoseAttr::ROTATE);

  LinearInterpolator* intTail = new LinearInterpolator ();
  intTail->addAttribute(attrRotTail01);
  intTail->addAttribute(attrRotTail02);
  intTail->addAttribute(attrRotTail03);

    ptrAnimator->addInterpolator(intTail);

    FishTail * ptrTail = new FishTail();
    ptrTail->setAnimator(ptrAnimator);
    Attach(ptrTail);
}

// ********************************************************************
//                FISH TAIL
// ********************************************************************

/**
  \brief Construtor padrao para a classe Fish
  Cria uma primitiva grafica composta
  \param bDayAnimation flag que indica se o Fisha tem anima�ao do dia
  \param bYearAnimation flag que indica se o Fisha tem ania�ao do ano
*/
FishTail::FishTail(): Joint()
{
  Initialize();
}
/**
  \brief Construtor de copia para a classe Fish
  Cria uma copia exata de um objeto Fish existente
  \param clone Objeto  da classe Fish a ser clonado
*/
FishTail::FishTail( const FishTail &clone ): Joint( clone )
{
  Initialize();
}
/**
  \brief Construtor de copia para a classe Fish a partir de ponteiros
  Cria uma copia exata de um objeto Fish existente
  \param ptrClone Ponteiro para um objeto Fish a ser clonado
*/
FishTail::FishTail( FishTail* ptrClone ): Joint( ptrClone )
{
  Initialize();
}


/**
   \brief Rotina responsavel pela constru��o do objeto
*/
void FishTail::Initialize()
{
  PrimitiveGL * ptrTail = new PrimitiveGL(PrimitiveGL::CUBE);
  ptrTail->setScale(Vector3(0.2,0.2,0.1));
  ptrTail->setRotate(Vector3(0,0,45));
  ptrTail->setTranslate(Vector3(0.2, 0.0, 0.0));
  ptrTail->setColor(Vector3(1,153/255.0,0));
  this->listOfEntities.push_back( ptrTail );
}
