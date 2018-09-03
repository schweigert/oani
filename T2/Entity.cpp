/**
   \file Entity.cpp
   \brief Implementacao dos metodos da classe Entity

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Agosto, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Entity.h"
#include <stdlib.h>

/**
  \brief Construtor para a classe Entity
  Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
  em escala canonica.
*/
Entity::Entity()
{
   this->setTranslate( Vector3::ZERO );
   this->setRotate( Vector3::ZERO );
   this->setRotatePivot( Vector3::ZERO );
   this->setScale( Vector3( 1.0f, 1.0f, 1.0f, 0.0f ) );
   this->setPivot( Vector3::ZERO );
}
/**
  \brief Construtor de clonagem para a classe Entity
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
Entity::Entity( const Entity& clone )
{
	this->setTranslate( clone.vTranslate );
	this->setRotate( clone.vRotate );
	this->setRotatePivot( clone.vRotatePivot );
	this->setScale( clone.vScale );
	this->setPivot( clone.vPivot );
}
/**
  \brief Construtor de clonagem para a classe Entity a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
Entity::Entity( Entity* ptrClone )
{
	this->setTranslate( ptrClone->vTranslate );
	this->setRotate( ptrClone->vRotate );
	this->setRotatePivot( ptrClone->vRotatePivot );
	this->setScale( ptrClone->vScale );
	this->setPivot( ptrClone->vPivot );
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
  \brief Define orientacao espacial para o objeto (em relaçao ao pivot)
  \param vec coordenadas do vetor orientacao
*/
void Entity::setRotatePivot( Vector3 vec )
{
   this->vRotatePivot = vec;
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
  \brief Define a posição do pivot do objeto (em coordenadas locais)
  \param vec coordenadas para o pivot do objeto
*/
void Entity::setPivot( Vector3 vec )
{
   this->vPivot = vec;
}
