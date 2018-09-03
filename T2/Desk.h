#ifndef _Desk_NOT_INCLUDED_
#define _Desk_NOT_INCLUDED_

#include "Object.h"

class Desk: public Object
{
public:
    Desk();
    Desk( const Desk & );
    Desk( Desk* );

    virtual void Initialize();
};

#endif
