/**
   \file Interpolator.h
   \brief Descricao da classe Interpolator

   Esta classe tem por objetivo implementar um interpolador entre dois atributos fornecidos

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _INTERPOLATOR_NOT_INCLUDED_
#define _INTERPOLATOR_NOT_INCLUDED_

#include "Entity.h"
#include "PoseAttr.h"

#include <vector>
using namespace std;

/**
   \class Interpolator
   \brief Classe que implementa um interpolador entre um conjunto de atributos dados
   \sa Pose
*/
class Interpolator
{
protected:
    Entity *         ptrOwner;       ///< ponteiro para o objeto que sera afetado por este interpolador
    vector<PoseAttr> listOfPoseAttr; ///< lista de atributos interpoláveis associados a este interpolador

    void updateParent( Entity * );

public:
    Interpolator();
    Interpolator( const Interpolator & );
    Interpolator( Interpolator * );

    void setParent( Entity * );
    void addAttribute( PoseAttr );

    virtual void OnLoop( double ) = 0;
};

#endif
