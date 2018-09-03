#include "Keyframing.h"
#include "BlockInterpolator.h"
#include "LinearInterpolator.h"
#include "PolynomInterpolator.h"
#include "PoseAttribute.h"
#include "VectorAttribute.h"


#include <stdio.h>

/**
  \brief Construtor para objetos da classe Keyframing
  \param bLoop flag que indica se a animacao deve ser reiniciada apos a execucao do ultimo frame
*/
Keyframing::Keyframing( bool bLoop ): uiCurrPose( 0 ), dAccumTime( 0.0 )
{
	this->setLooping( bLoop );
}
/**
  \brief Construtor de c�pia para ponteiros a objetos da classe Keyframing
  \param ptrClone ponteiro para o objeto do tipo Keyframing a ser clonado
*/
Keyframing::Keyframing( Keyframing * ptrClone )
{
	this->bLoop       = ptrClone->bLoop;
	this->uiCurrPose  = ptrClone->uiCurrPose;
	this->listOfIpos  = ptrClone->listOfIpos;
	this->listOfPoses = ptrClone->listOfPoses;
}
/**
  \brief Destrutor para a lista de poses adicionadas
*/
Keyframing::~Keyframing()
{
	for( vector< Pose* >::iterator ptrPose = this->listOfPoses.begin(); ptrPose != this->listOfPoses.end(); ptrPose++ )
		delete (* ptrPose );
}
/**
  \brief Adiciona uma nova pose a ser interpolada
  \param ptrPose ponteiro para a nova pose a ser interpolada
  \param ipoType tipo de interpolacao a ser aplicada entre esta nova pose e a sua subsequente
*/
void Keyframing::addPose( Pose* ptrPose, Interpolator::InterpolationType ipoType )
{
	this->listOfPoses.push_back( ptrPose );
	this->listOfIpos.push_back( ipoType );
}
/**
  \brief Retorna uma posa especifica dentro da lista de poses
  \param uiIndex indice da posicao a ser retornada
  \return ponteiro para a pose em questao ou nulo caso indice invalido
*/
Pose* Keyframing::getPose( unsigned int uiIndex )
{
	if( uiIndex < this->listOfPoses.size() )
		return this->listOfPoses[ uiIndex ];
	return NULL;
}
/**
  \brief Implementa o processo de animacao pose-to-pose entre as poses pertencentes a este objeto
  \param dDeltaTime tempo transcorrido entre duas chamadas a esta funcao
  \return ponteiro para a pose intermediaria gerada pelo processo de inteporlacao
*/
Pose* Keyframing::OnLoop( double dDeltaTime )
{
	if( this->listOfPoses.size() == 0 ) // nenhuma pose adicionada
		return NULL;

    Pose* tweenPose = NULL;

    this->dAccumTime += dDeltaTime;

    if( this->bLoop && this->dAccumTime >= this->getPose( this->listOfPoses.size()-1 )->getTime() )
        this->dAccumTime -= this->getPose( this->listOfPoses.size()-1 )->getTime();

    for( unsigned int uiPose = 0; uiPose < this->listOfPoses.size()-1; uiPose++ )
    {
        if( this->dAccumTime >= this->getPose( uiPose )->getTime() && this->dAccumTime <= this->getPose( uiPose+1 )->getTime() )
        {
            double dIpoDuration = this->getPose( uiPose+1 )->getTime() - this->getPose( uiPose )->getTime(); // determina o intervalo de tempo entre a pose corrente e a proxima
            double factor = (this->dAccumTime - this->getPose( uiPose )->getTime()) / dIpoDuration;

            tweenPose = new Pose();

            switch( this->listOfIpos[ uiPose ] )
            {
            case Interpolator::LINEAR:
						{
               LinearInterpolator linearIPO;

               for( unsigned int uiCounter = 0; uiCounter < this->getPose( uiPose )->getSize(); uiCounter++ )
               {
                    linearIPO.setStart( this->getPose( uiPose )->getPoseAttribute( uiCounter ) );
                    linearIPO.setEnd( this->getPose( uiPose+1 )->getPoseAttribute( uiCounter ) );
                    tweenPose->addPoseAttribute( linearIPO.Interpolate( factor ) );
										// break;
               }
               break;
						 }
						 case Interpolator::POLYNOM:
						 {
							 PolynomInterpolator polyIPO;

							 for( unsigned int uiCounter = 0; uiCounter < this->getPose( uiPose )->getSize(); uiCounter++ )
							 {
										polyIPO.setStart( this->getPose( uiPose )->getPoseAttribute( uiCounter ) );
										polyIPO.setEnd( this->getPose( uiPose+1 )->getPoseAttribute( uiCounter ) );
										tweenPose->addPoseAttribute( polyIPO.Interpolate( factor ) );
									 // break;
							 }
							 break;
						 }

						 case Interpolator::BLOCK:
						 {
							 BlockInterpolator blockIPO;

							 for( unsigned int uiCounter = 0; uiCounter < this->getPose( uiPose )->getSize(); uiCounter++ )
							 {
										blockIPO.setStart( this->getPose( uiPose )->getPoseAttribute( uiCounter ) );
										blockIPO.setEnd( this->getPose( uiPose+1 )->getPoseAttribute( uiCounter ) );
										tweenPose->addPoseAttribute( blockIPO.Interpolate( factor ) );
									 // break;
							 }
							 break;
						 }

            }
            break;
        }
    }
    return tweenPose;
}
/**
  \brief Define se a animacao deve ser executada em um loop constante (reiniciar sempre que atingir o ultimo frame)
  \param bLoop flag que indica se a animacao deve ser reiniciada apos a execucao do ultimo frame
*/
void Keyframing::setLooping( bool bLoop )
{
	this->bLoop = bLoop;
}
