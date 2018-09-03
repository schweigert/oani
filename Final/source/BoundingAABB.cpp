
#include "BoundingAABB.h"
#include "BoundingSphere.h"
#include "Entity.h"

#include <stdio.h>
#include <typeinfo>

/**
  \brief Construtor padrao para a classe BoundingAABB
  Cria um volume vazio, sem tipo e na origem
  \param ptrOwner ponteiro para o objeto que contem esse bounding volume
*/
BoundingAABB::BoundingAABB( Entity* ptrOwner ): BoundingVolume( ptrOwner )
{
	this->Dimensions = Vector3::WHITE; // usado para representar um cubo de aresta = 1.0f
}
/**
  \brief Construtor clonagem para objetos da classe BoundingAABB
  \param clone objeto da classe BoundingAABB a ser clonado
*/
BoundingAABB::BoundingAABB( const BoundingAABB& clone ): BoundingVolume( clone )
{
	this->Dimensions = clone.Dimensions;
}
/**
  \brief Construtor clonagem para ponteiros a objetos da classe BoundingAABB
  \param ptrClone ponteiro para o objeto da classe BoundingAABB a ser clonado
*/
BoundingAABB::BoundingAABB( BoundingAABB* ptrClone ): BoundingVolume( ptrClone )
{
	this->Dimensions = ptrClone->Dimensions;
}
/**
  \brief Especifica o valor das dimensoes da caixa orientada do volume delimitador
  \param Dimensions dimensoes da caixa orientada
*/
void BoundingAABB::setDimensions( Vector3 Dimensions )
{
	this->Dimensions = Dimensions;
}
/**
	\brief Determina se o objeto corrente esta colidindo contra outro volume determinado
	\param ptrOtherVolume ponteiro para o objeto volume a ser testado se ha colisao
	\return true caso haja colisao entre os volumes e false caso contrario
*/
bool BoundingAABB::CheckCollision( BoundingVolume * ptrOtherVolume )
{
    if(typeid( ( *ptrOtherVolume ) ).name() == string( "BoundingSphere" ) )
        return this->CheckCollisionAgainstSphere( ( BoundingSphere* )ptrOtherVolume );

    if(typeid( ( *ptrOtherVolume ) ).name() == string( "BoundingAABB" ) )
        return this->CheckCollisionAgainstAABB( ( BoundingAABB* )ptrOtherVolume );

	return false;
}
/**
	\brief Determina se o objeto corrente esta colidindo contra um volume esferico dado
	\param ptrOtherVolume ponteiro para o objeto volume esferico a ser testado se ha colisao
	\return true caso haja colisao entre os volumes e false caso contrario
*/
bool BoundingAABB::CheckCollisionAgainstSphere( BoundingSphere* ptrOtherVolume )
{
    // FALTA IMPLEMENTAR

    return false;
}
/**
	\brief Determina se o objeto corrente esta colidindo contra um volume caixa orientada dada
	\param ptrOtherVolume ponteiro para o objeto volume caixa orientada a ser testada se ha colisao
	\return true caso haja colisao entre os volumes e false caso contrario
*/
bool BoundingAABB::CheckCollisionAgainstAABB( BoundingAABB* ptrOtherVolume )
{
	printf("Testando BoudingAABB...");
	Vector3 minLimit = this->ptrOwner->getTranslate() - this->ptrOwner->getDimensions() * 0.5f,
		    maxLimit = this->ptrOwner->getTranslate() + this->ptrOwner->getDimensions() * 0.5f,
			otherMinLimit = ptrOtherVolume->ptrOwner->getTranslate() - ptrOtherVolume->ptrOwner->getDimensions() * 0.5f,
			otherMaxLimit = ptrOtherVolume->ptrOwner->getTranslate() + ptrOtherVolume->ptrOwner->getDimensions() * 0.5f;

	if( otherMinLimit.x >= minLimit.x && otherMinLimit.x <= maxLimit.x )
	{
		if( otherMinLimit.y >= minLimit.y && otherMinLimit.y <= maxLimit.y )
		{
			if( otherMinLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
			else if( otherMaxLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
		}
		else if( otherMaxLimit.y >= minLimit.y && otherMinLimit.y <= maxLimit.y )
		{
			if( otherMinLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
			else if( otherMaxLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
		}
	}
	else if( otherMaxLimit.x >= minLimit.x && otherMinLimit.x <= maxLimit.x )
	{
		if( otherMinLimit.y >= minLimit.y && otherMinLimit.y <= maxLimit.y )
		{
			if( otherMinLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
			else if( otherMaxLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
		}
		else if( otherMaxLimit.y >= minLimit.y && otherMinLimit.y <= maxLimit.y )
		{
			if( otherMinLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
			else if( otherMaxLimit.z >= minLimit.z && otherMinLimit.z <= maxLimit.z )
			{
				return true;
			}
		}
	}
	return false;
}
