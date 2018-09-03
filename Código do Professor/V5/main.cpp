/**
	\file main.cpp
	\brief Modulo principal responsavel pela inicializacao do programa.<p>

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Fevereiro, 2015. Universidade do Estado de Santa Catarina (UDESC)
*/

#define _DEBUG_ 0
#define _LINUX_
#define _SPEED_ 19 //< No linux, 19, No Windows 1




#include <stdlib.h>
//#include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include "Application.h"
#include "Camera.h"
#include "PrimitiveGL.h"
#include "Fence.h"
#include "Tree.h"
#include "House.h"
#include "Robot.h"
#include "Helix.h"
#include "AttrVector3.h"
#include "LinearInterpolator.h"
#include "BlockingInterpolator.h"
#include "Animator.h"

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
	ptrCamera->setTranslate( Vector3( 5.0f, 5.0f, -12.0f ));
	ptrApp->addEntity( ptrCamera );


    // **********************************************************
    //                               GROUND
    // **********************************************************
	PrimitiveGL * ptrGround = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrGround->setScale( Vector3( 8.0f, 0.05f, 8.0f ));
	ptrGround->setColor( Vector3::GREEN );
	ptrApp->addEntity( ptrGround );

    // **********************************************************
    //                                CERCA
    // **********************************************************
    Fence * ptrFence = new Fence();
    ptrFence->setTranslate( Vector3( -1.0f, 0.0f, -3.0f ));
    ptrApp->addEntity( ptrFence );

    Fence * ptrFence1 = new Fence();
    ptrFence1->setTranslate( Vector3( -2.55f, 0.0f, -3.0f ));
    ptrApp->addEntity( ptrFence1 );

    Fence * ptrFence2 = new Fence();
    ptrFence2->setTranslate( Vector3( -1.0f, 0.0f, 0.5f ));
    ptrApp->addEntity( ptrFence2 );

    Fence * ptrFence3 = new Fence();
    ptrFence3->setTranslate( Vector3( -2.55f, 0.0f, 0.5f ));
    ptrApp->addEntity( ptrFence3 );

    Fence * ptrFence4 = new Fence();
    ptrFence4->setTranslate( Vector3( -0.2f, 0.0f, -0.5f ));
    ptrFence4->setRotate( Vector3( 0.0f, 90.0f, 0.0f ));
    ptrApp->addEntity( ptrFence4 );

    Fence * ptrFence5 = new Fence();
    ptrFence5->setTranslate( Vector3( -3.3f, 0.0f, -0.5f ));
    ptrFence5->setRotate( Vector3( 0.0f, 90.0f, 0.0f ));
    ptrApp->addEntity( ptrFence5 );

    Fence * ptrFence6 = new Fence();
    ptrFence6->setTranslate( Vector3( -3.3f, 0.0f, -2.2f ));
    ptrFence6->setRotate( Vector3( 0.0f, 90.0f, 0.0f ));
    ptrApp->addEntity( ptrFence6 );

    // **********************************************************
    //                                ARVORE
    // **********************************************************
    Tree * ptrTree = new Tree();
    ptrTree->setTranslate( Vector3( 2.0f, 0.0f, 2.0f ));
    //ptrTree->setPivot( Vector3( 0.0f, 1.0f, 0.0f ));
    ptrTree->setRotate( Vector3( 180.0f, 0.0f, 0.0f ));
    ptrApp->addEntity( ptrTree );

    Tree * ptrTree1 = new Tree();
    ptrTree1->setTranslate( Vector3( 2.9f, 0.0f, -4.2f ));
    ptrApp->addEntity( ptrTree1 );

    Tree * ptrTree2 = new Tree();
    ptrTree2->setTranslate( Vector3( -1.0f, 0.0f, -0.3f ));
    ptrTree2->setScale( Vector3( 0.5f, 0.5f, 0.5f ));
    ptrApp->addEntity( ptrTree2 );

    // **********************************************************
    //                                CASA
    // **********************************************************
    House * ptrHouse = new House();
    ptrHouse->setTranslate( Vector3( -2.2f, 0.0f, 0.0f ));
    ptrHouse->setScale( Vector3( 0.85f, 1.5f, 0.85f ));
    ptrApp->addEntity( ptrHouse );

    // **********************************************************
    //                            ACTOR: ROBOT 2
    // **********************************************************
    AttrVector3 * ptrRobotPos1 = new AttrVector3( Vector3( 0.0f, 0.3f, 0.0f ), 0.0f, PoseAttr::TRANSLATE );
    AttrVector3 * ptrRobotPos2 = new AttrVector3( Vector3( 4.0f, 0.3f, 0.0f ), 6.0f, PoseAttr::TRANSLATE );
    AttrVector3 * ptrRobotPos3 = new AttrVector3( Vector3( -4.0f, 0.3f, 1.0f ), 12.0f, PoseAttr::TRANSLATE );
    AttrVector3 * ptrRobotPos4 = new AttrVector3( Vector3( 0.0f, 0.3f, -2.0f ), 18.0f, PoseAttr::TRANSLATE );
    AttrVector3 * ptrRobotPos5 = new AttrVector3( Vector3( 0.0f, 0.3f, 0.0f ), 24.0f, PoseAttr::TRANSLATE );

    BlockingInterpolator * ptrBlckInterp = new BlockingInterpolator();
    ptrBlckInterp->addAttribute( ptrRobotPos1 );
    ptrBlckInterp->addAttribute( ptrRobotPos2 );
    ptrBlckInterp->addAttribute( ptrRobotPos3 );
    ptrBlckInterp->addAttribute( ptrRobotPos4 );
    ptrBlckInterp->addAttribute( ptrRobotPos5 );

    Animator *  ptrJumperAnimator = new Animator( Animator::LOOP );
    ptrJumperAnimator->addInterpolator( ptrBlckInterp );

    Robot * ptrRobotJumper = new Robot();
    ptrRobotJumper->setScale( Vector3( 0.25f, 0.25f, 0.25f ));
    ptrRobotJumper->setAnimator( ptrJumperAnimator );
    ptrApp->addEntity( ptrRobotJumper );

    // **********************************************************
    //                            ACTOR: ROBOT
    // **********************************************************
    AttrVector3 * ptrRobotOrientation00 = new AttrVector3( Vector3(), 0.0f, PoseAttr::ROTATE ); // tempo: 0 seg
    AttrVector3 * ptrRobotOrientation01 = new AttrVector3( Vector3(), 6.0f, PoseAttr::ROTATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinear0 = new LinearInterpolator();
    ptrLinear0->addAttribute( ptrRobotOrientation00 );
    ptrLinear0->addAttribute( ptrRobotOrientation01 );

    AttrVector3 * ptrRobotPosition1 = new AttrVector3( Vector3( 0.0f, 0.3f, 3.0f ), 0.0f, PoseAttr::TRANSLATE ); // tempo: 0 seg
    AttrVector3 * ptrRobotPosition2 = new AttrVector3( Vector3( 0.0f, 0.3f, -2.0f ), 6.0f, PoseAttr::TRANSLATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinear1 = new LinearInterpolator();
    ptrLinear1->addAttribute( ptrRobotPosition1 );
    ptrLinear1->addAttribute( ptrRobotPosition2 );

    AttrVector3 * ptrRobotOrientation1 = new AttrVector3( Vector3(), 7.0f, PoseAttr::ROTATE ); // tempo: 0 seg
    AttrVector3 * ptrRobotOrientation2 = new AttrVector3( Vector3( 0.0f, -270.0f, 0.0f ), 8.5f, PoseAttr::ROTATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinear2 = new LinearInterpolator();
    ptrLinear2->addAttribute( ptrRobotOrientation1 );
    ptrLinear2->addAttribute( ptrRobotOrientation2 );

    AttrVector3 * ptrRobotPosition3 = new AttrVector3( Vector3( 0.0f, 0.3f, -2.0f ), 10.0f, PoseAttr::TRANSLATE ); // tempo: 0 seg
    AttrVector3 * ptrRobotPosition4 = new AttrVector3( Vector3( -2.2f, 0.3f, -2.0f ), 15.0f, PoseAttr::TRANSLATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinear3 = new LinearInterpolator();
    ptrLinear3->addAttribute( ptrRobotPosition3 );
    ptrLinear3->addAttribute( ptrRobotPosition4 );

    Animator *  ptrRobotAnimator = new Animator( Animator::ONCE );
    ptrRobotAnimator->addInterpolator( ptrLinear0 );
    ptrRobotAnimator->addInterpolator( ptrLinear1 );
    ptrRobotAnimator->addInterpolator( ptrLinear2 );
    ptrRobotAnimator->addInterpolator( ptrLinear3 );

    Robot * ptrRobot = new Robot();
    ptrRobot->setScale( Vector3( 0.5f, 0.5f, 0.5f ));
    ptrRobot->setAnimator( ptrRobotAnimator );
    ptrApp->addEntity( ptrRobot );

    // **********************************************************
    //                            ACTOR: HELIX
    // **********************************************************
    AttrVector3 * ptrHelixOrientation0 = new AttrVector3( Vector3( 0.0f, 0.0f, 0.0f ), 0.0f, PoseAttr::ROTATE ); // tempo: 0 seg
    AttrVector3 * ptrHelixOrientation1 = new AttrVector3( Vector3( 0.0f, 0.0f, 360.0f ), 15.0f, PoseAttr::ROTATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinearHelix = new LinearInterpolator();
    ptrLinearHelix->addAttribute( ptrHelixOrientation0 );
    ptrLinearHelix->addAttribute( ptrHelixOrientation1 );

    Animator *  ptrHelixAnimator = new Animator( Animator::LOOP );
    ptrHelixAnimator->addInterpolator( ptrLinearHelix );

    Helix * ptrHelix = new Helix();
    ptrHelix->setTranslate( Vector3( -2.0f, 0.8f, -1.0f ));
    ptrHelix->setRotate( Vector3( 0.0f, -90.0f, 0.0f ));
    ptrHelix->setScale( Vector3( 2.0f, 2.0f, 1.0f ));
    ptrHelix->setAnimator( ptrHelixAnimator );
    ptrApp->addEntity( ptrHelix );
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

	ptrApp->Execute( elapsedTime*_SPEED_ );

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
