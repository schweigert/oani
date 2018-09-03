
#ifndef _FENCE_NOT_INCLUDED_
#define _FENCE_NOT_INCLUDED_

#include "Object.h"


class Fence: public Object
{
public:
    Fence();
    Fence( const Fence & );
    Fence( Fence* );

    virtual void Initialize();
};

#endif
