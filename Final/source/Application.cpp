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
#include "Wind.h"
#include "MageParticle.h"
#include "Grass.h"
#include "Timer.h"
#include "GlowCometa.h"

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
    return this->strAppName;
}

/**
  \brief Constroi a cena a ser renderizada e animada nesta aplica��o
*/

void Application::CreateScene()
{

  Interpolator::InterpolationType animPoly = Interpolator::POLYNOM;
  Interpolator::InterpolationType animLinear = Interpolator::LINEAR;

  string strPath = "./";

	printf("Montando a cena...\n");

	Camera * ptrCamera = new Camera();
  // Camera Setup
	{
    ptrCamera->setTranslate( Vector3( 18, 0.3, 18 ) );
    ptrCamera->LookAt(Vector3(15,10,15));
    ptrCamera->setFOV(40);
  	this->addEntity( ptrCamera );

    // Keyframing da Camera
    {
      Keyframing* cameraKeyframing = new Keyframing();
      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(0.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(18, 0.3, 18)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(15,10,15)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(5.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(18, 0.5, 18)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(15,0.50,15)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(10.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(18, 1.3, 18)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(15,1,15)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(12.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(25, 1.3, 18)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(20,1,15)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(17.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(25, 1.3, 18)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(19,1,15)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(20.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(25, 1.3, 18)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(19.5,1,15)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(35.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(8, 0.2, 6)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(-30,15,-30)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(37.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(8, 0.2, 6)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(-30,15,-30)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(39.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5, 0.5, 5)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(5.5, 0.7, 2.1)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(48.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(1, 3, 4)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(8, 2, 5)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(55.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(1, 1, 2)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(50, 30, 25)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(65.0);
        ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5, 0.3, 5)));
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(5, 1, 5)));
        cameraKeyframing->addPose(ptrPose, animPoly);
      }


      ptrCamera->setKeyframing(cameraKeyframing);
    }
  }


  LightSource* ptrLight = new LightSource( 3, LightSource::POINT );
  ptrLight->setTranslate( Vector3( 0.3f, 2.0f,25.0f ) );
  this->addEntity( ptrLight );

  // Skybox
  {
    BRep* subSky = new BRep();
    subSky->LoadfromFile(strPath + "models/skybox.obj");

    Skybox* sky = new Skybox(subSky, ptrCamera);
    ptrCamera->attach(sky);
  }


  BRep* terrain = new BRep();
  terrain->LoadfromFile("models/terrain.obj");
  terrain->setScale(Vector3(1,1,1)*10);
  addEntity(terrain);

  CreateVisualObjects();

  createInitialBird();
  CreateBirdBoidsScene();

  createStar();

  addEntity(createMage());



  // Casa rotacionada
  {
    ParticleEmissor* smoke = new Smoke(500);
    smoke->setTranslate(Vector3(-1.2,2.6,4.75));
    smoke->Setup();
    addEntity(smoke);
  }

  // Casa sem rotação
  {
    ParticleEmissor* smoke = new Smoke(500);
    smoke->setTranslate(Vector3(5.25,2.6,-1.2));
    smoke->Setup();
    addEntity(smoke);
  }



  printf("\nTerminou de montar a cena\n");
}

void Application::CreateVisualObjects()
{

  Wind* wind = new Wind();
  wind->setForce(0.1f);
  addEntity(wind);
  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.5);
    pinus->setTranslate(Vector3(10,0,12));


    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);



  }

  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.3);
    pinus->setTranslate(Vector3(14,0,7));

    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);


  }

  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.4);
    pinus->setTranslate(Vector3(0,0,0));


    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);


  }

  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.4);
    pinus->setTranslate(Vector3(-3,0,0));

    wind->attach(pinus);
    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);



  }


  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.5);
    pinus->setTranslate(Vector3(14,0,5));



    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);


  }

  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.5);
    pinus->setTranslate(Vector3(-3,0,-5));

    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);


  }

  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.5);
    pinus->setTranslate(Vector3(0,0,-5));


    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);


  }

  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.5);
    pinus->setTranslate(Vector3(3,0,15));


    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);


  }

  {

    BRep* pinus = new BRep();
    pinus->LoadfromFile("models/pinus.obj");
    pinus->setScale(Vector3(1,1,1)*0.6);
    pinus->setTranslate(Vector3(7.5,0,0));


    wind->attach(pinus);

    ParticleEmissor* grass = new GrassParticle(10);
    grass->Setup();
    grass->setTranslate(Vector3(0,2.7,0));
    grass->setScale(Vector3(1,1,1)*2.7);
    pinus->attach(grass);


    ParticleEmissor* grass1 = new GrassParticle(10);
    grass1->Setup();
    grass1->setTranslate(Vector3(0,4,0));
    grass1->setScale(Vector3(1,1,1)*1.7);
    pinus->attach(grass1);


  }


    {

      BRep* home = new BRep();
      home->LoadfromFile("models/home.obj");
      home->setScale(Vector3(1,1,1)*1);
      home->setTranslate(Vector3(5,0,0));


      addEntity(home);


    }

    {

      BRep* home = new BRep();
      home->LoadfromFile("models/home.obj");
      home->setScale(Vector3(1,1,1)*1);
      home->setRotate(Vector3(0,90,0));
      home->setTranslate(Vector3(0,0,5));

      addEntity(home);
    }

}

