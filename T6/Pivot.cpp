#include "Pivot.h"
#include <GL/glut.h>

/**
  \brief Construtor para a classe Pivot
  Cria um elemento pivot com seus parametros (posicao, orientacao e tamanho) default
*/
Pivot::Pivot():Entity()
{}
/**
  \brief Construtor de clonagem para a classe Pivot
  Copia um elemento Pivot ja existente
  \param Clone objeto a ser copiado
*/
Pivot::Pivot( const Pivot& Clone ):Entity( Clone )
{}
/**
  \brief Construtor de clonagem para a classe Pivot a partir de ponteiros
  Copia um elemento Pivot a partir de um ponteiro para um objeto Pivot ja existente
  \param ptrClone ponteiro para o objeto a ser copiado
*/
Pivot::Pivot( Pivot* ptrClone ):Entity( ptrClone )
{}
/**
  \brief Atualiza os parametros de animacao deste pivot em cada novo quadro da animacao
  \param uiDeltaTime tempo transcorrido desde a ultima chamada de atualizacao da primitiva
*/
void Pivot::OnLoop( double dDeltaTime )
{
	Entity::OnLoop( dDeltaTime );
}
/**
   \brief Desenha todos os objetos associados a este pivot
*/
void Pivot::OnRender()
{
	glPushMatrix();

	glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );
	glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
	glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );

	glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );

	glScalef( this->vScale.x, this->vScale.y, this->vScale.z );

	if( this->listOfEntities.size() > 0 )
		for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
			ptrEntity != this->listOfEntities.end(); ptrEntity++ )
			(* ptrEntity )->OnRender();

	glPopMatrix();
}
