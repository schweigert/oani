/**
	\file Application.cpp
	\brief Implementacao dos metodos da classe Application declarados em Application.h

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Fevereiro, 2015. Universidade do Estado de Santa Catarina (UDESC)
*/

#include "Application.h"
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <typeinfo>
// includes da aplica��o
#include "Camera.h"
#include "Vector3.h"
#include "LightSource.h"
#include "BRep.h"
#include "RigidBody.h"

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
    if( !ptrEnt )
        return;

    ptrEnt->setApplicationRef( this );

	this->listOfEntities.push_back( ptrEnt );

	if( ptrEnt->hasRigidBody() )
    {
        this->listOfRigidBodies.push_back( ptrEnt );
        //printf("+RB\n");
    }
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
/**
    \brief Retorna o valor corrente do titulo da aplicacao.<br>
    O titulo e o resultado do nome da aplicacao + o valor corrente para o FPS.

    \return string titulo da aplicacao
*/
string Application::getTitle()
{
    char strPolyCount[15];
    sprintf( strPolyCount, "%d", this->uiPolyCount );
    return this->strAppName + " - [" + this->strCurrentFPS + "] - " + strPolyCount + " poligonos";
}

/**
  \brief Constroi a cena a ser renderizada e animada nesta aplica��o
*/
void Application::CreateScene()
{
    string strPath = "G:/";

	printf("Montando a cena...\n");

	Camera * ptrCamera = new Camera();
	ptrCamera->setTranslate( Vector3( 0.0f, 2.0, 9.0f ) );
	this->addEntity( ptrCamera );

	LightSource* ptrLight = new LightSource( 0, LightSource::POINT );
	ptrLight->setTranslate( Vector3( 0.0f, 10.0f, 0.0f ) );
	this->addEntity( ptrLight );

	/*BRep * ptrGround = new BRep();
	ptrGround->LoadfromFile( strPath + "obj/ground.obj" );
	ptrGround->setScale( Vector3( 5.0f, 5.0f, 5.0f ));
	this->addEntity( ptrGround );
	this->uiPolyCount += ptrGround->getPolyCount();*/

	// -------------------------------------------------------------------------------------------------

	RigidBody * ptrRigidBody = new RigidBody();
	ptrRigidBody->setMass( 5.0f );
	ptrRigidBody->setGravity( Vector3( 0.0f, -1.0f, 0.0f ));
	ptrRigidBody->addForce( Vector3( 30.0f, 50.0f, 0.0f )); // trust
	//ptrRigidBody->addForce( Vector3( -20.0f, 0.0f, 0.0f )); // wind

	BRep * ptrBall = new BRep();
	ptrBall->LoadfromFile( strPath + "obj/Basketball.obj" );
	ptrBall->setScale( Vector3( 0.2f, 0.2f, 0.2f ));
	ptrBall->setTranslate( Vector3( -2.0f, 0.25f, 0.0f ));
	ptrBall->setRigidBody( ptrRigidBody );
	ptrRigidBody->setBoundingSphere();

	this->addEntity( ptrBall );
	this->uiPolyCount += ptrBall->getPolyCount();

	// -------------------------------------------------------------------------------------------------

	RigidBody * ptrRigidBody1 = new RigidBody();
	ptrRigidBody1->setMass( 5.0f );
	ptrRigidBody1->setGravity( Vector3( 0.0f, -1.0f, 0.0f ));
	ptrRigidBody1->addForce( Vector3( -30.0f, 50.0f, 0.0f )); // trust
	//ptrRigidBody1->addForce( Vector3( -20.0f, 0.0f, 0.0f )); // wind

	BRep * ptrBall1 = new BRep();
	ptrBall1->LoadfromFile( strPath + "obj/Basketball.obj" );
	ptrBall1->setScale( Vector3( 0.2f, 0.2f, 0.2f ));
	ptrBall1->setTranslate( Vector3( 2.0f, 0.25f, 0.0f ));
	ptrBall1->setRigidBody( ptrRigidBody1 );
	ptrRigidBody1->setBoundingSphere();

	this->addEntity( ptrBall1 );
	this->uiPolyCount += ptrBall1->getPolyCount();
}
