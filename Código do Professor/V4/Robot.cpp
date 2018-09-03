/**
   \file Robot.cpp
   \brief Implementacao dos metodos da classe Robot

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Robot.h"

/**
  \brief Construtor padrao para a classe Robot
  Cria uma primitiva grafica composta
*/
Robot::Robot(): Actor()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Robot
  Cria uma copia exata de um objeto Robot existente
  \param clone Objeto  da classe Robot a ser clonado
*/
Robot::Robot( const Robot &clone ): Actor( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Robot a partir de ponteiros
  Cria uma copia exata de um objeto Robot existente
  \param ptrClone Ponteiro para um objeto Robot a ser clonado
*/
Robot::Robot( Robot* ptrClone ): Actor( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void Robot::Initialize()
{
	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrBase->setScale( Vector3( 0.35f, 0.1f, 0.35f ));
	ptrBase->setColor( Vector3::RED );
	this->listOfEntities.push_back( ptrBase );

	PrimitiveGL * ptrStem = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrStem->setScale( Vector3( 0.05f, 0.4f, 0.05f ) );
	ptrStem->setTranslate( Vector3( 0.0f, 0.2f, 0.0f ));
	this->listOfEntities.push_back( ptrStem );

	PrimitiveGL * ptrBody = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrBody->setScale( Vector3( 0.5f, 0.8f, 0.3f ) );
	ptrBody->setTranslate( Vector3( 0.0f, 0.7f, 0.0f ));
	ptrBody->setColor( Vector3::RED );
	this->listOfEntities.push_back( ptrBody );

	PrimitiveGL * ptrHead = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrHead->setScale( Vector3( 0.2f, 0.2f, 0.2f ) );
	ptrHead->setTranslate( Vector3( 0.0f, 1.2f, 0.0f ));
	this->listOfEntities.push_back( ptrHead );

	// braço esquerdo
	PrimitiveGL * ptrArm1 = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrArm1->setScale( Vector3( 0.1f, 0.5f, 0.1f ) );
	ptrArm1->setTranslate( Vector3( 0.3f, 0.8f, 0.0f ));
	this->listOfEntities.push_back( ptrArm1 );

	// braço direito
	PrimitiveGL * ptrArm2 = new PrimitiveGL( ptrArm1 );
	ptrArm2->setTranslate( Vector3( -0.3f, 0.8f, 0.0f ));
	this->listOfEntities.push_back( ptrArm2 );
}
