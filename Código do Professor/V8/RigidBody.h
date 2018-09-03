/**
   \file RigidBody.h
   \brief Descricao da classe de gerenciamento de corpos rigidos

   Corpos rigidos permitem adicionar animaçoes straigh-ahead de um sistema de forças a um objeto Entity

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2014. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "Force.h"
#include <vector>
using namespace std;

class Entity;

class RigidBody
{
private:
    Entity *       ptrEntity;    ///< ponteiro para o objeto associado a este corpo rigido
    vector<Force*> listOfForces; ///< lista de forças submetidas a esse corpo rigido
    Vector3        vGravity;     ///< vetor gravidade ao qual o corpo rigido esta submetido
    float          fMass;        ///< massa do corpo rigido

public:
    RigidBody();
    RigidBody( const RigidBody& );
    RigidBody( RigidBody* );
    ~RigidBody();

    void attach( Entity* );

    void addForce( Force* );
    Force* getForce( unsigned int );
    Force* getForce( string );
    /**
       \brief Retorna a quantidade de forças submetidas a esse corpo rigido
       \return quantidade de forças desse corpo rigido
    */
    inline unsigned int getNumberOfForces() { return this->listOfForces.size(); }

    void setGravity( Vector3 );
    /**
       \brief Retorna o vetor gravidade corrente
       \return vetor gravidade em uso
    */
    Vector3 getGravity() { return this->vGravity; }

    void setMass( float );
    /**
       \brief Retorna o valor da massa do corpo rigido
       \return valor corrente da massa do corpo rigido
    */
    inline float getMass() { return this->fMass; }

    void OnLoop( double );
};
#endif
