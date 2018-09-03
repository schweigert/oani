#ifndef _LINEARINTERPOLATOR_NOT_INCLUDED_
#define _LINEARINTERPOLATOR_NOT_INCLUDED_

#include "Interpolator.h"

class LinearInterpolator : public Interpolator
{
public:
    LinearInterpolator();
    LinearInterpolator( const LinearInterpolator & );
    LinearInterpolator( LinearInterpolator* );

    void OnLoop( double );
};

#endif
