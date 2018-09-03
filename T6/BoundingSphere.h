
#ifndef _BOUNDING_SPHERE_H_
#define _BOUNDING_SPHERE_H_

#include <string>
using namespace std;

#include "BoundingVolume.h"

class BoundingAABB; // declaracao FORWARD para a classe

/**
   \class BoundingSphere
   \brief Especializacao da classe BoundingVolume para delimitadores em formato esferico
*/
class BoundingSphere: public BoundingVolume
{
protected:

private:
	bool CheckCollisionAgainstSphere( BoundingSphere* );
	bool CheckCollisionAgainstAABB( BoundingAABB* );

public:
	   BoundingSphere( Entity* );
	   BoundingSphere( const BoundingSphere& );
	   BoundingSphere( BoundingSphere* );

       /**
           \brief Retorna o tipo de bounding volume
           \return um dos rotulos do tipo enumerado
       */
       virtual VolumeType getType() { return BoundingVolume::SPHERE; }

	   void setRadius( float );
	   /**
	     \brief Retorna o valor do raio da esfera do volume
		 \return valor do raio
	   */
	   inline float getRadius() { return this->fRadius; }

	   /**
	     \brief Determina se o objeto corrente esta colidindo contra outro volume determinado
		 \param ptrOtherVolume ponteiro para o objeto volume a ser testado se ha colisao
		 \return true caso haja colisao entre os volumes e false caso contrario
	   */
	   virtual bool CheckCollision( BoundingVolume * );

};

#endif
