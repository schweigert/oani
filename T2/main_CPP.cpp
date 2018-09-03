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

#include "LinearInterpolator.h"
#include "PolynomInterpolator.h"
#include "AttrVector3.h"
#include "PoseAttr.h"
#include "Animator.h"

#include "PrimitiveGL.h"
#include "Desk.h"
#include "Chair.h"
#include "Table.h"
#include "Cat.h"
#include "Robot.h"
#include "Aquarium.h"

#include "Fish.h"

#include "Joint.h"

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


	   glShadeModel( GL_SMOOTH ); // ativa o modo de rendering suavizado = n�o facetado
     glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);


     glEnable(GL_LIGHT0);
     glEnable(GL_LIGHTING);

     glEnable(GL_DEPTH_TEST);
     glShadeModel(GL_SMOOTH);

     glEnable( GL_COLOR_MATERIAL );
    	glCullFace( GL_BACK );

    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	LastTime = clock();

  // ****************************************************
  //                  CAMERA
  // ****************************************************

  {

  	Camera * ptrCamera = new Camera();
  	ptrCamera->setTranslate( Vector3( 10.0f, 5.0f, 20.0f ));

  	ptrCamera->setClippingPlanes( 1.0f, 300.0f );
  	ptrApp->addEntity( ptrCamera );
  }

  // ****************************************************
  //                  CHÃO E PAREDES
  // ****************************************************
  // I e J será respectivamente o tamanho da sala
  for(float i = 0; i < 11; i++)
  {
    for (float j = 0; j < 11; j++){
      PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
      ptrBase->setScale( Vector3( 1.0f, 0.3f, 1.0f ));
      ptrBase->setTranslate (Vector3(i-2.5f,-0.15f,j-2.5f));
      ptrBase->setColor( Vector3(72.0/255.0,24.0/255.0,20.0/255.0) );
      if((int)j % 2 == (int)i % 2 ){
        ptrBase->setColor( Vector3(90.0/255.0,42.0/255.0,34.0/255.0) );
      }
      ptrApp->addEntity( ptrBase );
    }
  }

  {
    // Parede 001
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 12.0f, 5.0f, 0.3f ));
    ptrBase->setTranslate (Vector3(2.5f,2.5f,-2.0f));
    ptrBase->setColor(Vector3(21.0/255.0,125.0/255.0,3.0/255.0)  );
    ptrApp->addEntity( ptrBase );
  }

  {
    // Parede 002
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 12.0f, 5.0f, 0.3f ));
    ptrBase->setTranslate (Vector3(-3.0f,2.5f,2.0f));
    ptrBase->setRotate (Vector3(0,90.0f,0));
    ptrBase->setColor( Vector3(51.0/255.0,145.0/255.0,23.0/255.0) );
    ptrApp->addEntity( ptrBase );
  }

  // ****************************************************
  //                  ARMÁRIOS
  // ****************************************************

  {
    Desk* ptrDesk = new Desk();
    ptrDesk->setTranslate(Vector3(0,0,-1.5f));
    ptrApp->addEntity(ptrDesk);
  }

  {
    Desk* ptrDesk = new Desk();
    ptrDesk->setTranslate(Vector3(-1.75f,0,1.5f));
    ptrDesk->setRotate(Vector3(0,90,0));
    ptrApp->addEntity(ptrDesk);
  }

  {
    Table* ptrTable = new Table();
    ptrTable->setTranslate(Vector3(3.0f,0,3.0f));
    ptrTable->setRotate(Vector3(0,90,0));
    ptrApp->addEntity(ptrTable);
  }


  {
    Chair* ptrChair = new Chair();
    ptrChair->setTranslate(Vector3(5.0, 0.0,6.0));
    ptrChair->setRotate(Vector3(0,0,0));
    ptrApp->addEntity(ptrChair);
  }

  {
    Aquarium* ptrAquarium = new Aquarium();
    ptrAquarium->setTranslate(Vector3(0, 2.15,-1.5f));
    ptrAquarium->setRotate(Vector3(0,0,0));
    ptrApp->addEntity(ptrAquarium);
  }

  // ***********************************************
  //        Cat
  // ***********************************************

  {
    // Andar até a cadeira
    AttrVector3* attrCat0001 = new AttrVector3(Vector3(1,0,6),0.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0002 = new AttrVector3(Vector3(3,0,6),4.0f, PoseAttr::TRANSLATE);

    LinearInterpolator* intCat01 = new LinearInterpolator ();
    intCat01->addAttribute(attrCat0001);
    intCat01->addAttribute(attrCat0002);

    // Antecipar pulo
    AttrVector3* attrCat0201 = new AttrVector3(Vector3(3.0,0,6),5.5f, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0202 = new AttrVector3(Vector3(2.8,0,6),6.0f, PoseAttr::TRANSLATE);

    LinearInterpolator* intCat03 = new LinearInterpolator ();
    intCat03->addAttribute(attrCat0201);
    intCat03->addAttribute(attrCat0202);

    // Pular na cadeira
    AttrVector3* attrCat0101 = new AttrVector3(Vector3(2.8f,0.0f,6.0f),6.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0102 = new AttrVector3(Vector3(4.5f,1.5f,6.0f),6.5f, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0103 = new AttrVector3(Vector3(5.0f,1.05f,6.0f),7.0f, PoseAttr::TRANSLATE);

    PolynomInterpolator* intCat02 = new PolynomInterpolator(PoseAttr::TRANSLATE,6.0,7.0);
    intCat02->addAttribute(attrCat0101);
    intCat02->addAttribute(attrCat0102);
    intCat02->addAttribute(attrCat0103);
    intCat02->Setup();

    // Rotacionar pra mesa
    AttrVector3* attrCat0401 = new AttrVector3(Vector3(0,180,0),7.0f, PoseAttr::ROTATE);
    AttrVector3* attrCat0402 = new AttrVector3(Vector3(0,0,0),8.0f, PoseAttr::ROTATE);
    AttrVector3* attrCat0403 = new AttrVector3(Vector3(0,-90,0),10.0f, PoseAttr::ROTATE);

    PolynomInterpolator* intCat04 = new PolynomInterpolator(PoseAttr::ROTATE,7.0,10.0);
    intCat04->addAttribute(attrCat0401);
    intCat04->addAttribute(attrCat0402);
    intCat04->addAttribute(attrCat0403);
    intCat04->Setup();

    // Antecipar pulo na cadeira
    AttrVector3* attrCat0501 = new AttrVector3(Vector3(5,1.1,6),10.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0502 = new AttrVector3(Vector3(5,1.1,6.5),12.0f, PoseAttr::TRANSLATE);

    LinearInterpolator* intCat05 = new LinearInterpolator ();
    intCat05->addAttribute(attrCat0501);
    intCat05->addAttribute(attrCat0502);

    // Pular na mesa
    AttrVector3* attrCat0601 = new AttrVector3(Vector3(5,1.1,6.5),12.0, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0602 = new AttrVector3(Vector3(5,2.3,5.0),12.3, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0603 = new AttrVector3(Vector3(5.0f,1.75,4.0),12.6, PoseAttr::TRANSLATE);

    PolynomInterpolator* intCat06 = new PolynomInterpolator(PoseAttr::TRANSLATE,12.0,12.6);
    intCat06->addAttribute(attrCat0601);
    intCat06->addAttribute(attrCat0602);
    intCat06->addAttribute(attrCat0603);
    intCat06->Setup();

    // Andar na Mesa
    AttrVector3* attrCat0701 = new AttrVector3(Vector3(5.0f,1.75,4.0),12.6, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0702 = new AttrVector3(Vector3(5.0f,1.75,2.0),16.0, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0703 = new AttrVector3(Vector3(3.4f,1.75,3.0),19.0, PoseAttr::TRANSLATE);
    AttrVector3* attrCat0704 = new AttrVector3(Vector3(2.0f,1.75,2.0),21.0, PoseAttr::TRANSLATE);

    PolynomInterpolator* intCat07 = new PolynomInterpolator(PoseAttr::TRANSLATE,12.6,21.0);
    intCat07->addAttribute(attrCat0701);
    intCat07->addAttribute(attrCat0702);
    intCat07->addAttribute(attrCat0703);
    intCat07->addAttribute(attrCat0704);
    intCat07->Setup();

    // Rotacionar na Mesa
    AttrVector3* attrCat0801 = new AttrVector3(Vector3(0,-90,0),15.0, PoseAttr::ROTATE);
    AttrVector3* attrCat0802 = new AttrVector3(Vector3(0,0,0),16.0, PoseAttr::ROTATE);
    AttrVector3* attrCat0803 = new AttrVector3(Vector3(0,30,0),16.2, PoseAttr::ROTATE);

    PolynomInterpolator* intCat08 = new PolynomInterpolator(PoseAttr::ROTATE,15.0,16.2);
    intCat08->addAttribute(attrCat0801);
    intCat08->addAttribute(attrCat0802);
    intCat08->addAttribute(attrCat0803);
    intCat08->Setup();

    // Rotacionar na Mesa 2
    AttrVector3* attrCat0901 = new AttrVector3(Vector3(0,30,0),19.0, PoseAttr::ROTATE);
    AttrVector3* attrCat0902 = new AttrVector3(Vector3(0,0,0),20.0, PoseAttr::ROTATE);
    AttrVector3* attrCat0903 = new AttrVector3(Vector3(0,-60,0),21.2, PoseAttr::ROTATE);

    PolynomInterpolator* intCat09 = new PolynomInterpolator(PoseAttr::ROTATE,19.0,21.2);
    intCat09->addAttribute(attrCat0901);
    intCat09->addAttribute(attrCat0902);
    intCat09->addAttribute(attrCat0903);
    intCat09->Setup();


    // Adicionar todos os interpoladores
    Animator* catAnimator = new Animator ();
    catAnimator->addInterpolator(intCat01);
    catAnimator->addInterpolator(intCat02);
    catAnimator->addInterpolator(intCat03);
    catAnimator->addInterpolator(intCat04);
    catAnimator->addInterpolator(intCat05);
    catAnimator->addInterpolator(intCat06);
    catAnimator->addInterpolator(intCat07);
    catAnimator->addInterpolator(intCat08);
    catAnimator->addInterpolator(intCat09);



    Cat* ptrCat = new Cat();
    ptrCat->setRotate(Vector3(0,180,0));
    ptrCat->setAnimator(catAnimator);


    ptrApp->addEntity(ptrCat);

  }

  {
    Animator* fishAnimator = new Animator(Animator::LOOP);

    AttrVector3* attrFish00101 = new AttrVector3(Vector3(0,3.2,0),0.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrFish00102 = new AttrVector3(Vector3(0,3.0,0.5),5.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrFish00103 = new AttrVector3(Vector3(0,3.2,-0.1),6.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrFish00104 = new AttrVector3(Vector3(0,3.5,-0.8),9.0f, PoseAttr::TRANSLATE);

    PolynomInterpolator* intFish001 = new PolynomInterpolator(PoseAttr::TRANSLATE,0.0,9.0);
    intFish001->addAttribute(attrFish00101);
    intFish001->addAttribute(attrFish00102);
    intFish001->addAttribute(attrFish00103);
    intFish001->addAttribute(attrFish00104);
    intFish001->Setup();



    fishAnimator->addInterpolator(intFish001);

    {
      AttrVector3* attrFishR0001 = new AttrVector3(Vector3(0,0,0),3.0f, PoseAttr::ROTATE);
      AttrVector3* attrFishR0002 = new AttrVector3(Vector3(0,180,0),4.0f, PoseAttr::ROTATE);

      LinearInterpolator* intFishR01 = new LinearInterpolator ();
      intFishR01->addAttribute(attrFishR0001);
      intFishR01->addAttribute(attrFishR0002);
      fishAnimator->addInterpolator(intFishR01);
    }

    {
      AttrVector3* attrFishR0001 = new AttrVector3(Vector3(0,180,0),6.0f, PoseAttr::ROTATE);
      AttrVector3* attrFishR0002 = new AttrVector3(Vector3(0,0,0),8.0f, PoseAttr::ROTATE);

      LinearInterpolator* intFishR01 = new LinearInterpolator ();
      intFishR01->addAttribute(attrFishR0001);
      intFishR01->addAttribute(attrFishR0002);
      fishAnimator->addInterpolator(intFishR01);
    }
    AttrVector3* attrFish00201 = new AttrVector3(Vector3(0,3.5,-0.8),9.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrFish00202 = new AttrVector3(Vector3(0,2.8,-0.5),14.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrFish00203 = new AttrVector3(Vector3(0,3.0,-0.1),18.0f, PoseAttr::TRANSLATE);
    AttrVector3* attrFish00204 = new AttrVector3(Vector3(0,3.2,0),25.0f, PoseAttr::TRANSLATE);

    PolynomInterpolator* intFish002 = new PolynomInterpolator(PoseAttr::TRANSLATE,9.0,25.0);
    intFish002->addAttribute(attrFish00201);
    intFish002->addAttribute(attrFish00202);
    intFish002->addAttribute(attrFish00203);
    intFish002->addAttribute(attrFish00204);
    intFish002->Setup();


    fishAnimator->addInterpolator(intFish002);

    Fish* ptrFish= new Fish();
    ptrFish->setTranslate(Vector3(3,3,3));
    ptrFish->setAnimator(fishAnimator);
    ptrApp->addEntity(ptrFish);
  }


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
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
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
