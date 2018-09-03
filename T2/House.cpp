/**
   \file House.cpp
   \brief Implementacao dos metodos da classe House

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "House.h"

/**
  \brief Construtor padrao para a classe House
  Cria uma primitiva grafica composta
*/
House::House(): Object()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe House
  Cria uma copia exata de um objeto House existente
  \param clone Objeto  da classe House a ser clonado
*/
House::House( const House &clone ): Object( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe House a partir de ponteiros
  Cria uma copia exata de um objeto House existente
  \param ptrClone Ponteiro para um objeto House a ser clonado
*/
House::House( House* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela construção do objeto
*/
void House::Initialize()
{
	PrimitiveGL * ptrHouse = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrHouse->setScale( Vector3( 1.0f, 0.7f, 1.0f ));
	ptrHouse->setTranslate( Vector3( 0.0f, 0.35f, 0.0f ));
	this->listOfEntities.push_back( ptrHouse );

	PrimitiveGL * ptrRoof = new PrimitiveGL( PrimitiveGL::CONE );
	ptrRoof->setResolution( 4, 4 );
	ptrRoof->setScale( Vector3( 1.0f, 1.0f, 0.4f ));
	ptrRoof->setColor( Vector3::YELLOW );
	ptrRoof->setTranslate( Vector3( 0.0f, 0.7f, 0.0f ));
	ptrRoof->setRotate( Vector3( -90.0f, 45.0f, 0.0f ) );
	this->listOfEntities.push_back( ptrRoof );
}


