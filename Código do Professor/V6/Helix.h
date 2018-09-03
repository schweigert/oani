/**
   \file Helix.h
   \brief Descreve o modelo para uma helice

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _HELIX_NOT_INCLUDED_
#define _HELIX_NOT_INCLUDED_

#include "Actor.h"

/**
   \class Helix
   \brief Responsavel por construir um objeto do tipo helice<br>

   \sa Object()
*/
class Helix: public Actor
{
public:
    Helix();
    Helix( const Helix & );
    Helix( Helix* );

    virtual void Initialize();
};

#endif