void Application::CreateBirdBoidsScene()
{
  Entity* leader = createBirdBoid();
  addEntity(leader);
  // Leader Poses
  {
    Keyframing* leaderKeyframe = new Keyframing();
    leader->setKeyframing(leaderKeyframe);
    // Poses
    {
      Pose* ptrPose = new Pose();
      ptrPose->setTime(10.0f);
      ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(25,0,0)));
      leader->setTranslate(Vector3(25,0,0));
      leader->setRotate(Vector3(0,-130,0));
      leaderKeyframe->addPose(ptrPose, Interpolator::LINEAR);
    }

    // Poses
    {
      Pose* ptrPose = new Pose();
      ptrPose->setTime(20.0f);
      ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(-10,10,23)));
      leaderKeyframe->addPose(ptrPose, Interpolator::LINEAR);
    }
  }

  int N = 4; // Quantidade em fileira
  int i = 0;

  for(i = 0; i < N; i++){
    // Boid 1
    {
      Entity* boidEntity = createBirdBoid();
      boidEntity->setRotate(Vector3(0, -130, 0));
      boidEntity->setTranslate(Vector3(0,0,0));
      Boid* boid = new Boid(boidEntity, leader);
      boid->setDeltaPosition(Vector3(i, -0.1f, -i));

      addEntity(boid);
    }

    // Boid 2
    {
      Entity* boidEntity = createBirdBoid();
      boidEntity->setTranslate(Vector3(0,0,0));
      boidEntity->setRotate(Vector3(0, -130, 0));
      Boid* boid = new Boid(boidEntity, leader);
      boid->setDeltaPosition(Vector3(-i, -0.1f, -i));

      addEntity(boid);
    }
  }

}

