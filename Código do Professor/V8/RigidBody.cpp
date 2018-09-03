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
    this->setGravity( Vector3( 0.0f, -0.2f, 0.0f ));
    this->setMass( 1.0f );
}
/**
  \brief Construtor de clonagem para a classe RigidBody
  Cria uma copia exata de um objeto ja existente
  \param clone Objeto a ser clonado
*/
RigidBody::RigidBody( const RigidBody& clone )
{
    this->ptrEntity    = clone.ptrEntity;
    this->listOfForces = clone.listOfForces;
    this->vGravity     = clone.vGravity;
    this->fMass        = clone.fMass;
}
/**
  \brief Construtor de clonagem para a classe RigidBody
  Cria uma copia exata de um objeto ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
RigidBody::RigidBody( RigidBody* ptrClone )
{
    this->ptrEntity    = ptrClone->ptrEntity;
    this->listOfForces = ptrClone->listOfForces;
    this->vGravity     = ptrClone->vGravity;
    this->fMass        = ptrClone->fMass;
}
/**
   \brief Destrutor dos objetos dinamicos dessa classe
*/
RigidBody::~RigidBody()
{
    for( vector<Force*>::iterator itForce = this->listOfForces.begin(); itForce != this->listOfForces.end(); itForce++ )
        delete (* itForce );
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
   \param ptrForce ponteiro para a nova força associada ao corpo rigido
*/
void RigidBody::addForce( Force * ptrForce )
{
    this->listOfForces.push_back( ptrForce );
}
/**
   \brief Retorna uma força presente no sistema de forças desse corpo rigido
   \param uiIndex indice da posiçao no vetor do sistema de forças a ser retornado
   \return ponteiro para a referida força ou NULL caso indice invalido
*/
Force* RigidBody::getForce( unsigned int uiIndex )
{
    if( uiIndex < this->listOfForces.size() )
        return this->listOfForces[ uiIndex ];
    return NULL;
}
/**
   \brief Retorna uma força presente no sistema de forças desse corpo rigido
   \param strForceID nome da força a ser retornada
   \return ponteiro para a referida força ou NULL caso nome invalido
*/
Force* RigidBody::getForce( string strForceID )
{
    for( vector<Force*>::iterator itForce = this->listOfForces.begin(); itForce != this->listOfForces.end(); itForce++ )
        if( (* itForce )->getID() == strForceID )
            return (* itForce );
    return NULL;
}
/**
   \brief Define o vetor gravidade em uso para este corpo rigido
   \param vGravity novo vetor garvidade
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
    Vector3 vResultingForce;

    for( vector<Force*>::iterator itForce = this->listOfForces.begin(); itForce != this->listOfForces.end(); itForce++ )
            vResultingForce = vResultingForce + (* itForce )->getForce();

    Vector3 vAceleration = vResultingForce / this->fMass,
            vSpeed =


    this->ptrEntity->setTranslate( vTranslate + this->vGravity );

    printf("===> %f %f %f\n", vTranslate.x, vTranslate.y, vTranslate.z);
}
