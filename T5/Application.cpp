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
// includes da aplica��o
#include "Camera.h"
#include "Vector3.h"
#include "LightSource.h"
#include "VectorAttribute.h"
#include "BRep.h"
#include "RigidBody.h"
#include "Fire.h"
#include "Smoke.h"
#include "Water.h"
#include "Rain.h"

/**
	\brief Construtor default para a classe Application
*/
Application::Application( string strAppName ):
    uiWindowWidth( 960 ), uiWindowHeight( 540 ), strCurrentFPS( "FPS: ?" ), dCounterTimer( 0.0 ), uiFrames( 0 )
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
  glClearColor(0.3, 0.3, 0.7, 1.0);
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

  Keyframing * ptrAnimation = new Keyframing( true );

  Interpolator::InterpolationType animType = Interpolator::LINEAR;

    string strPath = "./";

	printf("Montando a cena...\n");

	Camera * ptrCamera = new Camera();
	ptrCamera->setTranslate( Vector3( 15.0f, 3.0, 10.0f ) );
  ptrCamera->LookAt(Vector3(0,1,4));
	this->addEntity( ptrCamera );

  LightSource* ptrLight = new LightSource( 3, LightSource::POINT );
  ptrLight->setTranslate( Vector3( 0.3f, 2.0f, 5.0f ) );
  this->addEntity( ptrLight );


  {
    BRep * Tree = new BRep();
    Tree->LoadfromFile( strPath + "t3obj/Bonsai.obj" );
    Tree->setScale( (Vector3)Vector3::UNIT * 1.2f );
    Tree->setTranslate ( Vector3( - 7, 0, 8 ) );
    Tree->setRotate (Vector3 (0, 45, 0));
    this->addEntity( Tree );
    this->uiPolyCount += Tree->getPolyCount();
  }

  {
    BRep * Tree = new BRep();
    Tree->LoadfromFile( strPath + "t3obj/Bonsai.obj" );
    Tree->setScale( (Vector3)Vector3::UNIT * 1.4f );
    Tree->setTranslate ( Vector3( - 7, 0, 2 ) );
    this->addEntity( Tree );
    this->uiPolyCount += Tree->getPolyCount();
  }


  {
    BRep * Home = new BRep();
    Home->LoadfromFile( strPath + "t3obj/Home.obj" );
    Home->setScale( Vector3::UNIT );
    this->addEntity( Home );
    this->uiPolyCount += Home->getPolyCount();
  }

  {
    BRep * Door = new BRep();
    Door->LoadfromFile( strPath + "t3obj/Door.obj" );
    Door->setTranslate( Vector3(-0.25f,0,6) );
    this->addEntity( Door );
    this->uiPolyCount += Door->getPolyCount();

    // Animação da Porta

    Keyframing* DoorAnimation = new Keyframing();
    Door->setKeyframing(DoorAnimation);
    {
      Pose * ptrPoseDoor = new Pose();
      ptrPoseDoor->setTime( 40.0 );
      ptrPoseDoor->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      DoorAnimation->addPose( ptrPoseDoor, animType);
    }
    {
      Pose * ptrPoseDoor = new Pose();
      ptrPoseDoor->setTime( 44.0 );
      ptrPoseDoor->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 75.0f, 0.0f ) ) );
      DoorAnimation->addPose( ptrPoseDoor, animType);
    }
  }



  {
    // Quarium
    BRep * Quarium = new BRep();
    Quarium->LoadfromFile( strPath + "t3obj/quarium.obj" );
    Quarium->setTranslate(Vector3(1.6f, 1.5f, 0.9f));
    Quarium->setScale(Vector3(1,1,1)*0.7);
    this->addEntity( Quarium );
    this->uiPolyCount += Quarium->getPolyCount();
  }



  {
    // Box
    BRep * Box = new BRep();
    Box->LoadfromFile( strPath + "t3obj/box.obj" );
    Box->setTranslate(Vector3(2.0f, 0.0f, 2.0f));
    Box->setScale(Vector3(1,1,1)*0.4);
    this->addEntity( Box );
    this->uiPolyCount += Box->getPolyCount();


  }

  {
    BRep * Bench = new BRep();
    Bench->LoadfromFile( strPath + "t3obj/Bench.obj" );
    this->addEntity( Bench );
    this->uiPolyCount += Bench->getPolyCount();
  }


  ///////////////////////
  // EPITÁCIO
  ///////////////////////

  // Animação do Pivot do Epitacio
  Keyframing * ptrEptPivotAnimation = new Keyframing( );

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 0.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 9.0f, 0.0f, 9.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 90.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio, animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 2.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 9.0f, 0.0f, 3.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 90.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 3.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 7.0f, 0.0f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 6.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 3.0f, 0.0f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }
  // Preparar pulo
  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 7.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 3.2f, 0.0f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  // pular
  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 7.2 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 2.5f, 1.0f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  // Em cima da caixa
  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 7.3 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 2.2f, 0.8f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  // Rotacionar para descer

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 12.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 2.2f, 0.8f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 13.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 2.2f, 0.8f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 13.1 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 3.2f, 1.0f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 13.2 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 3.4f, 0.0f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 14.5 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 7.5f, 0.0f, 2.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 15.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 8.0f, 0.0f, 3.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -90.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 17.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 8.0f, 0.0f, 7.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -90.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 18.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 7.0f, 0.0f, 8.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 20.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 1.5f, 0.0f, 8.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -180.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  {
    Pose * ptrPoseEptacio = new Pose();
    ptrPoseEptacio->setTime( 22.0 );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "position", Vector3( 2.0f, 0.0f, 6.0f ) ) );
    ptrPoseEptacio->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -100.0f, 0.0f ) ) );
    ptrEptPivotAnimation->addPose( ptrPoseEptacio , animType);
  }

  Entity* EpitacioPivot = new Entity();
  EpitacioPivot->setScale(Vector3(1,1,1)*0.5f);
  EpitacioPivot->setKeyframing(ptrEptPivotAnimation);
  this->addEntity(EpitacioPivot);

