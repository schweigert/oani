/**
   \file PrimitiveGL.h
   \brief Descricao da classe para primitivas graficas do OPENGL

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _PRIMITIVE_NOT_INCLUDED_
#define _PRIMITIVE_NOT_INCLUDED_

#include "Entity.h"
#include <GL/gl.h>

/**
   \class PrimitiveGL
   \brief Responsavel por manipular objetos primitivos do OPENGL.<br>

   \sa Entity()
*/
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
    Vector3                     vColor;  /// cor da primitiva grafica
    PrimitiveGL::PrimitiveType  oType;   /// tipo da primitiva grafica
    GLdouble                    dSize,   /// raio/largura da primitiva grafica
                                dHeight; /// altura/raio 2 da primitiva grafica
    GLint                       iSlices, /// quantidade de fatias da primitiva
                                iStacks; /// quantidade de subdivisoes da primitiva

public:
    PrimitiveGL( PrimitiveGL::PrimitiveType = PrimitiveGL::SPHERE );
    PrimitiveGL( const PrimitiveGL& );
    PrimitiveGL( PrimitiveGL* );

    void setColor( Vector3 );

    /**
      \brief Retorna o valor corrente da cor do objeto
      \return Vector3 com o valor atual do vetor de cor
    */
    inline Vector3 getColor() { return this->vColor; }

    void OnRender();
    void OnLoop( double );

    void setSize( GLdouble );
    void setHeight( GLdouble );
    void setResolution( GLint, GLint );
};

#endif // _PRIMITIVE_NOT_INCLUDED_