Entity* Application::createBirdBoid()
{
  Interpolator::InterpolationType animPoly = Interpolator::POLYNOM;
  Interpolator::InterpolationType animLinear = Interpolator::LINEAR;

  Entity* birdPivot = new Entity();

  // BlueBird Pivot
  {

    birdPivot->setTranslate(Vector3(15,0.2,15));
    birdPivot->setScale(Vector3(1,1,1)*0.1f);
    birdPivot->setRotate(Vector3(0,45,0));
    //addEntity(birdPivot);


    // Body
    {
      Entity* bodyPivot = new Entity();
      birdPivot->attach(bodyPivot);

      BRep* bodyMesh = new BRep();
      bodyMesh->LoadfromFile("models/blue_body.obj");
      bodyPivot->attach(bodyMesh);



      // Head
      {
        Entity* headPivot = new Entity();
        headPivot->setTranslate(Vector3(0.35,0.6,0));
        headPivot->setRotate(Vector3(0, 0, -35));
        bodyPivot->attach(headPivot);

        BRep* headMesh = new BRep();
        headMesh->LoadfromFile("models/blue_head.obj");
        headPivot->attach(headMesh);

        // Bico Upper
        {
          Entity* bicoUpperPivot = new Entity();
          bicoUpperPivot->setTranslate(Vector3(0.35,0.28,0));
          headPivot->attach(bicoUpperPivot);

          BRep* bicoUpperMesh = new BRep();
          bicoUpperMesh->LoadfromFile("models/blue_bicoUpper.obj");
          bicoUpperPivot->attach(bicoUpperMesh);
        }


      }

      // Asa Negativa
      {
        Entity* asaPivot = new Entity();
        asaPivot->setTranslate(Vector3(0.2,0.1,0.4));
        asaPivot->setRotate(Vector3(45,150,-90));
        bodyPivot->attach(asaPivot);

        {
          Keyframing* asaKeyframe = new Keyframing(true);
          asaPivot->setKeyframing(asaKeyframe);

          // Asa Negativa Poses
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }

          // Asa Negativa Poses
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.3);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", (Vector3(45,150,-90))));
            asaKeyframe->addPose(ptrPose, animLinear);
          }

          // Asa Negativa Poses
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.6);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }



        }



        BRep* asaMesh = new BRep();
        asaMesh->LoadfromFile("models/blue_asaN.obj");
        asaPivot->attach(asaMesh);



      }

      // Asa Positiva
      {
        Entity* asaPivot = new Entity();
        asaPivot->setTranslate(Vector3(0.2,0.1,-0.4));
        asaPivot->setRotate(Vector3(45,-150,-90));
        bodyPivot->attach(asaPivot);

        {
          Keyframing* asaKeyframe = new Keyframing(true);
          asaPivot->setKeyframing(asaKeyframe);

          // Asa Negativa Poses
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }

          // Asa Negativa Poses
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.3);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", (Vector3(45,-150,-90))));
            asaKeyframe->addPose(ptrPose, animLinear);
          }

          // Asa Negativa Poses
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.6);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }



        }

        BRep* asaMesh = new BRep();
        asaMesh->LoadfromFile("models/blue_asaP.obj");
        asaPivot->attach(asaMesh);
      }


    }

  }

  return birdPivot;
}



