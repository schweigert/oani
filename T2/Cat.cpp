/**
   \file Cat.cpp
   \brief Implementacao dos metodos da classe Cat

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Cat.h"

/**
  \brief Construtor padrao para a classe Cat
  Cria uma primitiva grafica composta
*/
Cat::Cat(): Actor()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Cat
  Cria uma copia exata de um objeto Cat existente
  \param clone Objeto  da classe Cat a ser clonado
*/
Cat::Cat( const Cat &clone ): Actor( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Cat a partir de ponteiros
  Cria uma copia exata de um objeto Cat existente
  \param ptrClone Ponteiro para um objeto Cat a ser clonado
*/
Cat::Cat( Cat* ptrClone ): Actor( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela constru��o do objeto
*/
void Cat::Initialize()
{
	{
    // Corpo
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
  	ptrBase->setScale( Vector3( 0.5f, 0.3f, 0.3f ));
    ptrBase->setTranslate(Vector3(0,0.2f,0));
    ptrBase->setRotate(Vector3(0,0,-30));
  	ptrBase->setColor( Vector3(1,1,1)*0.2f );
  	this->listOfEntities.push_back( ptrBase );
  }

  {
    // Rosto
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.4f, 0.5f, 0.5f ));
    ptrBase->setTranslate(Vector3(-0.4f,0.4f,0));
    ptrBase->setRotate(Vector3(0,0,0));
    ptrBase->setColor( Vector3(1,1,1)*0.2f );
    this->listOfEntities.push_back( ptrBase );
  }
  {
    // Fucinho
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.1f, 0.1f, 0.1f ));
    ptrBase->setTranslate(Vector3(-0.65f,0.3f,0));
    ptrBase->setRotate(Vector3(0,0,0));
    ptrBase->setColor( Vector3(1,0.6,1));
    this->listOfEntities.push_back( ptrBase );
  }
  {
    // Olhos Esquedos
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.1f, 0.17f, 0.1f ));
    ptrBase->setTranslate(Vector3(-0.65f,0.4f,-0.15f));
    ptrBase->setRotate(Vector3(0,0,0));
    ptrBase->setColor( Vector3(0.0,0.8,0.0));
    this->listOfEntities.push_back( ptrBase );
  }

  {
    // Olhos Direitos
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.1f, 0.17f, 0.1f ));
    ptrBase->setTranslate(Vector3(-0.65f,0.4f,0.15f));
    ptrBase->setRotate(Vector3(0,0,0));
    ptrBase->setColor( Vector3(0.0,0.8,0.0));
    this->listOfEntities.push_back( ptrBase );
  }

  {
    // Pata Traseira Esquerda
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
  	ptrBase->setScale( Vector3( 0.25f, 0.2f, 0.25f ));
    ptrBase->setTranslate(Vector3(0.2f,0.1f,0.25));
  	ptrBase->setColor( Vector3(1,1,1)*0.4f );
  	this->listOfEntities.push_back( ptrBase );
  }

  {
    // Pata Dianteira Esquerda
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.2f, 0.15f, 0.2f ));
    ptrBase->setTranslate(Vector3(-0.2f,0.1f,0.25));
    ptrBase->setColor( Vector3(1,1,1)*0.4f );
    this->listOfEntities.push_back( ptrBase );
  }

  {
    // Pata Traseira Direita
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
  	ptrBase->setScale( Vector3( 0.25f, 0.2f, 0.25f ));
    ptrBase->setTranslate(Vector3(0.2f,0.1f,-0.25));
  	ptrBase->setColor( Vector3(1,1,1)*0.4f );
  	this->listOfEntities.push_back( ptrBase );
  }


    {
      // Pata Dianteira Direita
      PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
      ptrBase->setScale( Vector3( 0.2f, 0.15f, 0.2f ));
      ptrBase->setTranslate(Vector3(-0.2f,0.1f,-0.25));
      ptrBase->setColor( Vector3(1,1,1)*0.4f );
      this->listOfEntities.push_back( ptrBase );
    }

}
