/**
   \file RigidBody.cpp
	\brief Implementacao dos metodos da classe RigidBody declarados em RigidBody.h

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Abril, 2017. Universidade do Estado de Santa Catarina (UDESC)
*/
#include "RigidBody.h"
#include "Entity.h"

#include <stdio.h>

/**
   \brief Construtor default para a classe RigidBody
*/
RigidBody::RigidBody(): ptrEntity( NULL )
{
    this->setMass( 1.0f );
    this->vForce = Vector3::ZERO;
    this->setGravity( Vector3( 0.0f, -9.8f, 0.0f ));
}
/**
  \brief Construtor de clonagem para a classe RigidBody
  Cria uma copia exata de um objeto ja existente
  \param clone Objeto a ser clonado
*/
RigidBody::RigidBody( const RigidBody& clone )
{
    this->ptrEntity = clone.ptrEntity;
    this->fMass     = clone.fMass;
    this->vForce    = clone.vForce;
    this->vGravity  = clone.vGravity;
}
/**
  \brief Construtor de clonagem para a classe RigidBody
  Cria uma copia exata de um objeto ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
RigidBody::RigidBody( RigidBody* ptrClone )
{
    this->ptrEntity = ptrClone->ptrEntity;
    this->fMass     = ptrClone->fMass;
    this->vForce    = ptrClone->vForce;
    this->vGravity  = ptrClone->vGravity;
}
/**
   \brief Associa um objeto a receber os efeitos da simulaçao de corpos rigidos
   \param ptrEntity ponteiro para o objeto-pai desse corpo rigido
*/
void RigidBody::attach( Entity * ptrEntity )
{
    this->ptrEntity = ptrEntity;
}
/**
   \brief Adiciona uma nova força ao sistema de forças desse corpo rigido
   \param vForce nova força associada ao corpo rigido
*/
void RigidBody::addForce( Vector3 vForce )
{
    this->vForce = this->vForce + vForce;
}
/**
   \brief Define a força gravitacional aplicada sobre este corpo rigido
   \param vGravity vetor gravidade
*/
void RigidBody::setGravity( Vector3 vGravity )
{
    this->vGravity = vGravity;
}
/**
   \brief Especifica o valor da massa do corpo rigido
   \param fMass quantidade de massa do corpo rigido
*/
void RigidBody::setMass( float fMass )
{
    if( fMass > 0.0f )  // previne a especificaçao de massa negativa ou nula
        this->fMass = fMass;
}
/**
   \brief Calcula as forças envolvidas nesse corpo rigido e atualiza o objeto associado
*/
void RigidBody::OnLoop( double dDeltaTime )
{
    this->vForce = this->vForce + this->vGravity;

    Vector3 vAcceleration = this->vForce * (1.0f / this->fMass);

    this->vSpeed = this->vSpeed + vAcceleration * dDeltaTime;

    Vector3 vPosition = this->ptrEntity->getTranslate();

    vPosition = vPosition + this->vSpeed * dDeltaTime + vAcceleration * dDeltaTime * dDeltaTime * 0.5f;

    this->ptrEntity->setTranslate( vPosition );

    //printf("===> %f %f %f\n", vPosition.x, vPosition.y, vPosition.z);
}