void Application::createInitialBird()
{


    Interpolator::InterpolationType animPoly = Interpolator::POLYNOM;
    Interpolator::InterpolationType animLinear = Interpolator::LINEAR;

    // BlueBird Pivot
    {
      Entity* birdPivot = new Entity();
      birdPivot->setTranslate(Vector3(15,0.2,15));
      birdPivot->setScale(Vector3(1,1,1)*0.1f);
      addEntity(birdPivot);

      // birdPivot Poses
      {
        Keyframing* birdPivotKeyframing = new Keyframing();
        birdPivot->setKeyframing(birdPivotKeyframing);

        // Poses
        {
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(6.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(15, 0.2, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            birdPivotKeyframing->addPose(ptrPose, animPoly);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(6.3);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(15, 0.4, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,15,0)));
            birdPivotKeyframing->addPose(ptrPose, animPoly);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(6.8);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(15, 0.2, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,30,0)));
            birdPivotKeyframing->addPose(ptrPose, animPoly);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(8.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(15, 0.2, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,30,0)));
            birdPivotKeyframing->addPose(ptrPose, animPoly);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(8.3);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(15, 0.6, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,10,0)));
            birdPivotKeyframing->addPose(ptrPose, animPoly);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(8.7);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(15, 0.2, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-10,0)));
            birdPivotKeyframing->addPose(ptrPose, animPoly);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(12.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(15, 0.2, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            birdPivotKeyframing->addPose(ptrPose, animLinear);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(12.4);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(16, 0.3, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            birdPivotKeyframing->addPose(ptrPose, animLinear);
          }


          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(14.0);
            ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(25, 3.5, 15)));
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            birdPivotKeyframing->addPose(ptrPose, animLinear);
          }
        }
      }

      // Body
      {
        Entity* bodyPivot = new Entity();
        birdPivot->attach(bodyPivot);

        BRep* bodyMesh = new BRep();
        bodyMesh->LoadfromFile("models/blue_body.obj");
        bodyPivot->attach(bodyMesh);

        // Body Keyframing

        {
          Keyframing* bodyKeyframe = new Keyframing();
          bodyPivot->setKeyframing(bodyKeyframe);
          // Poses
          {
            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(0.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(1.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-50)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(2.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(3.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-50)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }
            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(4.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(5.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-50)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }
            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(6.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(6.5);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,15)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(8.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(8.5);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,15)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(10.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              bodyKeyframe->addPose(ptrPose, animPoly);
            }
          }
        }

        // Head
        {
          Entity* headPivot = new Entity();
          headPivot->setTranslate(Vector3(0.35,0.6,0));
          bodyPivot->attach(headPivot);

          BRep* headMesh = new BRep();
          headMesh->LoadfromFile("models/blue_head.obj");
          headPivot->attach(headMesh);

          // Bico Upper
          {
            Entity* bicoUpperPivot = new Entity();
            bicoUpperPivot->setTranslate(Vector3(0.35,0.28,0));
            headPivot->attach(bicoUpperPivot);

            BRep* bicoUpperMesh = new BRep();
            bicoUpperMesh->LoadfromFile("models/blue_bicoUpper.obj");
            bicoUpperPivot->attach(bicoUpperMesh);

            // Bico Down
            {
              Entity* BicoDownPivot = new Entity();
              BicoDownPivot->setTranslate(Vector3(-0.10,-0.05,0));
              bicoUpperPivot->attach(BicoDownPivot);

              BRep* bicoDownMesh = new BRep();
              bicoDownMesh->LoadfromFile("models/blue_bicoDown.obj");
              BicoDownPivot->attach(bicoDownMesh);
            }
          }


        }

        // Asa Negativa
        {
          Entity* asaPivot = new Entity();
          asaPivot->setTranslate(Vector3(0.2,0.1,0.4));
          bodyPivot->attach(asaPivot);

          {
            Keyframing* asaKeyframe = new Keyframing();
            asaPivot->setKeyframing(asaKeyframe);

            // Asa Negativa Poses
            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(0.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(11.5);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(11.8);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(45,150,-75)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(12.2);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(13.2);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(45,150,-75)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

          }

          BRep* asaMesh = new BRep();
          asaMesh->LoadfromFile("models/blue_asaN.obj");
          asaPivot->attach(asaMesh);

        }

        // Asa Positiva
        {
          Entity* asaPivot = new Entity();
          asaPivot->setTranslate(Vector3(0.2,0.1,-0.4));
          bodyPivot->attach(asaPivot);

          {
            Keyframing* asaKeyframe = new Keyframing();
            asaPivot->setKeyframing(asaKeyframe);

            // Asa Negativa Poses
            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(0.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(11.5);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(11.8);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(45,-150,-75)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(12.2);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(13.2);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(45,-150,-75)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

          }

          BRep* asaMesh = new BRep();
          asaMesh->LoadfromFile("models/blue_asaP.obj");
          asaPivot->attach(asaMesh);
        }

        // Pata Negativa
        {
          Entity* feetPivot = new Entity();
          feetPivot->setTranslate(Vector3(0,-0.3,0.2));
          birdPivot->attach(feetPivot);

          BRep* feetMesh = new BRep();
          feetMesh->LoadfromFile("models/blue_feet.obj");
          feetPivot->attach(feetMesh);
        }

        // Pata Positiva
        {
          Entity* feetPivot = new Entity();
          feetPivot->setTranslate(Vector3(0,-0.3,-0.2));
          birdPivot->attach(feetPivot);

          BRep* feetMesh = new BRep();
          feetMesh->LoadfromFile("models/blue_feet.obj");
          feetPivot->attach(feetMesh);
        }

      }


    }
}

Entity* Application::createFlyingYellowBird(){
  Interpolator::InterpolationType animPoly = Interpolator::POLYNOM;
  Interpolator::InterpolationType animLinear = Interpolator::LINEAR;

  // BlueBird Pivot
    Entity* birdPivot = new Entity();
    birdPivot->setTranslate(Vector3(-300,100,-300));
    birdPivot->setScale(Vector3(1,1,1)*3.0f);

    // birdPivot Poses
    {
      Keyframing* birdPivotKeyframing = new Keyframing();
      birdPivot->setKeyframing(birdPivotKeyframing);

      // Poses
      {
        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(37.0);
          ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(150, 30, 150)));
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0, 90, 0)));
          birdPivotKeyframing->addPose(ptrPose, animPoly);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(46.0);
          ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, -1, 0)));
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0, 90, 0)));
          birdPivotKeyframing->addPose(ptrPose, animPoly);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(47.0);
          ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(1, 0, 0)));
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0, 90, 0)));
          birdPivotKeyframing->addPose(ptrPose, animPoly);
        }


        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(48.0);
          ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(0, 0, 0)));
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0, 0, 0)));
          birdPivotKeyframing->addPose(ptrPose, animLinear);
        }

      }
    }

    // Body
    {
      Entity* bodyPivot = new Entity();
      birdPivot->attach(bodyPivot);

      BRep* bodyMesh = new BRep();
      bodyMesh->LoadfromFile("models/yellow_body.obj");
      bodyPivot->attach(bodyMesh);

      // Body Keyframing

      {
        Keyframing* bodyKeyframe = new Keyframing();
        bodyPivot->setKeyframing(bodyKeyframe);
        // Poses
        {
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
            bodyKeyframe->addPose(ptrPose, animPoly);
          }

        }
      }

      // Head
      {
        Entity* headPivot = new Entity();
        headPivot->setTranslate(Vector3(0.35,0.6,0));
        bodyPivot->attach(headPivot);

        BRep* headMesh = new BRep();
        headMesh->LoadfromFile("models/yellow_head.obj");
        headPivot->attach(headMesh);

        // Bico Upper
        {
          Entity* bicoUpperPivot = new Entity();
          bicoUpperPivot->setTranslate(Vector3(0.35,0.28,0));
          headPivot->attach(bicoUpperPivot);

          BRep* bicoUpperMesh = new BRep();
          bicoUpperMesh->LoadfromFile("models/yellow_bicoUpper.obj");
          bicoUpperPivot->attach(bicoUpperMesh);

          // Bico Down
          {
            Entity* BicoDownPivot = new Entity();
            BicoDownPivot->setTranslate(Vector3(-0.10,-0.05,0));
            bicoUpperPivot->attach(BicoDownPivot);

            BRep* bicoDownMesh = new BRep();
            bicoDownMesh->LoadfromFile("models/yellow_bicoDown.obj");
            BicoDownPivot->attach(bicoDownMesh);
          }
        }


      }

      // Asa Negativa
      {
        Entity* asaPivot = new Entity();
        asaPivot->setTranslate(Vector3(0.2,0.1,0.4));
        bodyPivot->attach(asaPivot);

        {
          Keyframing* asaKeyframe = new Keyframing();
          asaPivot->setKeyframing(asaKeyframe);

          // Asa Negativa Poses

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-150,-70)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(45.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(30,-150,-70)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }

          int i;

          for(i = 0; i < 30; i++){
            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(i + 46.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(130,-150,-70)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(i + 46.5);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-150,-70)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

          }


        }

        BRep* asaMesh = new BRep();
        asaMesh->LoadfromFile("models/yellow_asaN.obj");
        asaPivot->attach(asaMesh);

      }

      // Asa Positiva
      {
        Entity* asaPivot = new Entity();
        asaPivot->setTranslate(Vector3(0.2,0.1,-0.4));
        bodyPivot->attach(asaPivot);

        {
          Keyframing* asaKeyframe = new Keyframing();
          asaPivot->setKeyframing(asaKeyframe);

          // Asa Negativa Poses

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(0.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(360-130,360-150,360-70)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(45.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(360-0,360-150,360-70)));
            asaKeyframe->addPose(ptrPose, animLinear);
          }

          int i;

          for(i = 0; i < 30; i++){
            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(i + 46.0);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(360-130,360-150,360-70)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

            {
              Pose* ptrPose = new Pose();
              ptrPose->setTime(i + 46.5);
              ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(360-0,360-150,360-70)));
              asaKeyframe->addPose(ptrPose, animLinear);
            }

          }


        }

        BRep* asaMesh = new BRep();
        asaMesh->LoadfromFile("models/yellow_asaP.obj");
        asaPivot->attach(asaMesh);
      }

      // Pata Negativa
      {
        Entity* feetPivot = new Entity();
        feetPivot->setTranslate(Vector3(0,-0.3,0.2));
        birdPivot->attach(feetPivot);

        BRep* feetMesh = new BRep();
        feetMesh->LoadfromFile("models/yellow_feet.obj");
        feetPivot->attach(feetMesh);

        Keyframing* feetKey = new Keyframing();
        feetMesh->setKeyframing(feetKey);

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(46.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,90)));
          feetKey->addPose(ptrPose, animLinear);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(47.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
          feetKey->addPose(ptrPose, animLinear);
        }

      }

      // Pata Positiva
      {
        Entity* feetPivot = new Entity();
        feetPivot->setTranslate(Vector3(0,-0.3,-0.2));
        birdPivot->attach(feetPivot);

        BRep* feetMesh = new BRep();
        feetMesh->LoadfromFile("models/yellow_feet.obj");
        feetPivot->attach(feetMesh);
      }

    }

    return birdPivot;

}

