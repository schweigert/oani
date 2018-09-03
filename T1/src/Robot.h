#ifndef _ROBOT_NOT_INCLUDED_
#define _ROBOT_NOT_INCLUDED_

#include "Actor.h"

class Robot: public Actor
{
public:
    Robot();
    Robot( const Robot & );
    Robot( Robot* );

    virtual void Initialize();
};

#endif