//  ptrCamera->LookAt(EpitacioPivot);

  {


    // Animação do Pivot do Epitacio
    Keyframing * ptrBodyAnimation = new Keyframing( );
    Keyframing * ptrFeetDAnimation = new Keyframing( );
    Keyframing * ptrFeetEAnimation = new Keyframing( );
    Keyframing * ptrHandDAnimation = new Keyframing( );
    Keyframing * ptrHandEAnimation = new Keyframing( );
    Keyframing * ptrHeadAnimation = new Keyframing( );



    Entity* Epitacio = new Entity();
    EpitacioPivot->attach(Epitacio);


    BRep * Body = new BRep();
    Body->LoadfromFile( strPath + "t3objv2/eptacio_body.obj" );
    Body->setTranslate(Vector3(0,0.2f,0));
    Body->setKeyframing(ptrBodyAnimation);
    Epitacio->attach( Body );
    this->uiPolyCount += Body->getPolyCount();

    BRep * FeetD = new BRep();
    FeetD->LoadfromFile( strPath + "t3obj/feet.obj" );
    FeetD->setTranslate(Vector3(0,0,0.3f));
    FeetD->setKeyframing(ptrFeetDAnimation);
    Epitacio->attach( FeetD );
    this->uiPolyCount += FeetD->getPolyCount();

    BRep * FeetE = new BRep();
    FeetE->LoadfromFile( strPath + "t3obj/feet.obj" );
    FeetE->setTranslate(Vector3(0,0,-0.3f));
    FeetE->setKeyframing(ptrFeetEAnimation);
    Epitacio->attach( FeetE );
    this->uiPolyCount += FeetE->getPolyCount();

    BRep * HandD = new BRep();
    HandD->LoadfromFile( strPath + "t3obj/Eptacio_handD.obj" );
    HandD->setTranslate(Vector3(0,1.3f,0.7f));
    HandD->setKeyframing(ptrHandDAnimation);
    Body->attach( HandD );
    this->uiPolyCount += HandD->getPolyCount();

    BRep * HandE = new BRep();
    HandE->LoadfromFile( strPath + "t3obj/Eptacio_handE.obj" );
    HandE->setTranslate(Vector3(0,1.3f,-0.7f));
    HandE->setKeyframing(ptrHandEAnimation);
    Body->attach( HandE );
    this->uiPolyCount += HandE->getPolyCount();

    BRep * Head = new BRep();
    Head->LoadfromFile( strPath + "t3objv2/eptacio_head.obj" );
    Head->setTranslate(Vector3(0,1.3f,0.0f));
    Head->setKeyframing(ptrHeadAnimation);
    Body->attach( Head );
    this->uiPolyCount += Head->getPolyCount();

    BRep * Boina = new BRep();
    Boina->LoadfromFile( strPath + "t3objv2/eptacio_boina.obj" );
    Boina->setTranslate(Vector3(0,1.35f,0.0f));
    Head->attach( Boina );
    this->uiPolyCount += Boina->getPolyCount();

    // HandD Track

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 0.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, -45.0f, 0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 1.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 2.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, -45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 3.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 4.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, -45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 5.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 6.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, -45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 7.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 8.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, -45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 9.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }
    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 10.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, -45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 11.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 12.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, -45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 13.0 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 14.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 0.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 15.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 17.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,30.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 20.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 45.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 22.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 0.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 24.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 0.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }


    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 25.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 0.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    {
      Pose * HandDPose = new Pose();
      HandDPose->setTime( 26.5 );
      HandDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 0.0f,0.0f ) ) );
      ptrHandDAnimation->addPose( HandDPose, animType);
    }

    // HandE Track

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 0.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f, 0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 1.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 2.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 3.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 4.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 5.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 6.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 7.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 8.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 9.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 10.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }


    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 11.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 12.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }


    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 13.0 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 14.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 0.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 15.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -45.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 17.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -40.0f,30.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 20.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, -40.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 21.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 0.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 24.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 0.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 25.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 90.0f, 0.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }

    {
      Pose * HandEPose = new Pose();
      HandEPose->setTime( 26.5 );
      HandEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -90.0f, 0.0f,0.0f ) ) );
      ptrHandEAnimation->addPose( HandEPose, animType);
    }


    // Body Track

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 0.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }


    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 1.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 2.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 3.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 4.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 5.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 6.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 7.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 8.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 9.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 10.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 11.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 12.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 27.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 28.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 29.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 30.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 31.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 32.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 33.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 34.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 35.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 36.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 37.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 38.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 39.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 40.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 41.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 42.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 30.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 43.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 00.0f, 0.0f ) ) );
      ptrBodyAnimation->addPose( BodyPose, animType);
    }



    // Head Track

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 0.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }


    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 1.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 20.0f, 20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 2.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 3.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 20.0f, 20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 4.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 5.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 20.0f, 20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 6.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 7.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3(20.0f, 20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 8.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 9.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 20.0f, 20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 10.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 11.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 20.0f, 20.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 12.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -0.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 13.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 30.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 14.5 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 15.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 15.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -15.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 20.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 10.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 23.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 25.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 00.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 43.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 45.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, -45.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    {
      Pose * HeadPose = new Pose();
      HeadPose->setTime( 50.0 );
      HeadPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 45.0f, 0.0f ) ) );
      ptrHeadAnimation->addPose( HeadPose, animType);
    }

    // FootE Track

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 0.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 1.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 2.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 3.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 4.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 5.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 6.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 7.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 8.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 9.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 10.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 11.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 12.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 27.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 28.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 29.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 30.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 31.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 32.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 33.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 34.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 35.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 36.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 37.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 38.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 39.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 40.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 41.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }

    {
      Pose * FeetEPose = new Pose();
      FeetEPose->setTime( 42.0 );
      FeetEPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrFeetEAnimation->addPose( FeetEPose, animType);
    }



    // FootD Track

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 0.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 1.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 2.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 3.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 4.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 5.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 6.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f,50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 7.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 8.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 9.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 10.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 11.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 12.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 27.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 28.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 29.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 30.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 31.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 32.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 33.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 34.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 35.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 36.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 37.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 38.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 39.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 40.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 41.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, -50.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }

    {
      Pose * FeetDPose = new Pose();
      FeetDPose->setTime( 42.0 );
      FeetDPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      ptrFeetDAnimation->addPose( FeetDPose, animType);
    }



  }


  // -----------------------------------------------------------------------------------------------
  // CAT
  //------------------------------------------------------------------------------------------------

  Keyframing* kfCatPivot = new Keyframing();

  Entity* ptrCatPivot = new Entity();
  ptrCatPivot->setTranslate(Vector3(7,0,7));
  ptrCatPivot->setRotate(Vector3(0,-90,0));
  ptrCatPivot->setScale(Vector3(1,1,1)*0.5f);
  ptrCatPivot->setKeyframing(kfCatPivot);

  // Cat Pivot
  {
    Pose * CatPivotPose = new Pose();
    CatPivotPose->setTime( 0.0 );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0 ) ) );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "position", Vector3( -2.0f, 0.0f, 7.0f ) ) );
    kfCatPivot->addPose( CatPivotPose, animType);
  }

  {
    Pose * CatPivotPose = new Pose();
    CatPivotPose->setTime( 23.5 );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0 ) ) );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "position", Vector3( -2.0f, 0.0f, 7.0f ) ) );
    kfCatPivot->addPose( CatPivotPose, animType);
  }

  {
    Pose * CatPivotPose = new Pose();
    CatPivotPose->setTime( 23.7 );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0 ) ) );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "position", Vector3( 1.5f, 0.4f, 7.0f ) ) );
    kfCatPivot->addPose( CatPivotPose, animType);
  }

  {
    Pose * CatPivotPose = new Pose();
    CatPivotPose->setTime( 24.0 );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0 ) ) );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "position", Vector3( 4.0f, 0.0f, 7.0f ) ) );
    kfCatPivot->addPose( CatPivotPose, animType);
  }


  {
    Pose * CatPivotPose = new Pose();
    CatPivotPose->setTime( 24.2 );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0 ) ) );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "position", Vector3( 5.5f, 0.4f, 7.0f ) ) );
    kfCatPivot->addPose( CatPivotPose, animType);
  }

  {
    Pose * CatPivotPose = new Pose();
    CatPivotPose->setTime( 24.5 );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0 ) ) );
    CatPivotPose->addPoseAttribute( new VectorAttribute( "position", Vector3( 7.0f, 0.0f, 7.0f ) ) );
    kfCatPivot->addPose( CatPivotPose, animType);
  }

  this->addEntity(ptrCatPivot);

  {

    // Keyframes

    Keyframing* kfCatBody = new Keyframing();
    Keyframing* kfCatHead = new Keyframing();
    Keyframing* kfCatFeetFD = new Keyframing();
    Keyframing* kfCatFeetFE = new Keyframing();
    Keyframing* kfCatFeetTD = new Keyframing();
    Keyframing* kfCatFeetTE = new Keyframing();

    Keyframing* kfCatTail = new Keyframing(true);



    // Objs Load

    BRep * brepCatBody = new BRep();
    brepCatBody->LoadfromFile( strPath + "t3obj/cat_body.obj" );
    brepCatBody->setTranslate(Vector3(0,0.5f,0.0f));
    brepCatBody->setKeyframing(kfCatBody);
    ptrCatPivot->attach( brepCatBody );
    this->uiPolyCount += brepCatBody->getPolyCount();

    BRep * brepCatFeetFE = new BRep();
    brepCatFeetFE->LoadfromFile( strPath + "t3obj/cat_feet.obj" );
    brepCatFeetFE->setTranslate(Vector3(0.5f,-0.2f,-0.4f));
    brepCatBody->attach( brepCatFeetFE );
    brepCatFeetFE->setKeyframing(kfCatFeetFD);
    this->uiPolyCount += brepCatFeetFE->getPolyCount();

    BRep * brepCatFeetFD = new BRep();
    brepCatFeetFD->LoadfromFile( strPath + "t3obj/cat_feet.obj" );
    brepCatFeetFD->setTranslate(Vector3(0.5f,-0.2f,0.4f));
    brepCatFeetFD->setKeyframing(kfCatFeetFD);
    brepCatBody->attach( brepCatFeetFD );
    this->uiPolyCount += brepCatFeetFD->getPolyCount();

    BRep * brepCatFeetTE = new BRep();
    brepCatFeetTE->LoadfromFile( strPath + "t3obj/cat_feet.obj" );
    brepCatFeetTE->setTranslate(Vector3(-0.5f,-0.2f,-0.4f));
    brepCatBody->attach( brepCatFeetTE );
    brepCatFeetTE->setKeyframing(kfCatFeetTD);
    this->uiPolyCount += brepCatFeetTE->getPolyCount();

    BRep * brepCatFeetTD = new BRep();
    brepCatFeetTD->LoadfromFile( strPath + "t3obj/cat_feet.obj" );
    brepCatFeetTD->setTranslate(Vector3(-0.5f,-0.2f,0.4f));
    brepCatBody->attach( brepCatFeetTD );
    brepCatFeetTD->setKeyframing(kfCatFeetTD);
    this->uiPolyCount += brepCatFeetTD->getPolyCount();

    BRep * brepCatHead = new BRep();
    brepCatHead->LoadfromFile( strPath + "t3obj/cat_head.obj" );
    brepCatHead->setTranslate(Vector3(1.0f,0.7f,0.0f));
    brepCatBody->attach( brepCatHead );
    brepCatHead->setKeyframing(kfCatHead);
    this->uiPolyCount += brepCatHead->getPolyCount();

    BRep * brepCatTail01 = new BRep();
    brepCatTail01->LoadfromFile( strPath + "t3obj/cat_tail.obj" );
    brepCatTail01->setTranslate(Vector3(-0.5f,0.2f,0.0f));
    brepCatBody->attach( brepCatTail01 );
    brepCatTail01->setKeyframing(kfCatTail);
    this->uiPolyCount += brepCatTail01->getPolyCount();

    BRep * brepCatTail02 = new BRep();
    brepCatTail02->LoadfromFile( strPath + "t3obj/cat_tail.obj" );
    brepCatTail02->setTranslate(Vector3(-0.2f,0.4f,0.0f));
    brepCatTail01->attach( brepCatTail02 );
    brepCatTail02->setKeyframing(kfCatTail);
    this->uiPolyCount += brepCatTail02->getPolyCount();

    // Tail Moviment
    {
      Pose * TailPose = new Pose();
      TailPose->setTime( 0.0 );
      TailPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 10.0f ) ) );
      kfCatTail->addPose( TailPose, animType);
    }

    {
      Pose * TailPose = new Pose();
      TailPose->setTime( 1.0 );
      TailPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 30.0f, 0.0f, 0.0f ) ) );
      kfCatTail->addPose( TailPose, animType);
    }

    {
      Pose * TailPose = new Pose();
      TailPose->setTime( 2.0 );
      TailPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 10.0f ) ) );
      kfCatTail->addPose( TailPose, animType);
    }

    {
      Pose * TailPose = new Pose();
      TailPose->setTime( 3.0 );
      TailPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( -30.0f, 0.0f, 0.0f ) ) );
      kfCatTail->addPose( TailPose, animType);
    }

    {
      Pose * TailPose = new Pose();
      TailPose->setTime( 4.0 );
      TailPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 10.0f ) ) );
      kfCatTail->addPose( TailPose, animType);
    }

    // Body
    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 0.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 30.0f ) ) );
      kfCatBody->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 1.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 30.0f ) ) );
      kfCatBody->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 41.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 30.0f ) ) );
      kfCatBody->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 47.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      kfCatBody->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 47.5 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0, -30.0f ) ) );
      kfCatBody->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 48.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 0.0f, 0.0f ) ) );
      kfCatBody->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 48.5 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f,  0.0f,30.0f ) ) );
      kfCatBody->addPose( BodyPose, animType);
    }

    {
      Pose * BodyPose = new Pose();
      BodyPose->setTime( 49.0 );
      BodyPose->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f,  0.0f, 0.0f) ) );
      kfCatBody->addPose( BodyPose, animType);
    }






  }


	// -----------------------------------------------------------------------------------------------




	Pose * ptrPose1 = new Pose();
	ptrPose1->setTime( 0.0 );
	ptrPose1->addPoseAttribute( new VectorAttribute( "position", Vector3( -1.5f, 0.05f, 1.0f ) ) );
	ptrPose1->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 90.0f, 0.0f ) ) );
	ptrAnimation->addPose( ptrPose1 , animType);

	Pose * ptrPose2 = new Pose();
	ptrPose2->setTime( 5.0 );
	ptrPose2->addPoseAttribute( new VectorAttribute( "position", Vector3( 1.5f, 0.05f, 1.0f ) ) );
	ptrPose2->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 90.0f, 0.0f ) ) );
	ptrAnimation->addPose( ptrPose2 , animType);

	Pose * ptrPose3 = new Pose();
	ptrPose3->setTime( 10.0 );
	ptrPose3->addPoseAttribute( new VectorAttribute( "position", Vector3( 1.5f, 0.05f, 1.0f ) ) );
	ptrPose3->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 270.0f, 0.0f ) ) );
	ptrAnimation->addPose( ptrPose3, animType );

	Pose * ptrPose4 = new Pose();
	ptrPose4->setTime( 15.0 );
	ptrPose4->addPoseAttribute( new VectorAttribute( "position", Vector3( -1.5f, 0.05f, 1.0f ) ) );
	ptrPose4->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 270.0f, 0.0f ) ) );
	ptrAnimation->addPose( ptrPose4 , animType );

	Pose * ptrPose5 = new Pose();
	ptrPose5->setTime( 20.0 );
	ptrPose5->addPoseAttribute( new VectorAttribute( "position", Vector3( -1.5f, 0.05f, 1.0f ) ) );
	ptrPose5->addPoseAttribute( new VectorAttribute( "orientation", Vector3( 0.0f, 90.0f, 0.0f ) ) );
	ptrAnimation->addPose( ptrPose5 , animType );




	BRep * ptrBlueCar = new BRep();
	ptrBlueCar->LoadfromFile( strPath + "obj/Car.obj" );
	ptrBlueCar->setTranslate( Vector3( -1.5f, 0.05f, 1.0f ));
	ptrBlueCar->setScale( Vector3( 0.1f, 0.1f, 0.1f ));
	ptrBlueCar->setRotate( Vector3( 0.0f, 90.0f, 0.0f ));
	ptrBlueCar->setKeyframing( ptrAnimation );

	this->uiPolyCount += ptrBlueCar->getPolyCount();

  {
    BRep * Table = new BRep();
    Table->LoadfromFile( strPath + "t3obj/Table.obj" );
    Table->setTranslate(Vector3(5, 0, 5));
    this->addEntity( Table );
    this->uiPolyCount += Table->getPolyCount();


  }

  Entity* pivotTest = new Entity();
  pivotTest->setTranslate(Vector3(6,0,5));
  pivotTest->setRotate(Vector3(0,45,0));
  pivotTest->attach(ptrBlueCar);
  this->addEntity(pivotTest);


  // -------------------------------------------------------------------------------------------------

  RigidBody * ptrRigidBody = new RigidBody();
  ptrRigidBody->setMass( 3.0f );
  ptrRigidBody->setGravity( Vector3( 0.0f, -1.0f, 0.0f ));
  ptrRigidBody->addForce( Vector3( 3.0f, 0.0f, 0.0f )); // trust
  //ptrRigidBody->addForce( Vector3( -20.0f, 0.0f, 0.0f )); // wind

  BRep * ptrBall = new BRep();
  ptrBall->LoadfromFile( strPath + "t3obj/basketball.obj" );
  ptrBall->setTranslate( Vector3( 3.0f, 3.0f, 9.0f ));
  ptrBall->setRigidBody( ptrRigidBody );
  ptrRigidBody->setBoundingSphere();

  this->addEntity( ptrBall );
  this->uiPolyCount += ptrBall->getPolyCount();

  // -------------------------------------------------------------------------------------------------

  RigidBody * ptrRigidBody1 = new RigidBody();
  ptrRigidBody1->setMass( 1.5f );
  ptrRigidBody1->setGravity( Vector3( 0.0f, -1.0f, 0.0f ));
  ptrRigidBody1->addForce( Vector3( -50.0f, 9.0f, 0.0f )); // trust

  BRep * ptrBall1 = new BRep();
  ptrBall1->LoadfromFile( strPath + "t3obj/scoccerball.obj" );
  ptrBall1->setTranslate( Vector3( 6.0f, 4.0f, 9.0f ));
  ptrBall1->setRigidBody( ptrRigidBody1 );
  ptrRigidBody1->setBoundingSphere();

  this->addEntity( ptrBall1 );
  this->uiPolyCount += ptrBall1->getPolyCount();


  // -------------------------------------------------------------------------//

  // PARTICLES
  {
    BRep * Table = new BRep();
    Table->LoadfromFile( strPath + "t3objv2/fogareira.obj" );
    Table->setTranslate(Vector3(1, 1, 5));
    this->addEntity( Table );
    this->uiPolyCount += Table->getPolyCount();

    {
      ParticleEmissor* pe = new Fire(5000);
      pe->Setup();
      pe->setTranslate(Vector3(0,0,0));
      Table->attach(pe);
    }

    {
      ParticleEmissor* pe = new Smoke(10000);
      pe->Setup();
      pe->setTranslate(Vector3(0,0,0));
      Table->attach(pe);
    }

  }


  {
    ParticleEmissor* pe = new Water(1000);
    pe->Setup();
    pe->setTranslate(Vector3(0.6,1.6,2.45));
    this->addEntity(pe);
  }


  {


    ParticleEmissor* pe = new Rain(30000);
    pe->Setup();
    pe->setTranslate(Vector3(-4,7,5));
    pe->setScale(Vector3(0.5,1,4));
    this->addEntity(pe);
  }
  printf("\nTerminou de montar a cena\n");
}
