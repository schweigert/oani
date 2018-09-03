#ifndef _Table_NOT_INCLUDED_
#define _Table_NOT_INCLUDED_

#include "Object.h"

class Table: public Object
{
public:
    Table();
    Table( const Table & );
    Table( Table* );

    virtual void Initialize();
};

#endif
