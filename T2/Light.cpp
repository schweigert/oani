/**
   \file Light.cpp
   \brief Implementacao dos metodos da classe Light

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "Light.h"

#include "stdio.h"

/**
  \brief Construtor padrao para a classe Light
  Cria uma primitiva grafica composta
*/
Light::Light(): Actor()
{
    this->Initialize();
}

/*
  \brief Construtor de copia para a classe Light
  Cria uma copia exata de um objeto Light existente
  \param clone Objeto  da classe Light a ser clonado
*/
Light::Light( const Light &clone ): Actor( clone )
{
    this->Initialize();
}


/**
  \brief Construtor de copia para a classe Light a partir de ponteiros
  Cria uma copia exata de um objeto Light existente
  \param ptrClone Ponteiro para um objeto Light a ser clonado
*/
Light::Light( Light* ptrClone ): Actor( ptrClone )
{
    this->Initialize();
}

/**
   \brief Rotina responsavel pela constru��o do objeto
*/
void Light::Initialize()
{
  puts("TESTE Light");
  GLfloat light_position[] = { 0.0, 0.0, 0.0, 0.0 },
          light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
  glLightfv( GL_LIGHT0, GL_POSITION, light_position );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
}
