#ifndef _TREE_NOT_INCLUDED_
#define _TREE_NOT_INCLUDED_

#include "Object.h"

class Tree: public Object
{
public:
    Tree();
    Tree( const Tree & );
    Tree( Tree* );

    virtual void Initialize();
};

#endif
