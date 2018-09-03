/**
   \file BlockingInterpolator.cpp
   \brief Implementacao dos metodos da classe BlockingInterpolator

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "BlockingInterpolator.h"
#include "PoseAttr.h"
#include "AttrVector3.h"
#include <stdio.h>
#include <typeinfo>
#include <string>
#include <math.h>

/**
  \brief Construtor para a classe BlockingInterpolator
*/
BlockingInterpolator::BlockingInterpolator(): Interpolator(), dPrecision( 0.01 )
{}
/**
  \brief Construtor de clonagem para a classe BlockingInterpolator
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
BlockingInterpolator::BlockingInterpolator( const BlockingInterpolator& clone ): Interpolator( clone )
{
    this->dPrecision = clone.dPrecision;
}
/**
  \brief Construtor de clonagem para a classe BlockingInterpolator a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
BlockingInterpolator::BlockingInterpolator( BlockingInterpolator* ptrClone ): Interpolator( ptrClone )
{
    this->dPrecision = ptrClone->dPrecision;
}
/**
  \brief Define a precisao para o calculo da interpola��o
  \param dPrecision valor da precisao
*/
void BlockingInterpolator::setPrecision( double dPrecision )
{
    this->dPrecision = dPrecision;
}
/**
   \brief Calcula o proximo valor da interpola��o
   \param dAnimationTime tempo acumulado deste o inicio do processo de anima��o
*/
void BlockingInterpolator::OnLoop( double dAnimationTime )
{
    for( unsigned int uiCounter = 0; uiCounter < this->listOfPoseAttr.size(); uiCounter++ )
    {
        // o tempo transcorrido na anima��o � igual ao tempo da pose ?
        if( fabs( dAnimationTime - this->listOfPoseAttr[ uiCounter ]->getTime() ) <= this->dPrecision )
        {
            AttrVector3 * ptrTweenAttr = new AttrVector3(
                                (( AttrVector3* )this->listOfPoseAttr[ uiCounter ])->getValue(),
                                0.0,
                                this->listOfPoseAttr[ uiCounter ]->getName() );
            ptrTweenAttr->updateParent( this->ptrOwner );
            delete ptrTweenAttr;
            break;
        }
    }
}
