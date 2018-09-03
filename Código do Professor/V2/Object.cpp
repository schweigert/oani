/**
   \file Object.cpp
   \brief Implementacao dos metodos da classe Object

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Object.h"

/**
  \brief Construtor padrao para a classe Object
  Cria uma primitiva grafica composta
*/
Object::Object(): Entity()
{}

/*
  \brief Construtor de copia para a classe Object
  Cria uma copia exata de um objeto Object existente
  \param clone Objeto  da classe Object a ser clonado
*/
Object::Object( const Object &clone ): Entity( clone )
{
    this->listOfEntities = clone.listOfEntities;
}


/**
  \brief Construtor de copia para a classe Object a partir de ponteiros
  Cria uma copia exata de um objeto Object existente
  \param ptrClone Ponteiro para um objeto Object a ser clonado
*/
Object::Object( Object* ptrClone ): Entity( ptrClone )
{
    this->listOfEntities = ptrClone->listOfEntities;
}


/**
	\brief Desaloca todos os membros dinamicos utilizados na classe Object
*/
Object::~Object()
{
	for( vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++ )
		delete (* pointer );
}

/**
    \brief Rotina para rendering de todas as primitivas graficas que compoem este objeto
*/
void Object::OnRender()
{
    glPushMatrix();

    glTranslatef ( this->vPivot.x, this->vPivot.y, this->vPivot.z );
    glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
    glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );
    glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
    glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );
    glScalef( this->vScale.x, this->vScale.y, this->vScale.z );
    glTranslatef ( -this->vPivot.x, -this->vPivot.y, -this->vPivot.z );

	for( vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++ )
        (* pointer )->OnRender();

    glPopMatrix();
}


/**
   \brief Atualiza os parametros da primitiva para o proximo frame da animacao
   \param dDeltaTime tempo transcorrido entre duas atualizacoes sucessivas (em milisegundos)
*/
void Object::OnLoop( double dDeltaTime )
{}

