#include "ColoredEntity.h"
#include "VectorAttribute.h"

/**
  \brief Construtor para a classe ColoredEntity.<br>
  Cria um objeto vazio na cor branca
*/
ColoredEntity::ColoredEntity():Entity()
{
   this->setColor( Vector3::WHITE );
}
/**
  \brief Construtor de clonagem para a classe ColoredEntity.<br>
  Cria uma copia exata de um objeto entidade fisica ja existente
  \param clone Objeto a ser clonado
*/
ColoredEntity::ColoredEntity( const ColoredEntity& clone ): Entity( clone )
{
	this->vColor = clone.vColor;
}
/**
  \brief Construtor de clonagem para a classe ColoredEntity a partir de ponteiros.<br>
  Cria uma copia exata de um objeto entidade fisica ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
ColoredEntity::ColoredEntity( ColoredEntity* ptrClone ): Entity( ptrClone )
{
	this->vColor = ptrClone->vColor;
}
/**
  \brief Inicializa o atributo cor do objeto
  \param color cor a ser atribuida ao objeto
*/
void ColoredEntity::setColor( const Vector3 color )
{
	this->vColor = color;
}
/**
	\brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
	Esta rotina deve ser sobrecarregada para cada tipo de entidade em particular.
*/
void ColoredEntity::OnLoop( double dDeltaTime )
{
	if( this->ptrKeyframing )
	{
		Pose * ptrCurrentPose = NULL;
		if( ptrCurrentPose = this->ptrKeyframing->OnLoop( dDeltaTime ) )
		{
			if( ptrCurrentPose->hasPoseAttributeName( "color" ) )
				this->setColor( ( ( VectorAttribute* ) ptrCurrentPose->getPoseAttribute( "color" ) )->getValue() );
		}
	}

	Entity::OnLoop( dDeltaTime );
}
