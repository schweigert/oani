
#include <stdlib.h>
#include <stdio.h>
// #include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include "Application.h"
#include "Camera.h"
#include "PrimitiveGL.h"
#include "Fence.h"
#include "Tree.h"
#include "House.h"
#include "Robot.h"
#include "PoseAttr.h"
#include "LinearInterpolator.h"
#include "Animator.h"
#include "WavefrontObject.h"

Application   * ptrApp   = NULL;

clock_t         LastTime;


void OnStartGL()
{
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
   	glEnable( GL_DEPTH_TEST );
   	glEnable( GL_COLOR_MATERIAL );
   	glCullFace( GL_BACK );

	glShadeModel( GL_SMOOTH );
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
    //                               TESTE
    // **********************************************************

  WavefrontObject* teste = new WavefrontObject("Mesh/Tree000.obj");
  //ptrApp->addEntity(teste);

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
    ptrHouse->setTranslate( Vector3( -2.2f, 0.0f, -0.5f ));
    //ptrHouse->setScale( Vector3( 0.85f, 0.85f, 0.85f ));
    ptrApp->addEntity( ptrHouse );

    // **********************************************************
    //                            ACTOR: ROBOT
    // **********************************************************
    PoseAttr oRobotPosition1( Vector3( 0.0f, 0.3f, 3.0f ), 0.0f, PoseAttr::TRANSLATE ); // tempo: 0 seg
    PoseAttr oRobotPosition2( Vector3( 0.0f, 0.3f, -2.0f ), 6.0f, PoseAttr::TRANSLATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinear1 = new LinearInterpolator();
    ptrLinear1->addAttribute( oRobotPosition1 );
    ptrLinear1->addAttribute( oRobotPosition2 );

    PoseAttr oRobotOrientation1( Vector3(), 7.0f, PoseAttr::ROTATE ); // tempo: 0 seg
    PoseAttr oRobotOrientation2( Vector3( 0.0f, -270.0f, 0.0f ), 8.5f, PoseAttr::ROTATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinear2 = new LinearInterpolator();
    ptrLinear2->addAttribute( oRobotOrientation1 );
    ptrLinear2->addAttribute( oRobotOrientation2 );

    PoseAttr oRobotPosition3( Vector3( 0.0f, 0.3f, -2.0f ), 10.0f, PoseAttr::TRANSLATE ); // tempo: 0 seg
    PoseAttr oRobotPosition4( Vector3( -2.2f, 0.3f, -2.0f ), 15.0f, PoseAttr::TRANSLATE ); // tempo: 1 seg

    LinearInterpolator * ptrLinear3 = new LinearInterpolator();
    ptrLinear3->addAttribute( oRobotPosition3 );
    ptrLinear3->addAttribute( oRobotPosition4 );

    Animator * ptrRobotAnimator = new Animator();
    ptrRobotAnimator->addInterpolator( ptrLinear1 );
    ptrRobotAnimator->addInterpolator( ptrLinear2 );
    ptrRobotAnimator->addInterpolator( ptrLinear3 );

    Robot * ptrRobot = new Robot();
    ptrRobot->setScale( Vector3( 0.5f, 0.5f, 0.5f ));
    ptrRobot->setAnimator( ptrRobotAnimator );
    ptrApp->addEntity( ptrRobot );

}


void OnFinishGL()
{}


void OnRenderEvent()
{
	ptrApp->RenderFrame();
}


void OnReshapeEvent( GLint uiWidth, GLint uiHeight )
{
	ptrApp->setWindowSize( uiWidth, uiHeight );
}


void OnKeyboardEvent( unsigned char ucKey, int iMouseX, int iMouseY )
{
	switch( ucKey )
	{
	// ESC
	case 27:
		OnFinishGL();
		exit( 0 );
		break;

	}
}


void OnSpecialKeyboardEvent( int iKey, int iMouseX, int iMouseY )
{
	switch( iKey )
	{
	case GLUT_KEY_LEFT: break;
	}
}


void OnMouseButtonEvent( int iButton, int iState, int iMouseX, int iMouseY )
{
	switch( iButton )
	{
	case GLUT_LEFT_BUTTON:
		if( iState == GLUT_DOWN )
		{
		}
		break;
	}
}


void OnMouseMotionEvent( int iMouseX, int iMouseY )
{}

void OnIdleEvent()
{
	clock_t currTime = clock();
	double elapsedTime = (( double) ( currTime - LastTime )) / CLOCKS_PER_SEC;
	LastTime = currTime;

	ptrApp->Execute( elapsedTime*19 );

	glutSetWindowTitle( ptrApp->getTitle().c_str() );
	glutPostRedisplay();
}


int main( int argc, char ** argv )
{
	ptrApp = new Application();


	glutInit( &argc, argv );
	glutInitWindowSize( ptrApp->getWidth(), ptrApp->getHeight() );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutCreateWindow( ptrApp->getTitle().c_str() );

	OnStartGL();


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
