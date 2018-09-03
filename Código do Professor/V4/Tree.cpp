/**
   \file Tree.cpp
   \brief Implementacao dos metodos da classe Tree

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Tree.h"

/**
  \brief Construtor padrao para a classe Tree
  Cria uma primitiva grafica composta
*/
Tree::Tree(): Object()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Tree
  Cria uma copia exata de um objeto Tree existente
  \param clone Objeto  da classe Tree a ser clonado
*/
Tree::Tree( const Tree &clone ): Object( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Tree a partir de ponteiros
  Cria uma copia exata de um objeto Tree existente
  \param ptrClone Ponteiro para um objeto Tree a ser clonado
*/
Tree::Tree( Tree* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void Tree::Initialize()
{
	PrimitiveGL * ptrTrunk = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrTrunk->setSize( 0.5f );
	ptrTrunk->setScale( Vector3( 0.35f, 1.5f, 0.35f ));
	ptrTrunk->setTranslate( Vector3( 0.0f, 0.75f, 0.0f ));
	ptrTrunk->setColor( Vector3( 0.46f, 0.38f, 0.25f ) ); // marrom RGB(119, 98, 66)
	this->listOfEntities.push_back( ptrTrunk );

	PrimitiveGL * ptrTree = new PrimitiveGL( PrimitiveGL::ICOSAHEDRON );
	ptrTree->setColor( (( Vector3 ) Vector3::GREEN ) * 0.35f ); // verde 15%
	ptrTree->setScale( Vector3( 0.5f, 0.5f, 0.5f ));
	ptrTree->setTranslate( Vector3( 0.0f, 1.5f, 0.0f ));
	this->listOfEntities.push_back( ptrTree );
}

