#ifndef _Aquarium_NOT_INCLUDED_
#define _Aquarium_NOT_INCLUDED_

#include "Object.h"

class Aquarium: public Object
{
public:
    Aquarium();
    Aquarium( const Aquarium & );
    Aquarium( Aquarium* );

    virtual void Initialize();
};

#endif
