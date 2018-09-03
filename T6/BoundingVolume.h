
#ifndef _BOUNDING_VOLUME_H_
#define _BOUNDING_VOLUME_H_

#include "Vector3.h"

class Entity;

/**
   \class BoundingVolume
   \brief Classe que tem por objetivo criar um volume delimitador para efeito de simplificacao geometria para testes geometricos
*/
class BoundingVolume
{
public:
    enum VolumeType
    {
        NONE = 0,
        SPHERE,
        AABB
    };

protected:
    Entity * ptrOwner;  ///< ponteiro para o objeto que contem este volume delimitador

public:
    BoundingVolume( Entity* );
    BoundingVolume( const BoundingVolume& );
    BoundingVolume( BoundingVolume* );

    float fRadius;  ///< raio da esfera do volume delimitador


    /**
     \brief Determina se o objeto corrente esta colidindo contra outro volume determinado
     \param ptrOtherVolume ponteiro para o objeto volume a ser testado se ha colisao
     \return true caso haja colisao entre os volumes e false caso contrario
    */
    virtual bool CheckCollision( BoundingVolume * ) { return false; }
    /**
       \brief Retorna o tipo de bounding volume
       \return um dos rotulos do tipo enumerado
    */
    virtual VolumeType getType() { return BoundingVolume::NONE; }

    /**
      brief Retorna a entidade que o rigidBody controla.
    */
    inline Entity* getEntity() {return ptrOwner;}
};

#endif
