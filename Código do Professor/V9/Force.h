/**
   \file Force.h
   \brief Descricao da classe de descri��o de uma for�a aplic�vel a um corpo rigido

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2014. Universidade do Estado de Santa Catarina - UDESC<br>

   \sa RigidBody
*/
#ifndef _FORCE_H_
#define _FORCE_H_

#include <string>
using namespace std;

#include "Vector3.h"

class Force
{
private:
    string  strID;  ///< identificador da for�a
    Vector3 vForce; ///< vetor que indica dire�ao e magnitude da for�a

public:
    Force( string, Vector3 );
    Force( Force* );

    void setID( string );
    /**
       \brief Expoe o conteudo do identificador da for�a
       \return string contendo o nome da for�a
    */
    inline string getID() { return this->strID; }

    void setForce( Vector3 );
    /**
       \brief Expoe o conteudo do vetor direcional da for�a
       \return dire�ao da for�a
    */
    inline Vector3 getForce() { return this->vForce; }
};

#endif
