#ifndef _APPLICATION_NOT_INCLUDED_
#define _APPLICATION_NOT_INCLUDED_

#include "Entity.h"
#include "Camera.h"

#include <vector>
#include <string>
using namespace std;


class Application
{
private:
	string          strAppName,
		            strCurrentFPS;
	unsigned int    uiWindowWidth,
				    uiWindowHeight,
				    uiFrames;
	double		    dCounterTimer;
	vector<Entity*> listOfEntities;

	void CalculateFPS( double );

public:
	Application( string = "OAC 2017" );
	~Application();

	void setWindowSize( unsigned int, unsigned int );

	inline unsigned int getWidth() { return this->uiWindowWidth; }

	inline unsigned int getHeight() { return this->uiWindowHeight; }

	inline string getTitle() { return this->strAppName + " - [" + this->strCurrentFPS + "]"; }

	int Execute( double );
	void RenderFrame();

  void addEntity( Entity* );
	bool setEntity( Entity*, unsigned int );
	Entity* getEntity( unsigned int );

	Camera* getCamera();
};

#endif
