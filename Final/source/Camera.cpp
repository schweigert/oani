#include "Camera.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Entity.h"
#include "VectorAttribute.h"
#include "RigidBody.h"
/**
  \brief Construtor padrao para a classe Camera
  Cria uma camera virtual posicionada no eixo Z negativo, olhando para a origem, orientada para o eixo Y
  \param camType tipo da camera (ortografica ou perspectiva)
*/
Camera::Camera( Camera::CameraType camType , bool lookAtbooll): Entity()
{
	this->vTranslate = (( Vector3 ) Vector3::UNIT_Z) * -1; // transformar um "const Vector3" em um "Vector3" a fim de permitir sua manipula��o
	this->vFocalPoint = Vector3::ZERO;
	this->vUpVector = Vector3::UNIT_Y;
	this->cameraType = camType;
	this->setViewport( 960, 540 );
	this->setClippingPlanes( 1.0f, 1500.0f );  // default para camera perspectiva
	this->setFOV( 30.0f ); // uso apenas com a camera perspectiva

	this->boolLookAt = lookAtbooll;
}
/**
  \brief Construtor de copia para a classe Camera
  Cria uma copia exata de um objeto Camera existente
  \param clone Objeto Camera a ser clonado
*/
Camera::Camera( const Camera& clone ): Entity( clone )
{
	this->vFocalPoint = clone.vFocalPoint;
	this->vUpVector = clone.vUpVector;
	this->cameraType = clone.cameraType;
	this->uiWidth = clone.uiWidth;
	this->uiHeight = clone.uiHeight;
	this->fNearPlane = clone.fNearPlane;
	this->fFarPlane = clone.fFarPlane;
	this->fFOV = clone.fFOV;
}
/**
  \brief Construtor de copia para a classe Camera a partir de ponteiros
  Cria uma copia exata de um objeto Camera existente
  \param ptrClone Ponteiro para um objeto Camera a ser clonado
*/
Camera::Camera( Camera* ptrClone ): Entity( ptrClone )
{
	this->vFocalPoint = ptrClone->vFocalPoint;
	this->vUpVector = ptrClone->vUpVector;
	this->cameraType = ptrClone->cameraType;
	this->uiWidth = ptrClone->uiWidth;
	this->uiHeight = ptrClone->uiHeight;
	this->fNearPlane = ptrClone->fNearPlane;
	this->fFarPlane = ptrClone->fFarPlane;
	this->fFOV = ptrClone->fFOV;
}
/**
   \brief Apresenta a camera virtual no OPENGL utilizando os parametros fornecidos
*/
void Camera::OnRender()
{
	glPushMatrix();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

	switch( this->cameraType )
	{
	case Camera::ORTOGRAPHIC:
		glOrtho( 0.0f, this->uiWidth, this->uiHeight, 0.0f, this->fNearPlane, this->fFarPlane );
		break;

	case Camera::PERSPECTIVE:
		gluPerspective( this->fFOV, (float)this->uiWidth/this->uiHeight, this->fNearPlane, this->fFarPlane );
		gluLookAt( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z, // camera position
				   this->vFocalPoint.x, this->vFocalPoint.y, this->vFocalPoint.z,  // camera focus
				   this->vUpVector.x, this->vUpVector.y, this->vUpVector.z ); // camera up vec
		break;
	}

	glMatrixMode( GL_MODELVIEW );

	if( this->listOfEntities.size() > 0 )
		for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
			ptrEntity != this->listOfEntities.end(); ptrEntity++ )
			(* ptrEntity )->OnRender();

	glPopMatrix();
}
/**
  \brief Define o ponto para onde a camera esta apontada (foco de interesse)
  \param vFocalPoint ponto focal da camera
*/
void Camera::LookAt( Vector3 vFocalPoint )
{
	this->vFocalPoint = vFocalPoint;
}

