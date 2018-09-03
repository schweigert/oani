/**
   \file Entity.cpp
   \brief Implementacao dos metodos da classe Entity

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Agosto, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Entity.h"

/**
  \brief Construtor para a classe Entity
  Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
  em escala canonica.
*/
Entity::Entity()
{
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
	this->setTranslate( clone.vTranslate );
	this->setRotate( clone.vRotate );
	this->setScale( clone.vScale );
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
	this->setScale( ptrClone->vScale );
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
