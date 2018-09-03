#include "Planet.h"
#include "VectorAttribute.h"

/**
  \brief Construtor padrao para a classe Planet
  Cria um objeto Planet vazio
*/
Planet::Planet(): PivotedBRep()
{}
/**
  \brief Construtor de clonagem para objetos da classe Planet
  Copia um objeto Planet
  \param Clone objeto da classe a ser copiado
*/
Planet::Planet( const Planet& Clone ): PivotedBRep( Clone )
{}
/**
  \brief Construtor de clonagem para objetos da classe Planet a partir de ponteiros
  Copia um objeto Planet
  \param ptrClone ponteiro para o objeto da classe a ser copiado
*/
Planet::Planet( Planet* ptrClone ): PivotedBRep( ptrClone )
{}
/**
	\brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
	Esta rotina deve ser sobrecarregada para cada tipo de entidade em particular.
*/
void Planet::OnLoop( double dDeltaTime )
{
	PivotedBRep::OnLoop( dDeltaTime );
}
/**
  \brief Define a animacao do movimento de rotacao (giro sobre seu proprio eixo)
  \param stTime instante de tempo (em milisegundos) que a animacao se inicia
  \param endTime instante de tempo (em milisegundos) que um ciclo da animacao se completa. Este tipo de animacao e ciclica.
*/
void Planet::setRotationPeriod( unsigned int stTime, unsigned int endTime )
{
	if( this->listOfEntities.size() > 0 )
	{
		Keyframing * ptrKeyframing = new Keyframing( true );

		Pose * poseBefore = new Pose(); // pose #1
		poseBefore->setTime( stTime );  // momento em que uma revolu��o se inicia
		poseBefore->addPoseAttribute( new VectorAttribute( "orientation", Vector3::ZERO ) );
		ptrKeyframing->addPose( poseBefore );

		Pose * poseAfter = new Pose(); // pose #2
		poseAfter->setTime( endTime );  // momento em que uma revolu��o se completa
		poseAfter->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 360.0f, 0.0f ) ) );
		ptrKeyframing->addPose( poseAfter );

		this->listOfEntities[0]->setKeyframing( ptrKeyframing );
	}
}
/**
  \brief Define a animacao do movimento de translacao (giro sobre seu elemento pivot)
  \param stTime instante de tempo (em milisegundos) que a animacao se inicia
  \param endTime instante de tempo (em milisegundos) que um ciclo da animacao se completa. Este tipo de animacao e ciclica.
*/
void Planet::setTranslationPeriod( unsigned int stTime, unsigned int endTime )
{
	Keyframing * ptrKeyframing = new Keyframing( true );

	Pose * poseBefore = new Pose(); // pose #1
	poseBefore->setTime( stTime );  // momento em que uma revolu��o se inicia
	poseBefore->addPoseAttribute( new VectorAttribute( "orientation", Vector3::ZERO ) );
	ptrKeyframing->addPose( poseBefore );

	Pose * poseAfter = new Pose(); // pose #2
	poseAfter->setTime( endTime );  // momento em que uma revolu��o se completa
	poseAfter->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 360.0f, 0.0f ) ) );
	ptrKeyframing->addPose( poseAfter );

	this->setKeyframing( ptrKeyframing );
}
