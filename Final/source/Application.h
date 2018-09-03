
#ifndef _APPLICATION_NOT_INCLUDED_
#define _APPLICATION_NOT_INCLUDED_

#include "Entity.h"
#include "Camera.h"

#include <vector>
#include <string>
using namespace std;

class RigidBody;

/**
	\class Application
	\brief Classe responsavel por controlar o ambiente grafico e gerenciamento do ambiente IDS.
*/
class Application
{
private:
	string          strAppName,        //! nome do titulo da janela da aplicacao
		            strCurrentFPS;     //! valor corrente (convertido em texto) do FPS disponivel para execucao da aplicacao
	unsigned int    uiWindowWidth,     //! largura da janela da aplicacao
				    uiWindowHeight,    //! altura da janela da aplicacao
                    uiPolyCount,       ///< contador da quantidade de poligonos sendo renderizados por frame
				    uiFrames;          //! contador de frames para o calculo do FPS
	double		    dCounterTimer;     //! contador de tempo para o calculo do FPS
	vector<Entity*> listOfEntities;    ///< lista de ponteiros para entidades que pertencem a cena sendo renderizada/animada
    vector<Entity*> listOfRigidBodies; ///< lista das entities que contem um componente RigidBody

	void CalculateFPS( double );

	// Scene Creation Methods
	void createInitialBird();
	void CreateBirdBoidsScene();
	void CreateVisualObjects();
	void createStar();

	Entity* createBirdBoid();
	Entity* createFlyingYellowBird();
	Entity* createMage();

public:
	Application( string = "A OpenGL History" );
	~Application();

	void setWindowSize( unsigned int, unsigned int );
	/**
		\brief Retorna o valor corrente da largura da janela da aplicacao
		\return unsigned int o valor da largura da janela
	*/
	inline unsigned int getWidth() { return this->uiWindowWidth; }
	/**
		\brief Retorna o valor corrente da altura da janela da aplicacao
		\return unsigned int o valor da alura da janela
	*/
	inline unsigned int getHeight() { return this->uiWindowHeight; }
    /**
       \brief Retorna o valor da lista de corpos rigidos presentes na cena a fim de permitir simula�ao de fisica
       \return vector contendo a lista de entities que contem um componente RigidBody
    */
    inline vector<Entity*> getRigidBodies() { return this->listOfRigidBodies; }

	string getTitle();

	int Execute( double );
	void RenderFrame();

    void addEntity( Entity* );
	bool setEntity( Entity*, unsigned int );
	Entity* getEntity( unsigned int );

	Camera* getCamera();

	void CreateScene();
};

#endif
