/**
   \file Animator.cpp
   \brief Implementacao dos metodos da classe Animator

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Animator.h"
#include <stdlib.h>

/**
  \brief Construtor para a classe Animator
  \param animType tipo de anima��o executada por este animador
*/
Animator::Animator( Animator::AnimationType animType ): ptrOwner( NULL ), dAnimationTime( 0.0 ), animationType( animType )
{}
/**
  \brief Construtor de clonagem para a classe Animator
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
Animator::Animator( const Animator& clone ): dAnimationTime( 0.0 )
{
    this->ptrOwner            = clone.ptrOwner;
    this->animationType       = clone.animationType;
    this->listOfInterpolators = clone.listOfInterpolators;
}
/**
  \brief Construtor de clonagem para a classe Animator a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
Animator::Animator( Animator* ptrClone ): dAnimationTime( 0.0 )
{
    this->ptrOwner            = ptrClone->ptrOwner;
    this->animationType       = ptrClone->animationType;
    this->listOfInterpolators = ptrClone->listOfInterpolators;
}
/**
   \brief Destrutor para os objetos dinamicos utilizados por esta classe
*/
Animator::~Animator()
{
    for(vector<Interpolator *>::iterator ptrInterp = this->listOfInterpolators.begin();
        ptrInterp != this->listOfInterpolators.end(); ptrInterp++ )
        delete (* ptrInterp);
}
/**
   \brief Associa este animador a um objeto-pai do tipo Entity
   \param ptrOwner ponteiro para o objeto ao qual este animador sera associado
*/
void Animator::setParent( Entity* ptrOwner )
{
    this->ptrOwner = ptrOwner;

    for(vector<Interpolator *>::iterator ptrInterp = this->listOfInterpolators.begin();
        ptrInterp != this->listOfInterpolators.end(); ptrInterp++ )
        (* ptrInterp )->setParent( this->ptrOwner );
}
/**
   \brief Adiciona um novo interpolador a esta anima��o
   \param ptrInterp pointeiro para o novo interpolador a ser adicionado a esta anima��o
*/
void Animator::addInterpolator( Interpolator * ptrInterp )
{
    if( ptrInterp )
        this->listOfInterpolators.push_back( ptrInterp );
}
/**
   \brief Executa o processo de anima��o
   \param dDeltaTime tempo transcorrido deste a ultima chamada desta fun��o
*/
void Animator::OnLoop( double dDeltaTime )
{
    this->dAnimationTime += dDeltaTime;

    for( vector<Interpolator *>::iterator itInterp = this->listOfInterpolators.begin();
         itInterp != this->listOfInterpolators.end(); itInterp++ )
         {
             (* itInterp )->OnLoop( this->dAnimationTime );
         }
}
