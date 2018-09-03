#include "PrimitiveGL.h"
#include <GL/glut.h>


PrimitiveGL::PrimitiveGL( PrimitiveGL::PrimitiveType oType ): Entity(),
    dSize( 1.0 ), dHeight( 1.0 ), iSlices( 10 ), iStacks( 10 )
{
    this->oType  = oType;
    this->vColor = Vector3::WHITE;
}


PrimitiveGL::PrimitiveGL( const PrimitiveGL& clone ): Entity( clone )
{
    this->oType   = clone.oType;
    this->vColor  = clone.vColor;
    this->dSize   = clone.dSize;
    this->dHeight = clone.dHeight;
    this->iSlices = clone.iSlices;
    this->iStacks = clone.iStacks;
}


PrimitiveGL::PrimitiveGL( PrimitiveGL* ptrClone ): Entity( ptrClone )
{
    this->oType   = ptrClone->oType;
    this->vColor  = ptrClone->vColor;
    this->dSize   = ptrClone->dSize;
    this->dHeight = ptrClone->dHeight;
    this->iSlices = ptrClone->iSlices;
    this->iStacks = ptrClone->iStacks;
}


void PrimitiveGL::setColor( Vector3 color )
{
   this->vColor = color;
}

void PrimitiveGL::setSize( GLdouble dSize )
{
    this->dSize = dSize;
}

void PrimitiveGL::setHeight( GLdouble dHeight )
{
    this->dHeight = dHeight;
}

void PrimitiveGL::setResolution( GLint iSlices, GLint iStacks )
{
    this->iSlices = iSlices;
    this->iStacks = iStacks;
}

void PrimitiveGL::OnRender()
{


    glColor3f( this->vColor.x, this->vColor.y, this->vColor.z );

    glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
    glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );
    glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
    glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );
    glScalef( this->vScale.x, this->vScale.y, this->vScale.z );

    switch( this->oType )
    {
    case PrimitiveGL::SPHERE:
        glutSolidSphere( this->dSize, this->iSlices, this->iStacks );
        break;
    case PrimitiveGL::CUBE:
        glutSolidCube( this->dSize );
        break;
    case PrimitiveGL::CONE:
        glutSolidCone( this->dSize, this->dHeight, this->iSlices, this->iStacks );
        break;
    case PrimitiveGL::TORUS:
        glutSolidTorus( this->dSize, this->dHeight, this->iSlices, this->iStacks );
        break;
    case PrimitiveGL::TEAPOT:
        glutSolidTeapot( this->dSize );
        break;
    case PrimitiveGL::DODECAHEDRON:
        glutSolidDodecahedron();
        break;
    case PrimitiveGL::OCTAHEDRON:
        glutSolidOctahedron();
        break;
    case PrimitiveGL::ICOSAHEDRON:
        glutSolidIcosahedron();
        break;
    case PrimitiveGL::TETRAHEDRON:
        glutSolidTetrahedron();
        break;
    }

}

void PrimitiveGL::OnLoop( double dDeltaTime )
{}
