/**
	\file main.cpp
	\brief Modulo principal responsavel pela inicializacao do programa.<p>

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Fevereiro, 2015. Universidade do Estado de Santa Catarina (UDESC)
*/

#include <stdlib.h>
//#include <windows.h>
#include <GL/glut.h>
#include <time.h>

#include "Application.h"
#include "Camera.h"

#include "Planet.h"

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

    GLfloat light_position[] = { 1.0, 3.0, 100.0, 0.0 },
            light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );

    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	LastTime = clock();

	Camera * ptrCamera = new Camera();
	ptrCamera->setTranslate( Vector3( 5.0f, 5.0f, 120.0f ));
	ptrCamera->setClippingPlanes( 1.0f, 250.0f );
	ptrApp->addEntity( ptrCamera );

    // **********************************************************
    //                          ACTOR: MOON
    // **********************************************************
    Planet * ptrMoon = new Planet( false, true );
    ptrMoon->setTranslate( Vector3( 2.7f, 0.0f, 0.0f ));
    ptrMoon->setScale( Vector3( 0.3f, 0.3f, 0.3f ));
    ptrMoon->setYearAnimation( 0.0f, 1.0f );
    ptrMoon->Initialize();
    ptrMoon->setColor( Vector3( 0.6f, 0.6f, 0.6f ) );

    // **********************************************************
    //                          ACTOR: EARTH
    // **********************************************************
    Planet * ptrEarth = new Planet( );
    ptrEarth->setTranslate( Vector3( 20.0f, 0.0f, 0.0f ));
    ptrEarth->setDayAnimation( 0.0f, 2.0f );
    ptrEarth->setYearAnimation( 0.0f, 9.0f );
    ptrEarth->Initialize();
    ptrEarth->setColor( Vector3::BLUE );
    ptrEarth->Attach( ptrMoon );

    // **********************************************************
    //                          ACTOR: FOBOS
    // **********************************************************
    Planet * ptrFobos = new Planet( false, true );
    ptrFobos->setTranslate( Vector3( 2.7f, 0.0f, 0.0f ));
    ptrFobos->setScale( Vector3( 0.3f, 0.3f, 0.3f ));
    ptrFobos->setYearAnimation( 0.0f, 3.5f );
    ptrFobos->Initialize();
    ptrFobos->setColor( Vector3( 0.6f, 0.6f, 0.6f ) );

    // **********************************************************
    //                          ACTOR: DEIMOS
    // **********************************************************
    Planet * ptrDeimos = new Planet( false, true );
    ptrDeimos->setTranslate( Vector3( 3.5f, 0.0f, 0.0f ));
    ptrDeimos->setScale( Vector3( 0.4f, 0.4f, 0.4f ));
    ptrDeimos->setYearAnimation( 0.0f, 5.5f );
    ptrDeimos->Initialize();
    ptrDeimos->setColor( Vector3( 0.7f, 0.7f, 0.7f ) );

    // **********************************************************
    //                          ACTOR: MARS
    // **********************************************************
    Planet * ptrMars = new Planet( );
    ptrMars->setTranslate( Vector3( 33.0f, 0.0f, 0.0f ));
    ptrMars->setDayAnimation( 0.0f, 2.0f );
    ptrMars->setYearAnimation( 0.0f, 17.0f );
    ptrMars->Initialize();
    ptrMars->setColor( Vector3::RED );
    ptrMars->Attach( ptrFobos );
    ptrMars->Attach( ptrDeimos );

    // **********************************************************
    //                          ACTOR: SUN
    // **********************************************************
    Planet * ptrSun = new Planet( true, false );
    ptrSun->setScale( Vector3( 5.0f, 5.0f, 5.0f ));
    ptrSun->setDayAnimation( 0.0f, 120.0f );
    ptrSun->Initialize();
    ptrSun->setColor( Vector3::YELLOW );
    ptrSun->Attach( ptrEarth );
    ptrSun->Attach( ptrMars );

	ptrApp->addEntity( ptrSun );
}

/**
	\fn OnFinishGL
	\brief Finaliza o ambiente OPENGL antes de encerrar a aplicacao
*/
void OnFinishGL()
{}

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

	ptrApp->Execute( elapsedTime*19 );

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
