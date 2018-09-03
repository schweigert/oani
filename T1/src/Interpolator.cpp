#include "Interpolator.h"
#include <typeinfo>
#include <string>
#include <stdio.h>


Interpolator::Interpolator()
{}

Interpolator::Interpolator( const Interpolator& clone )
{}

Interpolator::Interpolator( Interpolator* ptrClone )
{}

void Interpolator::addAttribute( PoseAttr ptrPoseAttr )
{
        this->listOfPoseAttr.push_back( ptrPoseAttr );
}

void Interpolator::setParent( Entity* ptrOwner )
{
    this->ptrOwner = ptrOwner;
}
