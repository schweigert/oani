#ifndef _HOUSE_NOT_INCLUDED_
#define _HOUSE_NOT_INCLUDED_

#include "Object.h"


class House: public Object
{
public:
    House();
    House( const House & );
    House( House* );

    virtual void Initialize();
};

#endif
