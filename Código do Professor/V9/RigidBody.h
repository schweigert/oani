/**
   \file RigidBody.h
   \brief Descricao da classe de gerenciamento de corpos rigidos

   Corpos rigidos permitem adicionar animaçoes straigh-ahead de um sistema de forças a um objeto Entity

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2014. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "Vector3.h"

#include <vector>
using namespace std;

class Entity;

class RigidBody
{
private:
    Entity * ptrEntity; ///< ponteiro para o objeto associado a este corpo rigido
    Vector3  vForce,    ///< força resultante do sistema de forças
             vGravity;  ///< força da gravidade
    Vector3  vSpeed;    ///< velocidade do corpo rigido
    float    fMass;     ///< massa do corpo rigido

public:
    RigidBody();
    RigidBody( const RigidBody& );
    RigidBody( RigidBody* );

    void attach( Entity* );

    void addForce( Vector3 );
    void setGravity( Vector3 );

    void setMass( float );
    /**
       \brief Retorna o valor da massa do corpo rigido
       \return valor corrente da massa do corpo rigido
    */
    inline float getMass() { return this->fMass; }

    void OnLoop( double );
};
#endif
