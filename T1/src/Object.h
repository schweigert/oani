
#ifndef _OBJECT_NOT_INCLUDED_
#define _OBJECT_NOT_INCLUDED_

#include "Entity.h"
#include "PrimitiveGL.h"
#include <vector>
using namespace std;


class Object: public Entity
{
protected:
	vector<Entity*> listOfEntities;

public:
    Object();
    Object( const Object & );
    Object( Object* );
    ~Object();


    virtual void Initialize() = 0;

    virtual void OnRender();
    virtual void OnLoop( double );
};

#endif
