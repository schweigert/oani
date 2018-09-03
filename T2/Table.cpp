#include "Table.h"

Table::Table(): Object()
{
    this->Initialize();
}

Table::Table( const Table &clone ): Object( clone )
{
    this->Initialize();
}


Table::Table( Table* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}

void Table::Initialize()
{
  
  // Base da Mesa
  {
  	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
  	ptrBase->setScale( Vector3( 4.0f, 0.3f, 6.0f ));
    ptrBase->setTranslate (Vector3(0.0f,1.7f,0.0f));
  	ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
  	this->listOfEntities.push_back( ptrBase );
  }

    // Pernas
    {
    	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    	ptrBase->setScale( Vector3( 0.3f, 1.7f, 0.3f ));
      ptrBase->setTranslate (Vector3(1.7f,1.7f/2.0f,2.7f));
    	ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    	this->listOfEntities.push_back( ptrBase );
    }

    // Pernas
    {
    	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    	ptrBase->setScale( Vector3( 0.3f, 1.7f, 0.3f ));
      ptrBase->setTranslate (Vector3(-1.7f,1.7f/2.0f,2.7f));
    	ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    	this->listOfEntities.push_back( ptrBase );
    }

    // Pernas
    {
    	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    	ptrBase->setScale( Vector3( 0.3f, 1.7f, 0.3f ));
      ptrBase->setTranslate (Vector3(1.7f,1.7f/2.0f,-2.7f));
    	ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    	this->listOfEntities.push_back( ptrBase );
    }

    // Pernas
    {
    	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
    	ptrBase->setScale( Vector3( 0.3f, 1.7f, 0.3f ));
      ptrBase->setTranslate (Vector3(-1.7f,1.7f/2.0f,-2.7f));
    	ptrBase->setColor( Vector3(50.0/255.0,20.0/255.0,30.0/255.0) );
    	this->listOfEntities.push_back( ptrBase );
    }


}
