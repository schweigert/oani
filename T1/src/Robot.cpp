#include "Robot.h"

Robot::Robot(): Actor()
{
    this->Initialize();
}

Robot::Robot( const Robot &clone ): Actor( clone )
{
    this->Initialize();
}


Robot::Robot( Robot* ptrClone ): Actor( ptrClone )
{
    this->Initialize();
}

void Robot::Initialize()
{
	PrimitiveGL * ptrBase = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrBase->setScale( Vector3( 0.35f, 0.1f, 0.35f ));
	ptrBase->setColor( Vector3::RED );
	this->listOfEntities.push_back( ptrBase );

	PrimitiveGL * ptrStem = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrStem->setScale( Vector3( 0.05f, 0.4f, 0.05f ) );
	ptrStem->setTranslate( Vector3( 0.0f, 0.2f, 0.0f ));
	this->listOfEntities.push_back( ptrStem );

	PrimitiveGL * ptrBody = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrBody->setScale( Vector3( 0.5f, 0.8f, 0.3f ) );
	ptrBody->setTranslate( Vector3( 0.0f, 0.7f, 0.0f ));
	ptrBody->setColor( Vector3::RED );
	this->listOfEntities.push_back( ptrBody );

	PrimitiveGL * ptrHead = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrHead->setScale( Vector3( 0.2f, 0.2f, 0.2f ) );
	ptrHead->setTranslate( Vector3( 0.0f, 1.2f, 0.0f ));
	this->listOfEntities.push_back( ptrHead );

	// bra�o esquerdo
	PrimitiveGL * ptrArm1 = new PrimitiveGL( PrimitiveGL::CUBE );
	ptrArm1->setScale( Vector3( 0.1f, 0.5f, 0.1f ) );
	ptrArm1->setTranslate( Vector3( 0.3f, 0.8f, 0.0f ));
	this->listOfEntities.push_back( ptrArm1 );

	// bra�o direito
	PrimitiveGL * ptrArm2 = new PrimitiveGL( ptrArm1 );
	ptrArm2->setTranslate( Vector3( -0.3f, 0.8f, 0.0f ));
	this->listOfEntities.push_back( ptrArm2 );
}
