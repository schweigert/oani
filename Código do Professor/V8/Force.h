/**
   \file Force.h
   \brief Descricao da classe de descrição de uma força aplicável a um corpo rigido

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
    string  strID;  ///< identificador da força
    Vector3 vForce; ///< vetor que indica direçao e magnitude da força

public:
    Force( string, Vector3 );
    Force( Force* );

    void setID( string );
    /**
       \brief Expoe o conteudo do identificador da força
       \return string contendo o nome da força
    */
    inline string getID() { return this->strID; }

    void setForce( Vector3 );
    /**
       \brief Expoe o conteudo do vetor direcional da força
       \return direçao da força
    */
    inline Vector3 getForce() { return this->vForce; }
};

#endif
