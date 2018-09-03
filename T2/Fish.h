/**
   \file Fish.h
   \brief Descreve o modelo para um Fisha

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _Fish_NOT_INCLUDED_
#define _Fish_NOT_INCLUDED_

#include "Joint.h"

/**
   \class Fish
   \brief Responsavel por construir um Fisha<br>

   \sa Object()
*/
class Fish: public Joint
{


public:
    Fish();
    Fish( const Fish & );
    Fish( Fish* );

    virtual void Initialize();

};


class FishTail : public Joint {

public:
    FishTail();
    FishTail( const FishTail & );
    FishTail( FishTail* );

    virtual void Initialize();


};

#endif
