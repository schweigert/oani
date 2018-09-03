#include "Desk.h"

Desk::Desk(): Object()
{
    this->Initialize();
}

Desk::Desk( const Desk &clone ): Object( clone )
{
    this->Initialize();
}


Desk::Desk( Desk* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}

void Desk::Initialize()
{
  // Base do balcão
  {
  	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
  	ptrBase->setScale( Vector3( 4.0f, 2.0f, 1.5f ));
    ptrBase->setTranslate (Vector3(0.0f,1.0f,0.0f));
  	ptrBase->setColor( Vector3::RED );
  	this->listOfEntities.push_back( ptrBase );
  }
  // Tampa de Mármore Negro
  {
  	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
  	ptrBase->setScale( Vector3( 4.0f, 0.1f, 1.6f ));
    ptrBase->setTranslate (Vector3(0.0f,2.05f,0.1f));
  	ptrBase->setColor( Vector3::BLACK );
  	this->listOfEntities.push_back( ptrBase );
  }

  // Gaveta 001
  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 1.5f, 0.5f, 1.6f ));
    ptrBase->setTranslate (Vector3(1.2f,0.4f,0.1f));
    ptrBase->setColor( Vector3::GRAY );
    this->listOfEntities.push_back( ptrBase );

    PrimitiveGL * ptrAux = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrAux->setScale( Vector3( 0.5f, 0.1f, 1.7f ));
    ptrAux->setTranslate (Vector3(1.2f,0.4f,0.1f));
    ptrAux->setColor( Vector3::BLACK );
    this->listOfEntities.push_back( ptrAux );

  }
  // Gaveta 002
  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 1.5f, 0.5f, 1.6f ));
    ptrBase->setTranslate (Vector3(1.2f,1.0f,0.1f));
    ptrBase->setColor( Vector3::GRAY );
    this->listOfEntities.push_back( ptrBase );

    PrimitiveGL * ptrAux = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrAux->setScale( Vector3( 0.5f, 0.1f, 1.7f ));
    ptrAux->setTranslate (Vector3(1.2f,1.0f,0.1f));
    ptrAux->setColor( Vector3::BLACK );
    this->listOfEntities.push_back( ptrAux );
  }

  // Gaveta 003
  {
    PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrBase->setScale( Vector3( 1.5f, 0.5f, 1.6f ));
    ptrBase->setTranslate (Vector3(1.2f,1.6f,0.1f));
    ptrBase->setColor( Vector3::GRAY );
    this->listOfEntities.push_back( ptrBase );

    PrimitiveGL * ptrAux = new PrimitiveGL( PrimitiveGL::CUBE );
    ptrAux->setScale( Vector3( 0.5f, 0.1f, 1.7f ));
    ptrAux->setTranslate (Vector3(1.2f,1.6f,0.1f));
    ptrAux->setColor( Vector3::BLACK );
    this->listOfEntities.push_back( ptrAux );
  }


}
