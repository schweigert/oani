/**
   \file Planet.cpp
   \brief Implementacao dos metodos da classe Planet

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Planet.h"
#include "PrimitiveGL.h"
#include "AttrVector3.h"
#include "LinearInterpolator.h"
#include "Animator.h"

/**
  \brief Construtor padrao para a classe Planet
  Cria uma primitiva grafica composta
  \param bDayAnimation flag que indica se o planeta tem animaçao do dia
  \param bYearAnimation flag que indica se o planeta tem aniaçao do ano
*/
Planet::Planet( bool bDayAnimation, bool bYearAnimation ): Joint()
{
    this->setDayAnimation( 0.0f, 1.0f );
    this->setYearAnimation( 0.0f, 10.0f );
    this->bAnimateDay  = bDayAnimation;
    this->bAnimateYear = bYearAnimation;
}
/**
  \brief Construtor de copia para a classe Planet
  Cria uma copia exata de um objeto Planet existente
  \param clone Objeto  da classe Planet a ser clonado
*/
Planet::Planet( const Planet &clone ): Joint( clone )
{
    this->setDayAnimation( clone.fDayST, clone.fDayEND );
    this->setYearAnimation( clone.fYearST, clone.fYearEND );
    this->bAnimateDay  = clone.bAnimateDay;
    this->bAnimateYear = clone.bAnimateYear;
}
/**
  \brief Construtor de copia para a classe Planet a partir de ponteiros
  Cria uma copia exata de um objeto Planet existente
  \param ptrClone Ponteiro para um objeto Planet a ser clonado
*/
Planet::Planet( Planet* ptrClone ): Joint( ptrClone )
{
    this->setDayAnimation( ptrClone->fDayST, ptrClone->fDayEND );
    this->setYearAnimation( ptrClone->fYearST, ptrClone->fYearEND );
    this->bAnimateDay  = ptrClone->bAnimateDay;
    this->bAnimateYear = ptrClone->bAnimateYear;
}
/**
   \brief Define o intervalo de tempo dos frames da animaçao do dia do planeta (movimento de rotaçao sobre si)
   \param fStart tempo de inicio da animaçao
   \param fEnd tempo de fim da animaçao
*/
void Planet::setDayAnimation( float fStart, float fEnd )
{
    this->fDayST  = fStart;
    this->fDayEND = fEnd;
}
/**
   \brief Define o intervalo de tempo dos frames da animaçao do ano do planeta (movimento de rotaçao sobre o pivot)
   \param fStart tempo de inicio da animaçao
   \param fEnd tempo de fim da animaçao
*/
void Planet::setYearAnimation( float fStart, float fEnd )
{
    this->fYearST  = fStart;
    this->fYearEND = fEnd;
}
/**
   \brief Rotina responsavel pela construção do objeto
*/
void Planet::Initialize()
{
    Animator *  ptrAnimator = new Animator( Animator::LOOP );

    if( this->bAnimateDay )
    {
        AttrVector3 * ptrDayST = new AttrVector3( Vector3(), this->fDayST, PoseAttr::ROTATE );
        AttrVector3 * ptrDayEND = new AttrVector3( Vector3( 0.0f, 360.0f, 0.0f ), this->fDayEND, PoseAttr::ROTATE );

        LinearInterpolator * ptrDayAnimation = new LinearInterpolator();
        ptrDayAnimation->addAttribute( ptrDayST );
        ptrDayAnimation->addAttribute( ptrDayEND );

        ptrAnimator->addInterpolator( ptrDayAnimation );
    }

    if( this->bAnimateYear )
    {
        AttrVector3 * ptrYearST = new AttrVector3( Vector3(), this->fYearST, PoseAttr::ROTATE_PIVOT );
        AttrVector3 * ptrYearEND = new AttrVector3( Vector3( 0.0f, 360.0f, 0.0f ), this->fYearEND, PoseAttr::ROTATE_PIVOT );

        LinearInterpolator * ptrYearAnimation = new LinearInterpolator();
        ptrYearAnimation->addAttribute( ptrYearST );
        ptrYearAnimation->addAttribute( ptrYearEND );

        ptrAnimator->addInterpolator( ptrYearAnimation );
    }

	PrimitiveGL * ptrPlanet = new PrimitiveGL( );
	ptrPlanet->setResolution( 25,25 );
	this->listOfEntities.push_back( ptrPlanet );

	this->setAnimator( ptrAnimator );
}
