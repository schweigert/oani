/**
   \file Actor.cpp
   \brief Implementacao dos metodos da classe Actor

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Actor.h"
#include <stdlib.h>
#include <stdio.h>

/**
  \brief Construtor para a classe Actor
  Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
  em escala canonica.
*/
Actor::Actor(): ptrAnimator( NULL )
{
}
/**
  \brief Construtor de clonagem para a classe Actor
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
Actor::Actor( const Actor& clone )
{
	this->ptrAnimator = new Animator( clone.ptrAnimator );
}
/**
  \brief Construtor de clonagem para a classe Actor a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
Actor::Actor( Actor* ptrClone )
{
	this->ptrAnimator = new Animator( ptrClone->ptrAnimator );
}
/**
  \brief Desaloca os objetos dinamicos desta classe
*/
 Actor::~Actor()
 {
     if( this->ptrAnimator)
        delete this->ptrAnimator;
    this->ptrAnimator = NULL;   // as vezes a operaçao de delete mantem lixo no ponteiro
 }
/**
  \brief Associa um objeto animador com este ator
  \param ptrAnimator ponteiro do objeto animador a ser associado
*/
void Actor::setAnimator( Animator* ptrAnimator )
{
    if( ptrAnimator )
    {
        this->ptrAnimator = ptrAnimator;
        this->ptrAnimator->setParent( this );
    }
}
/**
   \brief Executa o processo de animação
   \param dDeltaTime tempo transcorrido deste a ultima chamada desta função
*/
void Actor::OnLoop( double dDeltaTime )
{
    if( this->ptrAnimator )
    {
        this->ptrAnimator->OnLoop( dDeltaTime );
    }

    Object::OnLoop( dDeltaTime ); // chama a mesma rotina no objeto-base
}
