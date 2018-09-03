/**
   \file Interpolator.cpp
   \brief Implementacao dos metodos da classe Interpolator

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Interpolator.h"
#include <typeinfo>
#include <string>
#include <stdio.h>

/**
  \brief Construtor para a classe Interpolator
*/
Interpolator::Interpolator()
{}
/**
  \brief Construtor de clonagem para a classe Interpolator
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
Interpolator::Interpolator( const Interpolator& clone )
{}
/**
  \brief Construtor de clonagem para a classe Interpolator a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
Interpolator::Interpolator( Interpolator* ptrClone )
{}
/**
  \brief Desaloca os objetos dinamicos desta classe
*/
Interpolator::~Interpolator()
{
    for( vector<PoseAttr*>::iterator itPose = this->listOfPoseAttr.begin();
         itPose != this->listOfPoseAttr.end(); itPose++ )
         delete (* itPose );
}
/**
   \brief Adiciona um novo atributo anim�vel neste interpolador
   \param ptrPoseAttr objeto do tipo PoseAttr associado a este interpolador
*/
void Interpolator::addAttribute( PoseAttr * ptrPoseAttr )
{
    // OBSERVA��O!
    // como n�o implementei um rotina para ordena��o temporal dos atributos
    // estes devem ser inseridos em ordem cronol�gica

    this->listOfPoseAttr.push_back( ptrPoseAttr );
}
/**
   \brief Associa este interpolador a um objeto-pai do tipo Entity
   \param ptrOwner ponteiro para o objeto ao qual este interpolador sera associado
*/
void Interpolator::setParent( Entity* ptrOwner )
{
    this->ptrOwner = ptrOwner;
}
/**
  \brief Retorna o ponteiro para um dos atributos associados a este interpolador
  \param uiIndex posi�ao do atributo a ser retornado
  \return ponteiro para o referido atributo ou nulo caso indice invalido
*/
PoseAttr* Interpolator::getAttribute( unsigned int uiIndex )
{
    if( uiIndex < this->listOfPoseAttr.size() )
        return this->listOfPoseAttr[ uiIndex ];
    return NULL;
}
