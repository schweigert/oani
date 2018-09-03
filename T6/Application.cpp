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
#include "Skybox.h"
#include "Boid.h"
#include "IronTrail.h"

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

	if( this->dCounterTimer >= 5.0 ) // 1 segundo transcorrido?
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

  Interpolator::InterpolationType animType = Interpolator::POLYNOM;

    string strPath = "./";

	printf("Montando a cena...\n");

	Camera * ptrCamera = new Camera();
	ptrCamera->setTranslate( Vector3( 0, 5, 25 ) );
  ptrCamera->LookAt(Vector3(0,5,0));
  ptrCamera->setFOV(40);
	this->addEntity( ptrCamera );

  LightSource* ptrLight = new LightSource( 3, LightSource::POINT );
  ptrLight->setTranslate( Vector3( 0.3f, 2.0f,25.0f ) );
  this->addEntity( ptrLight );

  {
    BRep* subSky = new BRep();
    subSky->LoadfromFile(strPath + "t3objv2/skybox.obj");
    subSky->setTranslate(Vector3(0,5,25));

    Skybox* sky = new Skybox(subSky, ptrCamera);
    ptrCamera->attach(sky);
  }

  /////////////
  // IRONMAN //
  /////////////

  Keyframing* ironFrame = new Keyframing();

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(0.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, 5, 21)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,0,0)));
    ironFrame->addPose(ptrPose, animType);
  }


  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(5.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, 5, 21)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,0,0)));
    ironFrame->addPose(ptrPose, animType);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(5.5);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(-1, 5, 21)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,-45,0)));
    ironFrame->addPose(ptrPose, animType);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(6.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5, 5, 21)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,0,0)));
    ironFrame->addPose(ptrPose, animType);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(10.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(100, 5, 21)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,-650,0)));
    ironFrame->addPose(ptrPose, animType);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(15.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(1000, 5, 21)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,-600,0)));
    ironFrame->addPose(ptrPose, animType);
  }

  Entity* ironPivot = new Entity();
  ironPivot->setTranslate ( Vector3( 0, 5,21 ) );
  ironPivot->setRotate(Vector3(90, 0, 0));
  ironPivot->setKeyframing(ironFrame);
  this->addEntity(ironPivot);
  {

    BRep* pelvis = new BRep();
    pelvis->LoadfromFile( strPath + "ironman/pelvis.obj" );
    ironPivot->attach( pelvis );
    this->uiPolyCount += pelvis->getPolyCount();

    {
      BRep* torax = new BRep();
      torax->LoadfromFile(strPath + "ironman/torax.obj");
      torax->setTranslate(Vector3(0,0.25,0));
      pelvis->attach(torax);
      this->uiPolyCount += torax->getPolyCount();
      {
        BRep* body = new BRep();
        body->LoadfromFile(strPath + "ironman/body.obj");
        body->setTranslate(Vector3(0,0.35,0));
        torax->attach(body);
        this->uiPolyCount += torax->getPolyCount();

        {
          BRep* shoulder = new BRep();
          shoulder->LoadfromFile(strPath + "ironman/shoulderP.obj");
          shoulder->setTranslate(Vector3(0.25,0.25,-0.05));
          body->attach(shoulder);
        }


        {
          BRep* shoulder = new BRep();
          shoulder->LoadfromFile(strPath + "ironman/shoulderP.obj");
          shoulder->setTranslate(Vector3(-0.25,0.25,-0.1));
          shoulder->setRotate(Vector3(0,180,0));
          body->attach(shoulder);
                }


        {
          BRep* head = new BRep();
          head->LoadfromFile(strPath + "ironman/head.obj");
          head->setTranslate(Vector3(0,0.4,0));
          body->attach(head);
          this->uiPolyCount += head->getPolyCount();
          Keyframing* ironFrameHead = new Keyframing();
          head->setKeyframing(ironFrameHead);
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, 0.4, 0)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            ironFrameHead->addPose(ptrPose, animType);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(3.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, 0.4, 0)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            ironFrameHead->addPose(ptrPose, animType);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(6.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, 0.4, 0)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(10,45,0)));
            ironFrameHead->addPose(ptrPose, animType);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(10.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, 0.4, 0)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            ironFrameHead->addPose(ptrPose, animType);
          }


        }
      }
    }
  }


  {

    BRep * mig15 = new BRep();
    mig15->LoadfromFile( strPath + "final/jet.obj" );
    this->uiPolyCount += mig15->getPolyCount();

    Boid* mig15Boid = new Boid(mig15, ironPivot);


    {
      ParticleEmissor* pe = new Fire(2000);
      pe->Setup();
      pe->setTranslate(Vector3(0,0,-6));
      pe->setRotate(Vector3(-90,0,0));
      mig15->attach(pe);
    }

    mig15Boid->setTranslate ( Vector3( 8, -100, 0 ) );
    mig15Boid->setDeltaPosition (Vector3(8, -1, -25));
    this->addEntity( mig15Boid );
  }


    {
      BRep * mig15 = new BRep();
      mig15->LoadfromFile( strPath + "final/jet.obj" );

      mig15->setRotate (Vector3 (0, 0, 0));

      Boid* mig15Boid = new Boid(mig15, ironPivot);
      this->uiPolyCount += mig15->getPolyCount();

      {
        ParticleEmissor* pe = new Fire(2000);
        pe->Setup();
        pe->setTranslate(Vector3(0,0,-6));
        pe->setRotate(Vector3(-90,0,0));
        mig15->attach(pe);
      }

      mig15Boid->setTranslate ( Vector3( -8, -100, 0 ) );
      mig15Boid->setDeltaPosition (Vector3(-8, -1, -25));
      this->addEntity( mig15Boid );

    }







  printf("\nTerminou de montar a cena\n");
}
