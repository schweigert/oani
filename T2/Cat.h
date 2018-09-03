/**
   \file Cat.h
   \brief Descreve um ator do tipo rob�

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _Cat_NOT_INCLUDED_
#define _Cat_NOT_INCLUDED_

#include "Actor.h"

/**
   \class Cat
   \brief Responsavel por construir um ator rob�<br>

   \sa Actor()
*/
class Cat: public Actor
{
public:
    Cat();
    Cat( const Cat & );
    Cat( Cat* );

    virtual void Initialize();
};

#endif
