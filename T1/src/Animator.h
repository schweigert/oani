#ifndef _ANIMATOR_NOT_INCLUDED_
#define _ANIMATOR_NOT_INCLUDED_

#include "Entity.h"
#include "Interpolator.h"

#include <vector>
using namespace std;


class Animator
{
public:

	enum AnimationType {
		ONCE = 0,
		LOOP
	};

protected:
    Entity *              ptrOwner;
    AnimationType         animationType;
    double                dAnimationTime;
    vector<Interpolator*> listOfInterpolators; 

public:
    Animator( Animator::AnimationType = Animator::ONCE );
    Animator( const Animator & );
    Animator( Animator * );
    ~Animator();

    void setParent( Entity* );

    void OnLoop( double );

    void addInterpolator( Interpolator * );

};

#endif
