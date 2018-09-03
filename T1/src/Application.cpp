#include "Application.h"
// #include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <typeinfo>

Application::Application( string strAppName ):
    uiWindowWidth( 800 ), uiWindowHeight( 600 ), strCurrentFPS( "FPS: ?" ), dCounterTimer( 0.0 ), uiFrames( 0 )
{
	this->strAppName = strAppName;
}

Application::~Application()
{
	for( vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++ )
		delete (* pointer );
}


int Application::Execute( double dElapsedTime )
{
	this->CalculateFPS( dElapsedTime );

	for( vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++ )
		(* entity )->OnLoop( dElapsedTime );

	return 1;
}


void Application::setWindowSize( unsigned int uiWidth, unsigned int uiHeight )
{
	this->uiWindowWidth  = uiWidth;
	this->uiWindowHeight = uiHeight;

	Camera * refCamera   = this->getCamera();
	if( refCamera )
        refCamera->setViewport( uiWidth, uiHeight );
}


void Application::CalculateFPS( double dElapsedTime )
{
	this->dCounterTimer += dElapsedTime;
	uiFrames ++;

	if( this->dCounterTimer >= 1.0 )
	{
		char strFPS[20];

		sprintf( strFPS, "FPS: %d", uiFrames );

		this->strCurrentFPS = strFPS;
		this->uiFrames      = 0;
		this->dCounterTimer = 0.0;
	}
}


Camera* Application::getCamera()
{
    for( vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++ )
        if(typeid( ( *entity ) ).name() == string( "Camera" ) )
            return ( Camera* )( *entity );
    return NULL;
}


void Application::RenderFrame()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	for( vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++ )
		(* entity )->OnRender();

	glutSwapBuffers();
}


void Application::addEntity( Entity* ptrEnt )
{
	this->listOfEntities.push_back( ptrEnt );
}

bool Application::setEntity( Entity* ptrEnt, unsigned int uiIndex )
{
	if( uiIndex < this->listOfEntities.size() )
	{
		this->listOfEntities[uiIndex] = ptrEnt;
		return true;
	}
	return false;
}

Entity* Application::getEntity( unsigned int uiIndex )
{
	if( uiIndex < this->listOfEntities.size() )
	{
		return this->listOfEntities[uiIndex];
	}
	return NULL;
}
