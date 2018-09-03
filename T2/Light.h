/**
   \file Light.h
   \brief Descreve um ator do tipo rob�

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _LIGHT_NOT_INCLUDED_
#define _LIGHT_NOT_INCLUDED_

#include "Actor.h"

/**
   \class Light
   \brief Responsavel por construir um ator rob�<br>

   \sa Actor()
*/
class Light: public Actor
{
public:
    Light();
    Light( const Light & );
    Light( Light* );

    virtual void Initialize();
    // virtual void OnLoop();
};

#endif
