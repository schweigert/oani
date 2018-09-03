#include "Fence.h"

Fence::Fence(): Object()
{
  this->Initialize();
}


Fence::Fence( const Fence &clone ): Object( clone )
{
    this->Initialize();
}



Fence::Fence( Fence* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}


void Fence::Initialize()
{
	PrimitiveGL * ptrFence1 = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrFence1->setSize( 0.5f );
	ptrFence1->setScale( Vector3( 0.2f, 1.0f, 0.05f ));
	ptrFence1->setTranslate( Vector3( -0.625f, 0.5f, 0.0f ));
	ptrFence1->setColor( Vector3( 0.46f, 0.38f, 0.25f ) ); // marrom RGB(119, 98, 66)
	this->listOfEntities.push_back( ptrFence1 );

	PrimitiveGL * ptrFence2 = new PrimitiveGL( ptrFence1 );
	ptrFence2->setTranslate( Vector3( -0.375f, 0.5f, 0.0f ));
	this->listOfEntities.push_back( ptrFence2 );

	PrimitiveGL * ptrFence3 = new PrimitiveGL( ptrFence1 );
	ptrFence3->setTranslate( Vector3( -0.125f, 0.5f, 0.0f ));
	this->listOfEntities.push_back( ptrFence3 );

	PrimitiveGL * ptrFence4 = new PrimitiveGL( ptrFence1 );
	ptrFence4->setTranslate( Vector3( 0.125f, 0.5f, 0.0f ));
	this->listOfEntities.push_back( ptrFence4 );

	PrimitiveGL * ptrFence5 = new PrimitiveGL( ptrFence1 );
	ptrFence5->setTranslate( Vector3( 0.375f, 0.5f, 0.0f ));
	this->listOfEntities.push_back( ptrFence5 );

	PrimitiveGL * ptrFence6 = new PrimitiveGL( ptrFence1 );
	ptrFence6->setTranslate( Vector3( 0.625f, 0.5f, 0.0f ));
	this->listOfEntities.push_back( ptrFence6 );

	PrimitiveGL * ptrFence7 = new PrimitiveGL( ptrFence1 );
	ptrFence7->setScale( Vector3( 3.0f, 0.2f, 0.05f ));
	ptrFence7->setTranslate( Vector3( 0.0, 0.4f, 0.0f ));
	this->listOfEntities.push_back( ptrFence7 );

	PrimitiveGL * ptrFence8 = new PrimitiveGL( ptrFence1 );
	ptrFence8->setScale( Vector3( 3.0f, 0.2f, 0.05f ));
	ptrFence8->setTranslate( Vector3( 0.0, 0.6f, 0.0f ));
	this->listOfEntities.push_back( ptrFence8 );
}
