
#include "BoundingVolume.h"

/**
  \brief Construtor padrao para a classe BoundingVolume
  Cria um volume vazio, sem tipo e na origem
  \param bvType tipo do volume delimitador
*/
BoundingVolume::BoundingVolume( Entity * ptrOwner )
{
	this->ptrOwner = ptrOwner;
}
/**
   \brief Construtor de copia para objetos estaticos da classe
   \param clone objeto a ser clonado
*/
BoundingVolume::BoundingVolume( const BoundingVolume& clone )
{
    this->ptrOwner = clone.ptrOwner;
}
/**
   \brief Construtor de copia para objetos dinamicos da classe
   \param ptrClone ponteiro para o objeto a ser clonado
*/
BoundingVolume::BoundingVolume( BoundingVolume * ptrClone )
{
    this->ptrOwner = ptrClone->ptrOwner;
}