void Camera::LookAt( Entity* parentalLook )
{
	this->boolLookAt = true;
	this->entLookAt = parentalLook;
}
/**
   \brief Atualiza os parametros da camera para o proximo frame da animacao
   \param uiDeltaTime tempo transcorrido entre duas atualizacoes sucessivas (em milisegundos)
*/
void Camera::OnLoop( double dDeltaTime )
{
	if(this->boolLookAt){
		this->vFocalPoint = entLookAt->getTranslate();
	}

	if( this->ptrKeyframing )
	{
		Pose * ptrCurrentPose = NULL;
		if( ptrCurrentPose = this->ptrKeyframing->OnLoop( dDeltaTime ) )
		{
			if( ptrCurrentPose->hasPoseAttributeName( "position" ) )
				this->setTranslate( ( ( VectorAttribute* ) ptrCurrentPose->getPoseAttribute( "position" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "orientation" ) )
				this->LookAt( ( ( VectorAttribute* ) ptrCurrentPose->getPoseAttribute( "orientation" ) )->getValue() );

		}
	}

	if( this->listOfEntities.size() > 0 )
		for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
			ptrEntity != this->listOfEntities.end(); ptrEntity++ )
			(* ptrEntity )->OnLoop(dDeltaTime);
	//Entity::OnLoop( dDeltaTime );
}
/**
   \brief Define as distancias minima e maxima dos planos de corte de visualizacao da camera.<br>
   No caso da camera perspectiva, esses valores precisam ser positivos sendo a distancia maxima superior a minima. No caso da camera ortografica, valores negativos
   significam que os planos de corte localizam-se antes da camera.
   \param fNear distancia minima de visualizacao da camera
   \param fFar distancia maxima de visualizacao da camera
*/
void Camera::setClippingPlanes( float fNear, float fFar )
{
	this->fNearPlane = fNear;
	this->fFarPlane = fFar;
}
/**
   \brief Define o angulo de abertura (em graus) do campo visual da camera Perspectiva. Valores validos sao entre 1 e 360 graus.
   \param fFOV angulo de abertura do campo visual (Field of View) da camera Perspectiva
*/
void Camera::setFOV( float fFOV )
{
	if( fFOV > 0.0f && fFOV <= 360.0f )
		this->fFOV = fFOV;
}
/**
   \brief Define as dimensoes da viewport corrente em uso no sistema. Estes valores permitem a determinacao da relacao de aspecto (aspect ratio) da janela OPENGL.<br>
   Valores validos sao inteiros nao nulos.
   \param uiWidth largura da viewport corrente
   \param uiHeight altura da viewport corrente
*/
void Camera::setViewport( unsigned int uiWidth, unsigned int uiHeight )
{
	if( uiWidth > 0 && uiHeight > 0 )
	{
		this->uiWidth = uiWidth;
		this->uiHeight = uiHeight;
	}
}
/**
   \brief Define o movimento rotacional do ponto de interesse da camera em torno de sua posicao em relacao a seu eixo de orientacao (UP vector).
   \param fAngle angulo (em graus) do movimento.
*/
void Camera::Yaw( float fAngle )
{
	fAngle /= 57.3f; // converte graus em radianos

	Vector3 temp = this->vFocalPoint - this->vTranslate; // transforma coordenadas globais em coordenadas locais considerando a posicao da camera como origem

	this->vFocalPoint =	Vector3(   // calcula a rota��o do ponto focal da camera no eixo Y
		temp.x * cos( fAngle ) + temp.z * sin( fAngle ),
		temp.y,
		temp.z * cos( fAngle ) - temp.x * sin( fAngle ) );

	this->vFocalPoint = this->vFocalPoint + this->vTranslate; // devolve o ponto focal da camera para sua posi��o original em coordenadas globais
}
/**
   \brief Define o movimento rotacional da camera em relacao a seu eixo longitudinal. Este movimento rotaciona o vetor orientacao da camera em torno da posicao da mesma.
   \param fAngle angulo (em graus) do movimento.
*/
void Camera::Roll( float fAngle )
{
	fAngle /= 57.3f; // converte graus em radianos

	// como o up vector apenas denota dire��o e n�o posi��o, sua localiza��o espacial � irrelevante, portanto n�o se faz necessaria a convers�o entre sistemas de coordenadas
	// global <-> local
	Vector3 temp = this->vUpVector;
	this->vUpVector = Vector3(   // calcula a rota��o do vetor orienta��o da camera no eixo X
		temp.x * (float)cos( fAngle ) - temp.y * (float)sin( fAngle ),
		temp.x * (float)sin( fAngle ) + temp.y * (float)cos( fAngle ),
		temp.z );
;
}
/**
   \brief Define o movimento rotacional do ponto de interesse e vetor orientacao da camera em torno da posicao em relacao a seu eixo sagital.
   \param fAngle angulo (em graus) do movimento.
*/
void Camera::Pitch( float fAngle )
{
	fAngle /= 57.3f; // converte graus em radianos

	Vector3 temp = this->vFocalPoint - this->vTranslate; // transforma coordenadas globais em coordenadas locais considerando a posicao da camera como origem

	this->vFocalPoint =	Vector3(   // calcula a rota��o do ponto focal da camera no eixo X
		temp.x ,
		temp.y * (float)cos( fAngle ) - temp.z * (float)sin( fAngle ),
		temp.y * (float)sin( fAngle ) + temp.z * (float)cos( fAngle ) );
	this->vFocalPoint = this->vFocalPoint + this->vTranslate; // devolve a posi��o da camera para sua posi��o original em coordenadas globais

	// como o up vector apenas denota dire��o e n�o posi��o, sua localiza��o espacial � irrelevante, portanto n�o se faz necessaria a convers�o entre sistemas de coordenadas
	// global <-> local
	temp = this->vUpVector;
	this->vUpVector = Vector3(   // calcula a rota��o do vetor orienta��o da camera no eixo X
		temp.x ,
		temp.y * (float)cos( fAngle ) - temp.z * (float)sin( fAngle ),
		temp.y * (float)sin( fAngle ) + temp.z * (float)cos( fAngle ) );

}
/**
   \brief Define o movimento rotacional da posicao da camera em torno de seu ponto de interesse em relacao a seu eixo de orientacao (UP vector) horizontalmente.
   \param fAngle angulo (em graus) do movimento.
*/
void Camera::TurnAround_H( float fAngle )
{
	fAngle /= 57.3f; // converte graus em radianos

	Vector3 temp = this->vTranslate - this->vFocalPoint; // transforma coordenadas globais em coordenadas locais considerando a posicao da camera como origem

	this->vTranslate =	Vector3(   // calcula a rota��o do ponto focal da camera no eixo Y
		temp.x * cos( fAngle ) + temp.z * sin( fAngle ),
		temp.y,
		temp.z * cos( fAngle ) - temp.x * sin( fAngle ) );

	this->vTranslate = this->vFocalPoint + this->vTranslate; // devolve o ponto focal da camera para sua posi��o original em coordenadas globais
}
/**
   \brief Define o movimento rotacional da posicao da camera em torno de seu ponto de interesse em relacao a seu eixo sagital.
   \param fAngle angulo (em graus) do movimento.
*/
void Camera::TurnAround_V( float fAngle )
{
	fAngle /= 57.3f; // converte graus em radianos

	Vector3 temp = this->vTranslate - this->vFocalPoint; // transforma coordenadas globais em coordenadas locais considerando a posicao da camera como origem

	this->vTranslate =	Vector3(   // calcula a rota��o do ponto focal da camera no eixo X
		temp.x ,
		temp.y * (float)cos( fAngle ) - temp.z * (float)sin( fAngle ),
		temp.y * (float)sin( fAngle ) + temp.z * (float)cos( fAngle ) );
	this->vTranslate = this->vFocalPoint + this->vTranslate; // devolve a posi��o da camera para sua posi��o original em coordenadas globais

	// como o up vector apenas denota dire��o e n�o posi��o, sua localiza��o espacial � irrelevante, portanto n�o se faz necessaria a convers�o entre sistemas de coordenadas
	// global <-> local
	temp = this->vUpVector;
	this->vUpVector = Vector3(   // calcula a rota��o do vetor orienta��o da camera no eixo X
		temp.x ,
		temp.y * (float)cos( fAngle ) - temp.z * (float)sin( fAngle ),
		temp.y * (float)sin( fAngle ) + temp.z * (float)cos( fAngle ) );

}
