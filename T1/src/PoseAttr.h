#ifndef _POSEATTR_NOT_INCLUDED_
#define _POSEATTR_NOT_INCLUDED_

#include "Vector3.h"

class Entity;


class PoseAttr
{
public:

	enum AttrName {
		TRANSLATE = 0,
		ROTATE,
		SCALE
	};

protected:
    PoseAttr::AttrName attrName;
    double             dAttrTime;
    Vector3            Value;

public:
    PoseAttr( Vector3, double, PoseAttr::AttrName );

    void setTime( double );

    inline double getTime() { return this->dAttrTime; }

    inline PoseAttr::AttrName getName() { return this->attrName; }

    void setValue( Vector3 );

    inline Vector3 getValue() { return this->Value; }

    void updateParent( Entity * );
};

#endif
