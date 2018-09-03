#ifndef _Chair_NOT_INCLUDED_
#define _Chair_NOT_INCLUDED_

#include "Object.h"

class Chair: public Object
{
public:
    Chair();
    Chair( const Chair & );
    Chair( Chair* );

    virtual void Initialize();
};

#endif
