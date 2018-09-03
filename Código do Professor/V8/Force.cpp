/**
   \file Force.cpp
	\brief Implementacao dos metodos da classe Force declarados em Force.h

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Abril, 2017. Universidade do Estado de Santa Catarina (UDESC)
*/
#include "Force.h"

/**
   \brief Construtor para a classe Force
   \param strID nome da for�a
   \param vForce vetor dire�ao da for�a
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
   \brief Especifica o nome da for�a
   \param strID nome da for�a
*/
void Force::setID( string strID )
{
    this->strID = strID;
}
/**
   \brief Especifica o vetor dire�ao da for�a
   \param vForce vetor dire�ao da for�a
*/
void Force::setForce( Vector3 vForce )
{
    this->vForce = vForce;
}
