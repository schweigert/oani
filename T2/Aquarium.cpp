#include "Aquarium.h"

Aquarium::Aquarium(): Object()
{
    this->Initialize();
}

Aquarium::Aquarium( const Aquarium &clone ): Object( clone )
{
    this->Initialize();
}


Aquarium::Aquarium( Aquarium* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}

void Aquarium::Initialize()
{

  // FUNDO
  {
  	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::PLANE );
  	ptrBase->setScale( Vector3( 1.5f, 1.0f, 1.0f ));
    ptrBase->setTranslate (Vector3(0.0f,0.0f,0.0f));
  	ptrBase->setColor( Vector3(0,1,1) );
  	this->listOfEntities.push_back( ptrBase );
  }
  // FUNDO VERTICAL
  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::PLANE );
    ptrBase->setScale( Vector3( 1.5f, 1.0f, 1.5f ));
    ptrBase->setTranslate (Vector3(0.0f,0.0f,-0.30f));
    ptrBase->setRotate (Vector3(90,0,0));
    ptrBase->setColor( Vector3(0,1,1) );
    this->listOfEntities.push_back( ptrBase );
  }
  // FUNDO Lateral
  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::PLANE );
    ptrBase->setScale( Vector3( 1.0f, 1.0f, 1.0f ));
    ptrBase->setTranslate (Vector3(-1.5f,0.5f,-0.2f));
    ptrBase->setRotate (Vector3(0,0,90));
    ptrBase->setColor( Vector3(0,1,1) );
    this->listOfEntities.push_back( ptrBase );
  }



}
