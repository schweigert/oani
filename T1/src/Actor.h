#ifndef _ACTOR_NOT_INCLUDED_
#define _ACTOR_NOT_INCLUDED_

#include "Object.h"
#include "Animator.h"


class Actor: public Object
{
protected:
    Animator * ptrAnimator;

public:
    Actor();
    Actor( const Actor & );
    Actor( Actor* );
    ~Actor();


    void setAnimator( Animator * );

    inline Animator * getAnimator() { return this->ptrAnimator; }

    virtual void OnLoop( double );
};

#endif
