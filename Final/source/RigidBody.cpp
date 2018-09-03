#include "RigidBody.h"
#include "Application.h"
#include "Entity.h"
#include "BoundingAABB.h"
#include "BoundingSphere.h"

#include <stdio.h>
#include <math.h>

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
   \brief Associa um objeto a receber os efeitos da simula�ao de corpos rigidos
   \param ptrEntity ponteiro para o objeto-pai desse corpo rigido
*/
void RigidBody::attach( Entity * ptrEntity )
{
    this->ptrEntity = ptrEntity;
}
/**
   \brief Adiciona uma nova for�a ao sistema de for�as desse corpo rigido
   \param vForce nova for�a associada ao corpo rigido
*/
void RigidBody::addForce( Vector3 vForce )
{
    this->vForce = this->vForce + vForce;
}
/**
   \brief Define a for�a gravitacional aplicada sobre este corpo rigido
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
    if( fMass > 0.0f )  // previne a especifica�ao de massa negativa ou nula
        this->fMass = fMass;
}
/**
   \brief Calcula as for�as envolvidas nesse corpo rigido e atualiza o objeto associado
*/
void RigidBody::OnLoop( double dDeltaTime )
{

    // Atenuação por atrito com o ar

    Vector3 newForce = this->vForce;
    newForce.y = 0;
    float densidade = this->fMass / (ptrBoundingVolume->fRadius + 0.1);
    float fatorDePerca = 1/densidade;

    this->vForce = this->vForce - newForce*fatorDePerca*dDeltaTime;

    // Algoritmo restante

    this->vForce = this->vForce + this->vGravity;
    Vector3 vAcceleration = this->vForce * (1.0f / this->fMass);
    this->vSpeed = this->vSpeed + vAcceleration * dDeltaTime;

    /*
    if( this->ptrBoundingVolume )
    {
        RigidBody * RBref;


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
                    if( RBref->ptrBoundingVolume && this->ptrBoundingVolume->CheckCollision( RBref->ptrBoundingVolume )) // ocorreu colisao?
                    {
                        // para efeito de simplifica��o caso haja colisao as velocidades sao simplesmente trocadas
                        // ao inves disso, calculo de reflexoes dos vetores seria uma alternativa mais realista
                        Vector3 tempVelocity = this->vSpeed;
                        this->vSpeed = RBref->vSpeed;
                        RBref->vSpeed = tempVelocity;

                        // Troca as forças

                        Vector3 tempForce = this->vForce;
                        this->vForce = RBref->vForce;
                        RBref->vForce = tempForce;


                    }
                }
           }

        // Colisão com o chão
        {
          Vector3 position = this->ptrEntity->getTranslate();

          float distChao = position.y;
          float raio = ptrBoundingVolume->fRadius;

          // Verifica a colisão
          if( distChao - raio <= 0.0 ){
            printf("Colidiu com o chão\n");

            // Aplica a penalidade
            ptrEntity->setTranslate(ptrEntity->getTranslate()+Vector3(0,raio - distChao,0));

            // Aplica a velocidade com 10% de perda
            Vector3 tempVelocity = this->vSpeed;
            this->vSpeed = Vector3(tempVelocity.x,-tempVelocity.y*0.5f,tempVelocity.z) * 0.9f;

            // Altera o sistema de força
            Vector3 tempForce = this->vForce;
            this->vForce = Vector3(tempForce.x, 0, tempForce.z) *0.8f;
          }
        }

        // Distância Parede 1
        {
          Vector3 position = this->ptrEntity->getTranslate();

          float dist = position.x;
          float raio = ptrBoundingVolume->fRadius;

          // Verifica a colisão
          if( dist - raio <= 0.0 ){
            printf("Colidiu com a parede 1\n");

            // Aplica a penalidade
            ptrEntity->setTranslate(ptrEntity->getTranslate()+Vector3(raio - dist,0,0));

            // Aplica a velocidade com 10% de perda
            Vector3 tempVelocity = this->vSpeed;
            this->vSpeed = Vector3(-tempVelocity.x*0.5f,tempVelocity.y*0.5f,tempVelocity.z);

            // Altera o sistema de força
            Vector3 tempForce = this->vForce;
            this->vForce = Vector3(0, tempForce.y, tempForce.z) *0.8f;
          }
        }

        // Distância Parede 2
        {
          Vector3 position = this->ptrEntity->getTranslate();

          float dist = position.z;
          float raio = ptrBoundingVolume->fRadius;

          // Verifica a colisão
          if( dist - raio <= 0.0 ){
            printf("Colidiu com a parede 2\n");

            // Aplica a penalidade
            ptrEntity->setTranslate(ptrEntity->getTranslate()+Vector3(raio - dist,0,0));

            // Aplica a velocidade com 10% de perda
            Vector3 tempVelocity = this->vSpeed;
            this->vSpeed = Vector3(tempVelocity.x*0.5f,tempVelocity.y*0.5f,-tempVelocity.z);

            // Altera o sistema de força
            Vector3 tempForce = this->vForce;
            this->vForce = Vector3(tempForce.x, tempForce.y, 0) *0.8f;
          }
        }




    }

    */

    Vector3 vPosition = this->ptrEntity->getTranslate();
    vPosition = vPosition + this->vSpeed * dDeltaTime + vAcceleration * dDeltaTime * dDeltaTime * 0.5f;
    this->ptrEntity->setTranslate( vPosition );

    //printf("===> %f %f %f\n", vPosition.x, vPosition.y, vPosition.z);
}
/**
    \brief Cria um volume esferico de delimita��o
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
    \brief Cria um volume AABB de delimita��o
*/
void RigidBody::setBoundingAABB()
{
    this->ptrBoundingVolume = new BoundingAABB( this->ptrEntity );
    Vector3 dimensions = this->ptrEntity->getDimensions();
    (( BoundingAABB* )this->ptrBoundingVolume )->setDimensions( dimensions );
}
