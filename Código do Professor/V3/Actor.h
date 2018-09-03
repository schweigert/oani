/**
   \file Actor.h
   \brief Um ator representa qualquer objeto animável na cena

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _ACTOR_NOT_INCLUDED_
#define _ACTOR_NOT_INCLUDED_

#include "Object.h"
#include "Animator.h"

/**
   \class Actor
   \brief Responsavel por construir um objeto do tipo ator<br>

   \sa Object()
   \sa Animator()
*/
class Actor: public Object
{
protected:
    Animator * ptrAnimator; ///< ponteiro para o objeto animador de atributos associado a este ator

public:
    Actor();
    Actor( const Actor & );
    Actor( Actor* );
    ~Actor();

    //virtual void Initialize() {}

    void setAnimator( Animator * );
    /**
      \brief Retorna a referencia ao objeto animador associado a este objeto
      \return ponteiro para o objeto animador
    */
    inline Animator * getAnimator() { return this->ptrAnimator; }

    virtual void OnLoop( double );
};

#endif

