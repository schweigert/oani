
/**
   \file Fence.h
   \brief Descreve o modelo para uma cerca

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _FENCE_NOT_INCLUDED_
#define _FENCE_NOT_INCLUDED_

#include "Object.h"

/**
   \class Fence
   \brief Responsavel por construir um objeto do tipo cerca<br>

   \sa Object()
*/
class Fence: public Object
{
public:
    Fence();
    Fence( const Fence & );
    Fence( Fence* );

    virtual void Initialize();
};

#endif
