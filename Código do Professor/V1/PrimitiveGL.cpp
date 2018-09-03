/**
   \file PrimitiveGL.cpp
   \brief Implementacao dos metodos da classe PrimitiveGL

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "PrimitiveGL.h"
#include <GL/glut.h>

/**
  \brief Construtor padrao para a classe PrimitiveGL
  Cria uma primitiva grafica do OPENGL
  \param oType tipo da primitiva grafica
*/
PrimitiveGL::PrimitiveGL( PrimitiveGL::PrimitiveType oType ): Entity(),
    dSize( 1.0 ), dHeight( 1.0 ), iSlices( 10 ), iStacks( 10 )
{
    this->oType  = oType;
    this->vColor = Vector3::WHITE;
}

/**
  \brief Construtor de copia para a classe PrimitiveGL
  Cria uma copia exata de um objeto PrimitiveGL existente
  \param clone Objeto PrimitiveGL a ser clonado
*/
PrimitiveGL::PrimitiveGL( const PrimitiveGL& clone ): Entity( clone )
{
    this->oType   = clone.oType;
    this->vColor  = clone.vColor;
    this->dSize   = clone.dSize;
    this->dHeight = clone.dHeight;
    this->iSlices = clone.iSlices;
    this->iStacks = clone.iStacks;
}

/**
  \brief Construtor de copia para a classe PrimitiveGL a partir de ponteiros
  Cria uma copia exata de um objeto PrimitiveGL existente
  \param ptrClone Ponteiro para um objeto PrimitiveGL a ser clonado
*/
PrimitiveGL::PrimitiveGL( PrimitiveGL* ptrClone ): Entity( ptrClone )
{
    this->oType   = ptrClone->oType;
    this->vColor  = ptrClone->vColor;
    this->dSize   = ptrClone->dSize;
    this->dHeight = ptrClone->dHeight;
    this->iSlices = ptrClone->iSlices;
    this->iStacks = ptrClone->iStacks;
}

/**
  \brief Define a cor a primitiva grafica
  \param color cor da primitiva em formato RGB
*/
void PrimitiveGL::setColor( Vector3 color )
{
   this->vColor = color;
}

/**
   \brief Define a largura da primitiva grafica
   \param dSize tamanho da primitiva grafica
*/
void PrimitiveGL::setSize( GLdouble dSize )
{
    this->dSize = dSize;
}

/**
   \brief Define a altura da primitiva grafica. Usado tambem como raio interno para o Torus
   \param dHeight altura da primitiva grafica
*/
void PrimitiveGL::setHeight( GLdouble dHeight )
{
    this->dHeight = dHeight;
}

/**
   \brief Define a resolu��o poligonal da primitiva grafica
   \param iSlices quantidade de fatias da primitiva grafica
   \param iStacks quantidade de subdivisoes da primitiva grafica
*/
void PrimitiveGL::setResolution( GLint iSlices, GLint iStacks )
{
    this->iSlices = iSlices;
    this->iStacks = iStacks;
}

/**
   \brief Apresenta a primitiva grafica no OPENGL utilizando os parametros fornecidos
*/
void PrimitiveGL::OnRender()
{
    glPushMatrix();

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

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
    glPopMatrix();
}

/**
   \brief Atualiza os parametros da primitiva para o proximo frame da animacao
   \param dDeltaTime tempo transcorrido entre duas atualizacoes sucessivas (em milisegundos)
*/
void PrimitiveGL::OnLoop( double dDeltaTime )
{}
