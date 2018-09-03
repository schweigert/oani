/**
   \file Joint.h
   \brief Um ator representa qualquer objeto animável na cena

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _JOINT_NOT_INCLUDED_
#define _JOINT_NOT_INCLUDED_

#include "Object.h"
#include "Actor.h"

/**
   \class Joint
   \brief Responsavel por construir um objeto do tipo junção em um modelo hierarquico<br>

   \sa Object()
*/
class Joint: public Actor
{
protected:
    vector<Joint*> listOfJoints; ///< lista de juntas filhas associadas a esta junta

public:
    Joint();
    Joint( const Joint & );
    Joint( Joint* );
    ~Joint();

    virtual void Initialize() {}

    void Attach( Joint* );

    virtual void OnRender();
    virtual void OnLoop( double );
};

#endif


