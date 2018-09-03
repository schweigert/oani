/**
   \file Helix.cpp
   \brief Implementacao dos metodos da classe Helix

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Helix.h"

/**
  \brief Construtor padrao para a classe Helix
  Cria uma primitiva grafica composta
*/
Helix::Helix(): Actor()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Helix
  Cria uma copia exata de um objeto Helix existente
  \param clone Objeto  da classe Helix a ser clonado
*/
Helix::Helix( const Helix &clone ): Actor( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Helix a partir de ponteiros
  Cria uma copia exata de um objeto Helix existente
  \param ptrClone Ponteiro para um objeto Helix a ser clonado
*/
Helix::Helix( Helix* ptrClone ): Actor( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void Helix::Initialize()
{
	PrimitiveGL * ptrHelix1 = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrHelix1->setSize( 0.75f );
	ptrHelix1->setScale( Vector3( 0.05f, 1.0f, 0.05f ));
	ptrHelix1->setColor( Vector3::BLUE );
	this->listOfEntities.push_back( ptrHelix1 );

	PrimitiveGL * ptrHelix2 = new PrimitiveGL( ptrHelix1 );
	ptrHelix2->setRotate( Vector3( 0.0f, 0.0f, 45.0f ));
	this->listOfEntities.push_back( ptrHelix2 );

	PrimitiveGL * ptrHelix3 = new PrimitiveGL( ptrHelix1 );
	ptrHelix3->setRotate( Vector3( 0.0f, 0.0f, 90.0f ));
	this->listOfEntities.push_back( ptrHelix3 );

	PrimitiveGL * ptrHelix4 = new PrimitiveGL( ptrHelix1 );
	ptrHelix4->setRotate( Vector3( 0.0f, 0.0f, -45.0f ));
	this->listOfEntities.push_back( ptrHelix4 );

	PrimitiveGL * ptrHelixBall = new PrimitiveGL( );
	ptrHelixBall->setSize( 0.1f );
	this->listOfEntities.push_back( ptrHelixBall );

	PrimitiveGL * ptrHelix5 = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrHelix5->setScale( Vector3( 0.1f, 0.1f, 0.5f ));
	ptrHelix5->setTranslate( Vector3( 0.0f, 0.0f, 0.25f ));
	this->listOfEntities.push_back( ptrHelix5 );

	this->setPivot( Vector3( 0.0f, 0.0f, 0.5f ));
}
