#include "Animator.h"
#include <stdlib.h>

Animator::Animator( Animator::AnimationType animType ): ptrOwner( NULL ), dAnimationTime( 0.0 ), animationType( animType )
{}

Animator::Animator( const Animator& clone ): dAnimationTime( 0.0 )
{
    this->ptrOwner            = clone.ptrOwner;
    this->animationType       = clone.animationType;
    this->listOfInterpolators = clone.listOfInterpolators;
}

Animator::Animator( Animator* ptrClone ): dAnimationTime( 0.0 )
{
    this->ptrOwner            = ptrClone->ptrOwner;
    this->animationType       = ptrClone->animationType;
    this->listOfInterpolators = ptrClone->listOfInterpolators;
}

Animator::~Animator()
{
    for(vector<Interpolator *>::iterator ptrInterp = this->listOfInterpolators.begin();
        ptrInterp != this->listOfInterpolators.end(); ptrInterp++ )
        delete (* ptrInterp);
}

void Animator::setParent( Entity* ptrOwner )
{
    this->ptrOwner = ptrOwner;

    for(vector<Interpolator *>::iterator ptrInterp = this->listOfInterpolators.begin();
        ptrInterp != this->listOfInterpolators.end(); ptrInterp++ )
        (* ptrInterp )->setParent( this->ptrOwner );
}

void Animator::addInterpolator( Interpolator * ptrInterp )
{
    if( ptrInterp )
        this->listOfInterpolators.push_back( ptrInterp );
}

void Animator::OnLoop( double dDeltaTime )
{
    this->dAnimationTime += dDeltaTime;

    for( vector<Interpolator *>::iterator itInterp = this->listOfInterpolators.begin();
         itInterp != this->listOfInterpolators.end(); itInterp++ )
         {
             (* itInterp )->OnLoop( this->dAnimationTime );
         }
}
