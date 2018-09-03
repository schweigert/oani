/**
	\file Application.h
	\brief Definicao do prototipo da classe Application para gerencimento do IDS<p>

	Desenvolvido por <b>Rogerio Eduardo da Silva</b><br>
	Fevereiro, 2015. Universidade do Estado de Santa Catarina (UDESC)
*/

#ifndef _APPLICATION_NOT_INCLUDED_
#define _APPLICATION_NOT_INCLUDED_

#include "Entity.h"
#include "Camera.h"

#include <vector>
#include <string>
using namespace std;

/**
	\class Application
	\brief Classe responsavel por controlar o ambiente grafico e gerenciamento do ambiente IDS.
*/
class Application
{
private:
	string          strAppName,      //! nome do titulo da janela da aplicacao
		            strCurrentFPS;   //! valor corrente (convertido em texto) do FPS disponivel para execucao da aplicacao
	unsigned int    uiWindowWidth,   //! largura da janela da aplicacao
				    uiWindowHeight,  //! altura da janela da aplicacao
				    uiFrames;        //! contador de frames para o calculo do FPS
	double		    dCounterTimer;   //! contador de tempo para o calculo do FPS
	vector<Entity*> listOfEntities;  ///< lista de ponteiros para entidades que pertencem a cena sendo renderizada/animada

	void CalculateFPS( double );

public:
	Application( string = "OAC 2017" );
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
		\brief Retorna o valor corrente do titulo da aplicacao.<br>
		O titulo e o resultado do nome da aplicacao + o valor corrente para o FPS.

		\return string titulo da aplicacao
	*/
	inline string getTitle() { return this->strAppName + " - [" + this->strCurrentFPS + "]"; }

	int Execute( double );
	void RenderFrame();

    void addEntity( Entity* );
	bool setEntity( Entity*, unsigned int );
	Entity* getEntity( unsigned int );

	Camera* getCamera();
};

#endif
