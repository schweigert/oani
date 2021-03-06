/**
   \file Entity.cpp
   \brief Implementacao dos metodos da classe Entity

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Agosto, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Entity.h"
#include "VectorAttribute.h"
#include <stdio.h>

/**
  \brief Construtor para a classe Entity
  Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
  em escala canonica.
*/
Entity::Entity()
{
    this->ptrKeyframing = NULL;
    this->setTranslate( Vector3::ZERO );
    this->setRotate( Vector3::ZERO );
    this->setScale( Vector3( 1.0f, 1.0f, 1.0f, 0.0f ) );
}
/**
  \brief Construtor de clonagem para a classe Entity
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
Entity::Entity( const Entity& clone )
{
	this->ptrKeyframing = new Keyframing( (( Entity )clone ).getKeyframing() );
	this->setTranslate( clone.vTranslate );
	this->setRotate( clone.vRotate );
	this->setScale( clone.vScale );
	this->listOfEntities = clone.listOfEntities;
}
/**
  \brief Construtor de clonagem para a classe Entity a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
Entity::Entity( Entity* ptrClone )
{
	this->ptrKeyframing = new Keyframing( ptrClone->getKeyframing() );
	this->setTranslate( ptrClone->vTranslate );
	this->setRotate( ptrClone->vRotate );
	this->setScale( ptrClone->vScale );
	this->listOfEntities = ptrClone->listOfEntities;
}
/**
  \brief Destrutor para a classe Entity
*/
Entity::~Entity()
{
	if( this->ptrKeyframing )
		delete this->ptrKeyframing;
	this->ptrKeyframing = NULL; // reiniciar o ponteiro elimina qualquer potencial lixo associado a ele remanescente da dele�ao

	for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
		ptrEntity != this->listOfEntities.end(); ptrEntity++ )
		delete (* ptrEntity );
}
/**
  \brief Define a posicao espacial para o objeto (em coordenadas locais)
  \param vec coordenadas do vetor translacao
*/
void Entity::setTranslate( Vector3 vec )
{
   this->vTranslate = vec;
}
/**
  \brief Define orientacao espacial para o objeto (em coordenadas locais)
  \param vec coordenadas do vetor orientacao
*/
void Entity::setRotate( Vector3 vec )
{
   this->vRotate = vec;
}
/**
  \brief Define o tamanho do objeto (em coordenadas locais)
  \param vec fatores de escala para o objeto
*/
void Entity::setScale( Vector3 vec )
{
   this->vScale = vec;
}
/**
  \brief Define o ponteiro para o objeto interpolador de animacoes pose-to-pose
  \param ptrKeyfrm ponteiro para o objeto Keyframing a ser utilizado
*/
void Entity::setKeyframing( Keyframing * ptrKeyfrm )
{
    if( ptrKeyfrm )
        this->ptrKeyframing = ptrKeyfrm;
}
/**
  \brief Adiciona um novo objeto Entity como filho deste objeto, ou seja, relativo ao sistema de coordenadas deste
  \param ptrEntity ponteiro para o objeto a ser associado a este sistema de coordenadas
*/
void Entity::attach( Entity * ptrEntity )
{
	if( ptrEntity )
		this->listOfEntities.push_back( ptrEntity );
}
/**
  \brief Retorna o ponteiro para um dos filhos associados a esta entidade
  \param uiIndex indice (na lista de filhos) do filho a ser retornado
  \return ponteiro para o respectivo objeto ou nulo caso indice fornecido seja invalido
*/
Entity* Entity::getChild( unsigned int uiIndex )
{
	if( uiIndex < this->listOfEntities.size() )
		return this->listOfEntities[ uiIndex ];
	return NULL;
}
/**
	\brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
	Esta rotina deve ser sobrecarregada para cada tipo de entidade em particular.
*/
void Entity::OnLoop( double dDeltaTime )
{
	if( this->ptrKeyframing )
	{
		Pose * ptrCurrentPose = NULL;
		if( ptrCurrentPose = this->ptrKeyframing->OnLoop( dDeltaTime ) )
		{
			if( ptrCurrentPose->hasPoseAttributeName( "position" ) )
				this->setTranslate( ( ( VectorAttribute* ) ptrCurrentPose->getPoseAttribute( "position" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "orientation" ) )
				this->setRotate( ( ( VectorAttribute* ) ptrCurrentPose->getPoseAttribute( "orientation" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "scale" ) )
				this->setScale( ( ( VectorAttribute* ) ptrCurrentPose->getPoseAttribute( "scale" ) )->getValue() );

            //printf("Tra: %f %f %f\n", this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
            //printf("Esc: %f %f %f\n", this->vScale.x, this->vScale.y, this->vScale.z );
            //printf("Rot: %f %f %f\n\n", this->vRotate.x, this->vRotate.y, this->vRotate.z );
		}
	}

	if( this->listOfEntities.size() > 0 )
		for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
			ptrEntity != this->listOfEntities.end(); ptrEntity++ )
			(* ptrEntity )->OnLoop( dDeltaTime );
}
