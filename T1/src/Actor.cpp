#include "Actor.h"
#include <stdlib.h>


Actor::Actor(): ptrAnimator( NULL )
{
}

Actor::Actor( const Actor& clone )
{
	this->ptrAnimator = new Animator( clone.ptrAnimator );
}

Actor::Actor( Actor* ptrClone )
{
	this->ptrAnimator = new Animator( ptrClone->ptrAnimator );
}

 Actor::~Actor()
 {
     if( this->ptrAnimator)
        delete this->ptrAnimator;
    this->ptrAnimator = NULL;
 }

void Actor::setAnimator( Animator* ptrAnimator )
{
    if( ptrAnimator )
    {
        this->ptrAnimator = ptrAnimator;
        this->ptrAnimator->setParent( this );
    }
}

void Actor::OnLoop( double dDeltaTime )
{
    if( this->ptrAnimator )
        this->ptrAnimator->OnLoop( dDeltaTime );

    Object::OnLoop( dDeltaTime );
}
