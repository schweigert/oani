#include "LinearInterpolator.h"
#include "PoseAttr.h"
#include <stdio.h>
#include <typeinfo>
#include <string>
#include <stdio.h>

LinearInterpolator::LinearInterpolator(): Interpolator()
{}

LinearInterpolator::LinearInterpolator( const LinearInterpolator& clone ): Interpolator( clone )
{}

LinearInterpolator::LinearInterpolator( LinearInterpolator* ptrClone ): Interpolator( ptrClone )
{}

void LinearInterpolator::OnLoop( double dAnimationTime )
{
    for( unsigned int uiCounter = 0; uiCounter < this->listOfPoseAttr.size()-1; uiCounter++ )
    {

        if( dAnimationTime >= this->listOfPoseAttr[ uiCounter ].getTime() &&
            dAnimationTime <= this->listOfPoseAttr[ uiCounter+1 ].getTime() )
        {
            double dFactor = ( dAnimationTime - this->listOfPoseAttr[ uiCounter ].getTime() ) /
                             ( this->listOfPoseAttr[ uiCounter+1 ].getTime() - this->listOfPoseAttr[ uiCounter ].getTime());

            PoseAttr oTweenAttr( this->listOfPoseAttr[ uiCounter ].getValue() * ( 1.0 - dFactor ) +
                                 this->listOfPoseAttr[ uiCounter+1 ].getValue() * dFactor, 0.0,
                                 this->listOfPoseAttr[ uiCounter ].getName() );
            oTweenAttr.updateParent( this->ptrOwner );
        }
    }
}
