/**
   \file Joint.cpp
   \brief Implementacao dos metodos da classe Joint

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Joint.h"
#include <stdlib.h>
#include <stdio.h>

/**
  \brief Construtor para a classe Joint
  Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
  em escala canonica.
*/
Joint::Joint(): Actor()
{}
/**
  \brief Construtor de clonagem para a classe Joint
  Cria uma copia exata de um objeto entidade ja existente
  \param clone Objeto a ser clonado
*/
Joint::Joint( const Joint& clone ): Actor( clone )
{}
/**
  \brief Construtor de clonagem para a classe Joint a partir de ponteiros
  Cria uma copia exata de um objeto entidade ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
Joint::Joint( Joint* ptrClone ): Actor( ptrClone )
{}
/**
  \brief Desaloca os objetos dinamicos desta classe
*/
 Joint::~Joint()
 {
     for( vector<Joint*>::iterator itJoint = this->listOfJoints.begin(); itJoint != this->listOfJoints.end(); itJoint++ )
        delete (* itJoint );
 }
/**
  \brief Associa uma nova junta como filha desta junta
  \param ptrJoint ponteiro para a nova junta-filha a ser associada
*/
void Joint::Attach( Joint* ptrJoint )
{
    if( ptrJoint )
        this->listOfJoints.push_back( ptrJoint );
}
/**
    \brief Rotina para rendering de todas as primitivas graficas que compoem esta junta
*/
void Joint::OnRender()
{
    glPushMatrix();

    glRotatef( this->vRotatePivot.z, 0.0f, 0.0f, 1.0f );
    glRotatef( this->vRotatePivot.y, 0.0f, 1.0f, 0.0f );
    glRotatef( this->vRotatePivot.x, 1.0f, 0.0f, 0.0f );
    glTranslatef( this->vPivot.x, this->vPivot.y, this->vPivot.z );
    glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
    glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );
    glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
    glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );

   	for( vector<Joint*>::iterator itJoint  = this->listOfJoints.begin(); itJoint != this->listOfJoints.end(); itJoint++ )
        (* itJoint )->OnRender();

    glScalef( this->vScale.x, this->vScale.y, this->vScale.z );
    glTranslatef( -this->vPivot.x, -this->vPivot.y, -this->vPivot.z );

	for( vector<Entity*>::iterator itEntity = this->listOfEntities.begin(); itEntity != this->listOfEntities.end(); itEntity++ )
        (* itEntity )->OnRender();

    glPopMatrix();
}
/**
   \brief Executa o processo de animação
   \param dDeltaTime tempo transcorrido deste a ultima chamada desta função
*/
void Joint::OnLoop( double dDeltaTime )
{
   	for( vector<Joint*>::iterator itJoint  = this->listOfJoints.begin(); itJoint != this->listOfJoints.end(); itJoint++ )
        (* itJoint )->OnLoop( dDeltaTime );

    Actor::OnLoop( dDeltaTime ); // chama a mesma rotina no objeto-base
}
