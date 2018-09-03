/**
   \file House.h
   \brief Descreve o modelo para uma casa

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _HOUSE_NOT_INCLUDED_
#define _HOUSE_NOT_INCLUDED_

#include "Object.h"

/**
   \class House
   \brief Responsavel por construir um objeto do tipo casa<br>

   \sa Object()
*/
class House: public Object
{
public:
    House();
    House( const House & );
    House( House* );

    virtual void Initialize();
};

#endif


