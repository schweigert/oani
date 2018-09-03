/**
   \file Force.cpp
	\brief Implementacao dos metodos da classe Force declarados em Force.h

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Abril, 2017. Universidade do Estado de Santa Catarina (UDESC)
*/
#include "Force.h"

/**
   \brief Construtor para a classe Force
   \param strID nome da força
   \param vForce vetor direçao da força
*/
Force::Force( string strID, Vector3 vForce )
{
    this->strID  = strID;
    this->vForce = vForce;
}
/**
   \brief Copy-constructor para objetos dinamicos
   \param ptrClone ponteiro para o objeto a ser clonado
*/
Force::Force( Force *ptrClone )
{
    this->strID  = ptrClone->strID;
    this->vForce = ptrClone->vForce;
}
/**
   \brief Especifica o nome da força
   \param strID nome da força
*/
void Force::setID( string strID )
{
    this->strID = strID;
}
/**
   \brief Especifica o vetor direçao da força
   \param vForce vetor direçao da força
*/
void Force::setForce( Vector3 vForce )
{
    this->vForce = vForce;
}
