/**
	\file Application.cpp
	\brief Implementacao dos metodos da classe Application declarados em Application.h

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Fevereiro, 2015. Universidade do Estado de Santa Catarina (UDESC)
*/

#include "Application.h"
#include <stdio.h>
#include <GL/glut.h>
#include <typeinfo>

/**
	\brief Construtor default para a classe Application
*/
Application::Application( string strAppName ):
    uiWindowWidth( 800 ), uiWindowHeight( 600 ), strCurrentFPS( "FPS: ?" ), dCounterTimer( 0.0 ), uiFrames( 0 )
{
	this->strAppName = strAppName;
}

/**
	\brief Desaloca todos os membros dinamicos utilizados na classe Application
*/
Application::~Application()
{
	for( vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++ )
		delete (* pointer );
}

/**
	\brief Executa o loop principal da aplicacao IDS
	\param dElapsedTime tempo transcorrido (em milisegundos) entre duas chamadas consecutivas da funcao
	\return int flag que indica sucesso ou falha na execucao
*/
int Application::Execute( double dElapsedTime )
{
	this->CalculateFPS( dElapsedTime );

	for( vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++ )
		(* entity )->OnLoop( dElapsedTime );

	return 1;
}

/**
	\brief Define as dimensoes da janela da aplicacao IDS
	\param uiWidth largura da janela da aplicacao
	\param uiHeight altura da janela da aplicacao
*/
void Application::setWindowSize( unsigned int uiWidth, unsigned int uiHeight )
{
	this->uiWindowWidth  = uiWidth;
	this->uiWindowHeight = uiHeight;

	Camera * refCamera   = this->getCamera();
	if( refCamera )
        refCamera->setViewport( uiWidth, uiHeight );
}

/**
	\brief Efetua o calculo do FPS (Frames per Second) disponivel
	\param dElapsedTime tempo transcorrido entre duas chamadas consecutivas da funcao
*/
void Application::CalculateFPS( double dElapsedTime )
{
	this->dCounterTimer += dElapsedTime;
	uiFrames ++;

	if( this->dCounterTimer >= 1.0 ) // 1 segundo transcorrido?
	{
		char strFPS[20];

		sprintf( strFPS, "FPS: %d", uiFrames );

		this->strCurrentFPS = strFPS;
		this->uiFrames      = 0;
		this->dCounterTimer = 0.0;
	}
}

/**
    \brief Retorna uma referencia ao objeto do tipo Camera na lista de entidades presentes na cena
    \return referencia ao objeto do tipo Camera
*/
Camera* Application::getCamera()
{
    for( vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++ )
        if(typeid( ( *entity ) ).name() == string( "Camera" ) )
            return ( Camera* )( *entity );
    return NULL; // se nenhuma camera foi encontrada
}

/**
    \brief Metodo responsavel por desenhar cada frame da aplicacao
*/
void Application::RenderFrame()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // limpa os buffers de cor e profundidade para o desenho do proximo frame

	for( vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++ )
		(* entity )->OnRender();

	glutSwapBuffers(); // efetua a troca de buffers para o calculo do proximo frame
}

/**
   \brief Adiciona uma nova entidade renderizavel a cena sendo manipulada
   \param ptrEnt ponteiro para a nova entidade a ser adicionada a cena
*/
void Application::addEntity( Entity* ptrEnt )
{
	this->listOfEntities.push_back( ptrEnt );
}
/**
   \brief Altera uma dada entidade pertencente a cena sendo manipulada
   \param ptrEnt ponteiro para a nova entidade a ser adicionada a cena
   \param uiIndex posicao da entidade na lista de entidades da cena
   \return flag que indica se houve sucesso na operacao
*/
bool Application::setEntity( Entity* ptrEnt, unsigned int uiIndex )
{
	if( uiIndex < this->listOfEntities.size() )
	{
		this->listOfEntities[uiIndex] = ptrEnt;
		return true;
	}
	return false;
}
/**
   \brief Retorna uma dada entidade da cena sendo manipulada
   \param uiIndex posicao da entidade na lista de entidades da cena a ser retornada
   \return ponteiro para a dade entidade ou NULL caso indice invalido
*/
Entity* Application::getEntity( unsigned int uiIndex )
{
	if( uiIndex < this->listOfEntities.size() )
	{
		return this->listOfEntities[uiIndex];
	}
	return NULL;
}