Entity* Application::createMage(){

  Entity* magePivot = new Entity();

  // PÁSSARO BOLADO

  magePivot->attach(createFlyingYellowBird());

  // MAGA BOLADA




  magePivot->setTranslate(Vector3(5,0,5));
  magePivot->setScale(Vector3(1,1,1)*0.2f);

  Keyframing* pivotKey = new Keyframing();
  magePivot->setKeyframing(pivotKey);

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(0.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5.5, 0.7, 2.1)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-90,0)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(46.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5.5, 0.7, 2.1)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-90,0)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(47.0);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5.5, 0.7, 2.1)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-90,-30)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(47.3);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5.5, 0.5, 2.4)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(40,-45,0)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(47.8);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(5.5, 0.3, 2.4)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(48.8);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(8, 3, 8)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-30,0)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(52);
    ptrPose->addPoseAttribute(new VectorAttribute("position", Vector3(50, 30, 25)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Pose* ptrPose = new Pose();
    ptrPose->setTime(70);
    ptrPose->addPoseAttribute(new VectorAttribute("position", (Vector3(50, 30, 25)*5) - (Vector3(-2,30,25)*5)));
    ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
    pivotKey->addPose(ptrPose, Interpolator::LINEAR);
  }

  {
    Entity* bodyPivot = new Entity();
    BRep* body = new BRep();
    body->LoadfromFile("models/mage_body.obj");
    bodyPivot->setTranslate(Vector3(0,3,0));
    bodyPivot->attach(body);
    magePivot->attach(bodyPivot);

    {
      Entity* headPivot = new Entity();
      BRep* head = new BRep();
      head->LoadfromFile("models/mage_head.obj");
      headPivot->setTranslate(Vector3(0,0.6,0));
      headPivot->attach(head);
      bodyPivot->attach(headPivot);

      Keyframing* headKey = new Keyframing();
      headPivot->setKeyframing(headKey);

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(0.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(34.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(35.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(-45,-90,0)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(37.5);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(-45,-90,0)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(39.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-30)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(39.3);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(40);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-30)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(41);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
        headKey->addPose(ptrPose, Interpolator::POLYNOM);
      }

    }

    // UpperHand Negative
    {
      Entity* upperHandPivot = new Entity();
      bodyPivot->attach(upperHandPivot);
      BRep* upperHand = new BRep();
      upperHandPivot->attach(upperHand);
      upperHand->LoadfromFile("models/mage_upperHandN.obj");
      upperHandPivot->setTranslate(Vector3(0,0.27,0.35));

      Keyframing* uhandKey = new Keyframing();
      upperHandPivot->setKeyframing(uhandKey);

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(0.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,0,0)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(15.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,00)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(25.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,0,0)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(35.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(90,0,0)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(36.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(-30,0,0)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(37.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(-30,0,0)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(39.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,70,30)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(43.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,70,30)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }


      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(45.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(60,0,0)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      // Hand Negative
      {
        Entity* handPivot = new Entity();
        upperHandPivot->attach(handPivot);
        BRep* hand = new BRep();
        handPivot->attach(hand);
        hand->LoadfromFile("models/mage_handN.obj");

        handPivot->setTranslate(Vector3(0,-0.025,0.55));

        Keyframing* handKey = new Keyframing();
        handPivot->setKeyframing(handKey);

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(0.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
          handKey->addPose(ptrPose, Interpolator::LINEAR);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(37.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
          handKey->addPose(ptrPose, Interpolator::LINEAR);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(39.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,120,0)));
          handKey->addPose(ptrPose, Interpolator::LINEAR);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(43.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,120,0)));
          handKey->addPose(ptrPose, Interpolator::LINEAR);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(45.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,0)));
          handKey->addPose(ptrPose, Interpolator::LINEAR);
        }

      }

    }

    // UpperHand Positive
    {
      Entity* upperHandPivot = new Entity();
      bodyPivot->attach(upperHandPivot);
      BRep* upperHand = new BRep();
      upperHandPivot->attach(upperHand);
      upperHand->LoadfromFile("models/mage_upperHandP.obj");
      upperHandPivot->setTranslate(Vector3(0,0.27,-0.35));


      Keyframing* uhandKey = new Keyframing();
      upperHandPivot->setKeyframing(uhandKey);

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(0.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-15,-30)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(46.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-15,-30)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }


      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(47.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(50,-30,0)));
        uhandKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      // Hand Positive
      {
        Entity* handPivot = new Entity();
        upperHandPivot->attach(handPivot);
        BRep* hand = new BRep();
        handPivot->attach(hand);
        hand->LoadfromFile("models/mage_handP.obj");

        handPivot->setTranslate(Vector3(0,-0.025,-0.45));

        {
          ParticleEmissor* mageparts = new MageParticle(200);
          mageparts->Setup();
          mageparts->setTranslate(Vector3(0,-1.4,-0.5f));
          handPivot->attach(mageparts);
        }


        Keyframing* handKey = new Keyframing();
        handPivot->setKeyframing(handKey);

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(0.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,15,0)));
          handKey->addPose(ptrPose, Interpolator::LINEAR);
        }


      }

    }

    // Upperlegs N
    {
      Entity* upperlegPivot = new Entity();
      bodyPivot->attach(upperlegPivot);
      BRep* upperleg = new BRep();
      upperleg->LoadfromFile("models/mage_upperlegsN.obj");
      upperlegPivot->attach(upperleg);

      upperlegPivot->setTranslate(Vector3(-0.15,-1.3,0.25));

      Keyframing* ulegsKey = new Keyframing();
      upperlegPivot->setKeyframing(ulegsKey);

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(0.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,90)));
        ulegsKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(46.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,90)));
        ulegsKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(47.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,-45,90)));
        ulegsKey->addPose(ptrPose, Interpolator::LINEAR);
      }


      {
        Entity* legPivot = new Entity();
        upperlegPivot->attach(legPivot);

        BRep* leg = new BRep();
        legPivot->attach(leg);

        leg->LoadfromFile("models/mage_legsN.obj");

        legPivot->setTranslate(Vector3(0,-0.6,0));

        Keyframing* legsKey = new Keyframing();
        legPivot->setKeyframing(legsKey);

        int i = 0;

        for (i = 0; i < 35; i++)
        {
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(i + 0.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-135)));
            legsKey->addPose(ptrPose, Interpolator::LINEAR);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(i + 0.5);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-45)));
            legsKey->addPose(ptrPose, Interpolator::LINEAR);
          }
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(36.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-90)));
          legsKey->addPose(ptrPose, Interpolator::LINEAR);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(46.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-90)));
          legsKey->addPose(ptrPose, Interpolator::LINEAR);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(47.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-45)));
          legsKey->addPose(ptrPose, Interpolator::LINEAR);
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(48.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-90)));
          legsKey->addPose(ptrPose, Interpolator::LINEAR);
        }

      }


    }

    // Upperlegs P
    {
      Entity* upperlegPivot = new Entity();
      bodyPivot->attach(upperlegPivot);
      BRep* upperleg = new BRep();
      upperleg->LoadfromFile("models/mage_upperlegsP.obj");
      upperlegPivot->attach(upperleg);

      upperlegPivot->setTranslate(Vector3(-0.15,-1.3,-0.25));

      Keyframing* ulegsKey = new Keyframing();
      upperlegPivot->setKeyframing(ulegsKey);

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(0.0);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,90)));
        ulegsKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(46.5);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,90)));
        ulegsKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Pose* ptrPose = new Pose();
        ptrPose->setTime(47.1);
        ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,30,90)));
        ulegsKey->addPose(ptrPose, Interpolator::LINEAR);
      }

      {
        Entity* legPivot = new Entity();
        upperlegPivot->attach(legPivot);

        BRep* leg = new BRep();
        legPivot->attach(leg);

        leg->LoadfromFile("models/mage_legsP.obj");

        legPivot->setTranslate(Vector3(0,-0.6,0));

        Keyframing* legsKey = new Keyframing();
        legPivot->setKeyframing(legsKey);

        int i = 0;

        for (i = 0; i < 35; i++)
        {
          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(i + 0.0);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-45)));
            legsKey->addPose(ptrPose, Interpolator::LINEAR);
          }

          {
            Pose* ptrPose = new Pose();
            ptrPose->setTime(i + 0.5);
            ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-135)));
            legsKey->addPose(ptrPose, Interpolator::LINEAR);
          }
        }

        {
          Pose* ptrPose = new Pose();
          ptrPose->setTime(36.0);
          ptrPose->addPoseAttribute(new VectorAttribute("orientation", Vector3(0,0,-90)));
          legsKey->addPose(ptrPose, Interpolator::LINEAR);
        }
      }

    }


  }

  return magePivot;

}

