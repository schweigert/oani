/**
   \file RigidBody.cpp
	\brief Implementacao dos metodos da classe RigidBody declarados em RigidBody.h

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
    Editado por Gustavo Diel
	Abril, 2017. Universidade do Estado de Santa Catarina (UDESC)
*/
#include "RigidBody.h"
#include "Application.h"
#include "Entity.h"
#include "BoundingAABB.h"
#include "BoundingSphere.h"

#include <stdio.h>

/**
   \brief Construtor default para a classe RigidBody
*/
RigidBody::RigidBody(): ptrEntity( NULL ), ptrBoundingVolume( NULL )
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

    switch( clone.ptrBoundingVolume->getType() )
    {
    case BoundingVolume::NONE:
        break;

    case BoundingVolume::SPHERE:
        this->ptrBoundingVolume = new BoundingSphere( ( BoundingSphere* )clone.ptrBoundingVolume );
        break;

    case BoundingVolume::AABB:
        this->ptrBoundingVolume = new BoundingAABB( ( BoundingAABB* )clone.ptrBoundingVolume );
        break;
    }
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

    switch( ptrClone->ptrBoundingVolume->getType() )
    {
    case BoundingVolume::NONE:
        break;

    case BoundingVolume::SPHERE:
        this->ptrBoundingVolume = new BoundingSphere( ( BoundingSphere* )ptrClone->ptrBoundingVolume );
        break;

    case BoundingVolume::AABB:
        this->ptrBoundingVolume = new BoundingAABB( ( BoundingAABB* )ptrClone->ptrBoundingVolume );
        break;
    }
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

    if( this->ptrBoundingVolume )
    {
        RigidBody * RBref;
        //#define USE_BUGADO
        #ifndef USE_BUGADO

        // Fix
        unsigned int listSize =ptrEntity->getApplicationRef()->getRigidBodies().size();
        for( unsigned int i = 0; i < listSize; i++ )
           {
                Entity* ent = ptrEntity->getApplicationRef()->getRigidBodies()[i];
                if (!ent) continue;
                RBref = ent->getRigidBody();
                if (!RBref) continue;
                if( RBref != this ) // previne teste de colisao contra si proprio
                {
                    printf("kkkkkkkkkkkkkk\n");
                    if( RBref->ptrBoundingVolume && this->ptrBoundingVolume->CheckCollision( RBref->ptrBoundingVolume )) // ocorreu colisao?
                    {
                        // para efeito de simplificação caso haja colisao as velocidades sao simplesmente trocadas
                        // ao inves disso, calculo de reflexoes dos vetores seria uma alternativa mais realista
                        printf("oasiasodiasd\n");
                        Vector3 tempVelocity = this->vSpeed;
                        this->vSpeed = RBref->vSpeed * 0.9f;
                        RBref->vSpeed = tempVelocity * 0.9f;
                    }
                }
           }
           #else
        for( vector<Entity*>::iterator itRBody = this->ptrEntity->getApplicationRef()->getRigidBodies().begin();
           itRBody != this->ptrEntity->getApplicationRef()->getRigidBodies().end(); itRBody++ )
           {
                RBref = (* itRBody )->getRigidBody();
                if( RBref && RBref != this ) // previne teste de colisao contra si proprio
                {
                    if( RBref->ptrBoundingVolume && this->ptrBoundingVolume->CheckCollision( RBref->ptrBoundingVolume )) // ocorreu colisao?
                    {
                        // para efeito de simplificação caso haja colisao as velocidades sao simplesmente trocadas
                        // ao inves disso, calculo de reflexoes dos vetores seria uma alternativa mais realista

                        Vector3 tempVelocity = this->vSpeed;
                        this->vSpeed = RBref->vSpeed * 0.9f;
                        RBref->vSpeed = tempVelocity * 0.9f;
                    }
                }
           }
           #endif // USE_BUGADO
    }

    Vector3 vPosition = this->ptrEntity->getTranslate();
    vPosition = vPosition + this->vSpeed * dDeltaTime + vAcceleration * dDeltaTime * dDeltaTime * 0.5f;
    this->ptrEntity->setTranslate( vPosition );

    //printf("===> %f %f %f\n", vPosition.x, vPosition.y, vPosition.z);
}
/**
    \brief Cria um volume esferico de delimitação
*/
void RigidBody::setBoundingSphere()
{
    this->ptrBoundingVolume = new BoundingSphere( this->ptrEntity );
    Vector3 dimensions = this->ptrEntity->getDimensions();

    float fRadius = dimensions.x;
    if( fRadius < dimensions.y ) fRadius = dimensions.y;
    if( fRadius < dimensions.z ) fRadius = dimensions.z;
    printf("Adding BSphere: Radius = %f\n", fRadius);
    (( BoundingSphere* )this->ptrBoundingVolume )->setRadius( fRadius );
}
/**
    \brief Cria um volume AABB de delimitação
*/
void RigidBody::setBoundingAABB()
{
    this->ptrBoundingVolume = new BoundingAABB( this->ptrEntity );
    Vector3 dimensions = this->ptrEntity->getDimensions();
    (( BoundingAABB* )this->ptrBoundingVolume )->setDimensions( dimensions );
}
