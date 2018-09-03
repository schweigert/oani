#include "PoseAttr.h"
#include "Entity.h"


PoseAttr::PoseAttr( Vector3 Value, double dAttrTime, PoseAttr::AttrName attrName )
{
    this->setValue( Value );
    this->attrName = attrName;
    this->setTime( dAttrTime );
}

void PoseAttr::setTime( double dAttrTime )
{
    this->dAttrTime = dAttrTime;
}

void PoseAttr::updateParent( Entity * ptrParent )
{
    if( !ptrParent )
        return;

    switch( this->attrName )
    {
    case PoseAttr::TRANSLATE: ptrParent->setTranslate( this->Value ); break;
    case PoseAttr::ROTATE:    ptrParent->setRotate( this->Value );    break;
    case PoseAttr::SCALE:     ptrParent->setScale( this->Value );     break;
    }
}

void PoseAttr::setValue( Vector3 Value )
{
    this->Value = Value;
}
