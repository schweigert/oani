/**
	\file main.cpp
	\brief Modulo principal responsavel pela inicializacao do programa.<p>

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Fevereiro, 2015. Universidade do Estado de Santa Catarina (UDESC)
*/

#include <stdlib.h>
// #include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include "application.h"
#include "Camera.h"
#include "PrimitiveGL.h"

// vari�veis globais

//! gerenciador da aplicacao IDS
Application   * ptrApp   = NULL;
//! armazena a ultima contagem de ticks para o calculo do delta time entre frames
clock_t         LastTime;

/**
	\fn OnStartGL
	\brief Inicia os parametros do ambiente grafico OPENGL e as variaveis de controle da aplicacao
*/
void OnStartGL()
{
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
   	glEnable( GL_DEPTH_TEST ); // ativa o calculo do depth buffer = aplicacoes em 3D
   	glEnable( GL_COLOR_MATERIAL );
   	glCullFace( GL_BACK );

	glShadeModel( GL_SMOOTH ); // ativa o modo de rendering suavizado = n�o facetado
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    GLfloat light_position[] = { 1.0, 1.0, -1.0, 0.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	LastTime = clock();

	Camera * ptrCamera = new Camera();
	ptrCamera->setTranslate( Vector3( 0.0f, 0.0f, -5.0f ));
	ptrApp->addEntity( ptrCamera );

	PrimitiveGL * ptrSphere = new PrimitiveGL();
	ptrSphere->setSize( 0.5 );
	ptrSphere->setResolution( 25, 25 );
	ptrSphere->setTranslate( Vector3( -1.0f, 0.0f, 0.0f ));
	ptrSphere->setColor( Vector3::BLUE );
	ptrApp->addEntity( ptrSphere );

	PrimitiveGL * ptrTeapot = new PrimitiveGL( PrimitiveGL::TEAPOT );
	ptrTeapot->setSize( 0.5 );
	ptrTeapot->setTranslate( Vector3( 1.0f, 0.0f, 0.0f ));
	ptrTeapot->setColor( Vector3::RED );
	ptrApp->addEntity( ptrTeapot );

}

/**
	\fn OnFinishGL
	\brief Finaliza o ambiente OPENGL antes de encerrar a aplicacao
*/
void OnFinishGL()
{
  delete ptrApp;
}

/**
	\fn OnRenderEvent
	\brief Desenha um frame da animacao a cada vez que um evento de REDISPLAY ocorrer
*/
void OnRenderEvent()
{
	ptrApp->RenderFrame();
}

/**
    \fn OnReshapeEvent()
	\brief Recalcula a aparencia grafico da janela sempre que a mesma for redimensionada
	\param uiWidth  nova largura da janela
	\param uiHeight nova altura da janela
*/
void OnReshapeEvent( GLint uiWidth, GLint uiHeight )
{
	ptrApp->setWindowSize( uiWidth, uiHeight );

	/*glViewport( 0.0f, 0.0f, uiWidth, uiHeight );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 65.0f, (float)uiWidth / uiHeight, 0.1f, 100.0f ); // FOV, aspect ratio, near plane, far plane
    glMatrixMode( GL_MODELVIEW );*/
}

/**
	\fn OnKeyboardEvent
	\brief Processa eventos do teclado
	\param ucKey codigo da tecla sendo pressionada
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento do teclado
	\param iMouseY posicao vertical do cursor do mouse no momento do evento do teclado
*/
void OnKeyboardEvent( unsigned char ucKey, int iMouseX, int iMouseY )
{
	switch( ucKey )
	{
	// ESC
	case 27: // encerra a aplicacao
		OnFinishGL();
		exit( 0 );
		break;

	}
}

/**
	\fn OnSpecialKeyboardEvent
	\brief Processa eventos para teclas 'especiais' do teclado como setas direcionais, CTRL, ALT, SHIFT, etc.
	\param iKey codigo da tecla sendo pressionada
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento do teclado
	\param iMouseY posicao vertical do cursor do mouse no momento do evento do teclado
*/
void OnSpecialKeyboardEvent( int iKey, int iMouseX, int iMouseY )
{
	switch( iKey )
	{
	case GLUT_KEY_LEFT: break;
	}
}

/**
	\fn OnMouseButtonEvent
	\brief Processa eventos dos botoes do mouse
	\param iButton indica qual botao do mouse foi pressionado
	\param iState indica o estado corrente do referido botao do mouse
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento
	\param iMouseY posicao vertical do cursor do mouse no momento do evento
*/
void OnMouseButtonEvent( int iButton, int iState, int iMouseX, int iMouseY )
{
	switch( iButton )
	{
	case GLUT_LEFT_BUTTON:
		if( iState == GLUT_DOWN )
		{
			// DO SOMETHING HERE
		}
		break;
	}
}

/**
	\fn OnMouseMotionEvent
	\brief Processa eventos de movimentacao do cursor do mouse
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento
	\param iMouseY posicao vertical do cursor do mouse no momento do evento
*/
void OnMouseMotionEvent( int iMouseX, int iMouseY )
{}

/**
	\fn OnIdleEvent
	\brief Executado a cada nova iteracao do loop OPENGL
*/
void OnIdleEvent()
{
	clock_t currTime = clock();
	double elapsedTime = (( double) ( currTime - LastTime )) / CLOCKS_PER_SEC;
	LastTime = currTime;

	ptrApp->Execute( elapsedTime );

	glutSetWindowTitle( ptrApp->getTitle().c_str() );
	glutPostRedisplay();
}

/**
   \fn main()
   \brief Funcao principal representando o ponto de inicio da execu�ao do codigo fonte
   \param argc quantidade de argumentos passados atraves de linha de comando de execucao
   \param argv lista contendo os argumentos passados por linha de comando
   \return int flag que indica sucesso ou falha na execucao da aplicacao
*/
int main( int argc, char ** argv )
{
	ptrApp = new Application();

	// inicializa�ao do ambiente da GLUT
	glutInit( &argc, argv );
	glutInitWindowSize( ptrApp->getWidth(), ptrApp->getHeight() );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutCreateWindow( ptrApp->getTitle().c_str() );

	OnStartGL();

	// define as funcoes callback do sistema
	glutDisplayFunc( OnRenderEvent );
	glutReshapeFunc( OnReshapeEvent );
	glutKeyboardFunc( OnKeyboardEvent );
	glutSpecialFunc( OnSpecialKeyboardEvent );
	glutMouseFunc( OnMouseButtonEvent );
	glutMotionFunc( OnMouseMotionEvent );
	glutIdleFunc( OnIdleEvent );

	glutMainLoop();

	return 1;
}
