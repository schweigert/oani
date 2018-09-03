#include "House.h"


House::House(): Object()
{
    this->Initialize();
}


House::House( const House &clone ): Object( clone )
{
    this->Initialize();
}



House::House( House* ptrClone ): Object( ptrClone )
{
    this->Initialize();
}


void House::Initialize()
{
	PrimitiveGL * ptrHouse = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrHouse->setScale( Vector3( 1.0f, 0.7f, 1.0f ));
	ptrHouse->setTranslate( Vector3( 0.0f, 0.35f, 0.0f ));
	this->listOfEntities.push_back( ptrHouse );

	PrimitiveGL * ptrRoof = new PrimitiveGL( PrimitiveGL::CONE );
	ptrRoof->setResolution( 4, 4 );
	ptrRoof->setScale( Vector3( 1.0f, 1.0f, 0.4f ));
	ptrRoof->setColor( Vector3::YELLOW );
	ptrRoof->setTranslate( Vector3( 0.0f, 0.7f, 0.0f ));
	ptrRoof->setRotate( Vector3( -90.0f, 45.0f, 0.0f ) );
	this->listOfEntities.push_back( ptrRoof );
}
