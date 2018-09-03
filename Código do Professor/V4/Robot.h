/**
   \file Robot.h
   \brief Descreve um ator do tipo robô

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _ROBOT_NOT_INCLUDED_
#define _ROBOT_NOT_INCLUDED_

#include "Actor.h"

/**
   \class Robot
   \brief Responsavel por construir um ator robô<br>

   \sa Actor()
*/
class Robot: public Actor
{
public:
    Robot();
    Robot( const Robot & );
    Robot( Robot* );

    virtual void Initialize();
};

#endif
