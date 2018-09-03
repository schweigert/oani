
#include "BoundingSphere.h"
#include "BoundingAABB.h"
#include "Entity.h"

#include <typeinfo>
#include <stdio.h>

/**
  \brief Construtor padrao para a classe BoundingSphere
  Cria um volume vazio, sem tipo e na origem
  \param ptrOwner ponteiro para o objeto que contem esse bounding volume
*/
BoundingSphere::BoundingSphere( Entity* ptrOwner ): BoundingVolume( ptrOwner )
{
	this->fRadius = 1.0f;
}
/**
  \brief Construtor clonagem para objetos da classe BoundingSphere
  \param clone objeto da classe BoundingSphere a ser clonado
*/
BoundingSphere::BoundingSphere( const BoundingSphere& clone ): BoundingVolume( clone )
{
	this->fRadius = clone.fRadius;
}
/**
  \brief Construtor clonagem para ponteiros a objetos da classe BoundingSphere
  \param ptrClone ponteiro para o objeto da classe BoundingSphere a ser clonado
*/
BoundingSphere::BoundingSphere( BoundingSphere* ptrClone ): BoundingVolume( ptrClone )
{
	this->fRadius = ptrClone->fRadius;
}
/**
  \brief Especifica o valor do raio da esfera do volume delimitador
  \param fRadius valor do raio da esfera
*/
void BoundingSphere::setRadius( float fRadius )
{
	this->fRadius = fRadius;
}
/**
	\brief Determina se o objeto corrente esta colidindo contra outro volume determinado
	\param ptrOtherVolume ponteiro para o objeto volume a ser testado se ha colisao
	\return true caso haja colisao entre os volumes e false caso contrario
*/
bool BoundingSphere::CheckCollision( BoundingVolume * ptrOtherVolume )
{
    if( !ptrOtherVolume )
			return false;

    switch( ptrOtherVolume->getType() )
    {
    case BoundingVolume::SPHERE:
        return this->CheckCollisionAgainstSphere( ( BoundingSphere* )ptrOtherVolume );

    case BoundingVolume::AABB:
        return this->CheckCollisionAgainstAABB( ( BoundingAABB* )ptrOtherVolume );
    }
	return false;
}
/**
	\brief Determina se o objeto corrente esta colidindo contra um volume esferico dado
	\param ptrOtherVolume ponteiro para o objeto volume esferico a ser testado se ha colisao
	\return true caso haja colisao entre os volumes e false caso contrario
*/
bool BoundingSphere::CheckCollisionAgainstSphere( BoundingSphere* ptrOtherVolume )
{
		// printf("Testando Sphere...");
    Vector3 A = this->ptrOwner->getTranslate(),
            B = ptrOtherVolume->ptrOwner->getTranslate();
    float rA = this->fRadius, rB = ptrOtherVolume->fRadius;
		// printf("Sphere vs Sphere... %f %f %f %f <-> %f %f %f %f\n", A.x, A.y, A.z, rA, B.x, B.y, B.z, rB );

	return( ( this->ptrOwner->getTranslate() - ptrOtherVolume->ptrOwner->getTranslate() ).Length() <=
            ( this->fRadius + ptrOtherVolume->fRadius ) );
}
/**
	\brief Determina se o objeto corrente esta colidindo contra um volume caixa orientada dada
	\param ptrOtherVolume ponteiro para o objeto volume caixa orientada a ser testada se ha colisao
	\return true caso haja colisao entre os volumes e false caso contrario
*/
bool BoundingSphere::CheckCollisionAgainstAABB( BoundingAABB* ptrOtherVolume )
{
    // FALTA IMPLEMENTAR

    return false;
}