void Application::createStar()
{

  RigidBody * ptrRigidBody = new RigidBody();
  ptrRigidBody->setMass( 3.0f );
  ptrRigidBody->setGravity( Vector3( 0.0f, -1.0f, 0.0f ));
  ptrRigidBody->addForce( Vector3( -150.0f, 0.0f, -15.0f )); // trust


  BRep * ptrBall = new BRep();
  //ptrBall->LoadfromFile("models/mage_head.obj" );
  ptrBall->setTranslate( Vector3( 0.0f, 100.0f, -100.0f ));
  ptrBall->setRotate(Vector3(-45,0,0));
  ptrBall->setRigidBody( ptrRigidBody );

  // Particles

  {
    ParticleEmissor* trail1 = new MageCometa(3000);
    //trail1->setRotate(Vector3(180,0,0));
    trail1->setTranslate(Vector3(0,10,0));
    trail1->setScale(Vector3(1,4,1));
    // Curti
    trail1->Setup();
    ptrBall->attach(trail1);

    ParticleEmissor* glow = new GlowCometa(3000);
    glow->Setup();
    ptrBall->attach(glow);
  }


  ptrRigidBody->setBoundingSphere();


  Timer* timer = new Timer(32, ptrBall);

  this->addEntity( timer );
  this->uiPolyCount += ptrBall->getPolyCount();
}
