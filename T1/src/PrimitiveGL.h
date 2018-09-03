#ifndef _PRIMITIVE_NOT_INCLUDED_
#define _PRIMITIVE_NOT_INCLUDED_

#include "Entity.h"
#include <GL/gl.h>


class PrimitiveGL: public Entity
{
public:
    enum PrimitiveType {
        SPHERE = 0,
        CUBE,
        CONE,
        TORUS,        /// toroide = rosquinha
        TEAPOT,       /// bule de cha
        DODECAHEDRON, /// poligono de 12 lados
        OCTAHEDRON,   /// poligono de 8 lados
        ICOSAHEDRON,  /// poligono de 20 lados
        TETRAHEDRON   /// poligono de 4 lados
    };

protected:
    Vector3                     vColor;
    PrimitiveGL::PrimitiveType  oType;
    GLdouble                    dSize,
                                dHeight;
    GLint                       iSlices,
                                iStacks;

public:
    PrimitiveGL( PrimitiveGL::PrimitiveType = PrimitiveGL::SPHERE );
    PrimitiveGL( const PrimitiveGL& );
    PrimitiveGL( PrimitiveGL* );

    void setColor( Vector3 );

    inline Vector3 getColor() { return this->vColor; }

    void OnRender();
    void OnLoop( double );

    void setSize( GLdouble );
    void setHeight( GLdouble );
    void setResolution( GLint, GLint );
};

#endif // _PRIMITIVE_NOT_INCLUDED_
