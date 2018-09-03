#include "Chair.h"

Chair::Chair(): Object()
{
    this->Initialize();
}

Chair::Chair( const Chair &clone ): Object( clone )
{
    this->Initialize();
}


Chair::Chair( Chair* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}

void Chair::Initialize()
{
  // Base da Cadeira
  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 1.0f, 0.2f, 1.0f ));
    ptrBase->setTranslate (Vector3(0.0f,1.0f,0.0f));
    ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    this->listOfEntities.push_back( ptrBase );
  }

  // Pé da Cadeira
  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.1f, 1.0f, 0.1f ));
    ptrBase->setTranslate (Vector3(0.4f,0.5f,0.4f));
    ptrBase->setRotate (Vector3(0,0,0));
    ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    this->listOfEntities.push_back( ptrBase );
  }

  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.1f, 1.0f, 0.1f ));
    ptrBase->setTranslate (Vector3(-0.4f,0.5f,0.4f));
    ptrBase->setRotate (Vector3(0,0,0));
    ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    this->listOfEntities.push_back( ptrBase );
  }

  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.1f, 1.0f, 0.1f ));
    ptrBase->setTranslate (Vector3(-0.4f,0.5f,-0.4f));
    ptrBase->setRotate (Vector3(0,0,0));
    ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    this->listOfEntities.push_back( ptrBase );
  }

  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 0.1f, 1.0f, 0.1f ));
    ptrBase->setTranslate (Vector3(0.4f,0.5f,-0.4f));
    ptrBase->setRotate (Vector3(0,0,0));
    ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    this->listOfEntities.push_back( ptrBase );
  }


}
