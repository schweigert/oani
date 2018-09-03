/**
   \file LinearInterpolator.cpp
   \brief Implementacao dos metodos da classe LinearInterpolator

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "LinearInterpolator.h"
#include "PoseAttr.h"
#include <stdio.h>
#include <typeinfo>
#include <string>

/**
  \brief Construtor para a classe LinearInterpolator
*/
LinearInterpolator::LinearInterpolator(): Interpolator()
{}
/**
  \brief Construtor de clonagem para a classe LinearInterpolator
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
LinearInterpolator::LinearInterpolator( const LinearInterpolator& clone ): Interpolator( clone )
{}
/**
  \brief Construtor de clonagem para a classe LinearInterpolator a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
LinearInterpolator::LinearInterpolator( LinearInterpolator* ptrClone ): Interpolator( ptrClone )
{}

/**
   \brief Calcula o proximo valor da interpola��o
   \param dAnimationTime tempo acumulado deste o inicio do processo de anima��o
*/
void LinearInterpolator::OnLoop( double dAnimationTime )
{
    for( unsigned int uiCounter = 0; uiCounter < this->listOfPoseAttr.size()-1; uiCounter++ )
    {
        // o tempo transcorrido na anima��o est� dentro do intervalo entre poses ?
        if( dAnimationTime >= this->listOfPoseAttr[ uiCounter ].getTime() &&
            dAnimationTime <= this->listOfPoseAttr[ uiCounter+1 ].getTime() )
        {
            double dFactor = ( dAnimationTime - this->listOfPoseAttr[ uiCounter ].getTime() ) /
                             ( this->listOfPoseAttr[ uiCounter+1 ].getTime() - this->listOfPoseAttr[ uiCounter ].getTime());

            PoseAttr oTweenAttr( this->listOfPoseAttr[ uiCounter ].getValue() * ( 1.0 - dFactor ) +
                                 this->listOfPoseAttr[ uiCounter+1 ].getValue() * dFactor, 0.0,
                                 this->listOfPoseAttr[ uiCounter ].getName() );
            oTweenAttr.updateParent( this->ptrOwner );
        }
    }
}
