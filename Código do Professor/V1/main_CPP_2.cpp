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

    GLfloat light_position[] = { 1.0, 3.0, -10.0, 0.0 },
            light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );

    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	LastTime = clock();

	Camera * ptrCamera = new Camera();
	ptrCamera->setTranslate( Vector3( 0.0f, 3.0f, -8.0f ));
	ptrApp->addEntity( ptrCamera );


    // **********************************************************
    //                               GROUND
    // **********************************************************
	PrimitiveGL * ptrGround = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrGround->setScale( Vector3( 4.0f, 0.05f, 4.0f ));
	ptrGround->setColor( Vector3::GREEN );
	ptrApp->addEntity( ptrGround );

    // **********************************************************
    //                                CERCA
    // **********************************************************
	PrimitiveGL * ptrFence1 = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrFence1->setSize( 0.5f );
	ptrFence1->setScale( Vector3( 0.2f, 1.0f, 0.05f ));
	ptrFence1->setTranslate( Vector3( 0.0f, 0.5f, -2.0f ));
	ptrFence1->setColor( Vector3( 0.46f, 0.38f, 0.25f ) ); // marrom RGB(119, 98, 66)
	ptrApp->addEntity( ptrFence1 );

	PrimitiveGL * ptrFence2 = new PrimitiveGL( ptrFence1 );
	ptrFence2->setTranslate( Vector3( 0.25f, 0.5f, -2.0f ));
	ptrApp->addEntity( ptrFence2 );

	PrimitiveGL * ptrFence3 = new PrimitiveGL( ptrFence1 );
	ptrFence3->setTranslate( Vector3( 0.5f, 0.5f, -2.0f ));
	ptrApp->addEntity( ptrFence3 );

	PrimitiveGL * ptrFence4 = new PrimitiveGL( ptrFence1 );
	ptrFence4->setTranslate( Vector3( 0.75f, 0.5f, -2.0f ));
	ptrApp->addEntity( ptrFence4 );

	PrimitiveGL * ptrFence5 = new PrimitiveGL( ptrFence1 );
	ptrFence5->setTranslate( Vector3( 1.0f, 0.5f, -2.0f ));
	ptrApp->addEntity( ptrFence5 );

	PrimitiveGL * ptrFence6 = new PrimitiveGL( ptrFence1 );
	ptrFence6->setTranslate( Vector3( 1.25f, 0.5f, -2.0f ));
	ptrApp->addEntity( ptrFence6 );

	PrimitiveGL * ptrFence7 = new PrimitiveGL( ptrFence1 );
	ptrFence7->setScale( Vector3( 3.0f, 0.2f, 0.05f ));
	ptrFence7->setTranslate( Vector3( 0.62f, 0.4f, -2.0f ));
	ptrApp->addEntity( ptrFence7 );

	PrimitiveGL * ptrFence8 = new PrimitiveGL( ptrFence1 );
	ptrFence8->setScale( Vector3( 3.0f, 0.2f, 0.05f ));
	ptrFence8->setTranslate( Vector3( 0.62f, 0.6f, -2.0f ));
	ptrApp->addEntity( ptrFence8 );

    // **********************************************************
    //                                ARVORE
    // **********************************************************
	PrimitiveGL * ptrTrunk = new PrimitiveGL( ptrFence1 );
	ptrTrunk->setScale( Vector3( 0.35f, 1.5f, 0.35f ));
	ptrTrunk->setTranslate( Vector3( 1.0f, 0.75f, 0.0f ));
	ptrApp->addEntity( ptrTrunk );

	PrimitiveGL * ptrTree = new PrimitiveGL( PrimitiveGL::ICOSAHEDRON );
	ptrTree->setColor( (( Vector3 ) Vector3::GREEN ) * 0.35f ); // verde 15%
	ptrTree->setScale( Vector3( 0.5f, 0.5f, 0.5f ));
	ptrTree->setTranslate( Vector3( 1.0f, 1.5f, 0.0f ));
	ptrApp->addEntity( ptrTree );

    // **********************************************************
    //                                CASA
    // **********************************************************
	PrimitiveGL * ptrHouse = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrHouse->setScale( Vector3( 1.0f, 0.7f, 1.0f ));
	ptrHouse->setTranslate( Vector3( -1.0f, 0.35f, -0.5f ));
	ptrApp->addEntity( ptrHouse );

	PrimitiveGL * ptrRoof = new PrimitiveGL( PrimitiveGL::CONE );
	ptrRoof->setResolution( 4, 4 );
	ptrRoof->setScale( Vector3( 1.0f, 1.0f, 0.4f ));
	ptrRoof->setColor( Vector3::YELLOW );
	ptrRoof->setTranslate( Vector3( -1.0f, 0.7f, -0.5f ));
	ptrRoof->setRotate( Vector3( -90.0f, 45.0f, 0.0f ) );
	ptrApp->addEntity( ptrRoof );

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
