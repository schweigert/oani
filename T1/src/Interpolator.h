#ifndef _INTERPOLATOR_NOT_INCLUDED_
#define _INTERPOLATOR_NOT_INCLUDED_

#include "Entity.h"
#include "PoseAttr.h"

#include <vector>
using namespace std;


class Interpolator
{
protected:
    Entity *         ptrOwner;
    vector<PoseAttr> listOfPoseAttr;

    void updateParent( Entity * );

public:
    Interpolator();
    Interpolator( const Interpolator & );
    Interpolator( Interpolator * );

    void setParent( Entity * );
    void addAttribute( PoseAttr );

    virtual void OnLoop( double ) = 0;
};

#endif
