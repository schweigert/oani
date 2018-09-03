
#ifndef _BOUNDING_AABB_H_
#define _BOUNDING_AABB_H_

#include <string>
using namespace std;

#include "BoundingVolume.h"

class BoundingSphere; // declaracao FORWARD para a classe

/**
   \class BoundingAABB
   \brief Especializacao da classe BoundingVolume para delimitadores em formato caixa orientada aos eixos
*/
class BoundingAABB: public BoundingVolume
{
protected:
	Vector3 Dimensions;  ///< dimensoes da caixa orientada delimitadora

private:
	bool CheckCollisionAgainstSphere( BoundingSphere* );
	bool CheckCollisionAgainstAABB( BoundingAABB* );

public:
	   BoundingAABB( Entity* );
	   BoundingAABB( const BoundingAABB& );
	   BoundingAABB( BoundingAABB* );

       /**
           \brief Retorna o tipo de bounding volume
           \return um dos rotulos do tipo enumerado
       */
       virtual VolumeType getType() { return BoundingVolume::AABB; }

	   void setDimensions( Vector3 );
	   /**
	     \brief Retorna o valor das dimensoes da caixa do volume
		 \return valor das dimensoes da caixa
	   */
	   inline Vector3 getDimensions() { return this->Dimensions; }

	   /**
	     \brief Determina se o objeto corrente esta colidindo contra outro volume determinado
		 \param ptrOtherVolume ponteiro para o objeto volume a ser testado se ha colisao
		 \return true caso haja colisao entre os volumes e false caso contrario
	   */
	   virtual bool CheckCollision( BoundingVolume * );
};

#endif
