
#include "Camera.h"
//#include <windows.h>
#include <GL/glut.h>
#include <math.h>


Camera::Camera( Camera::CameraType camType ): Entity()
{
	this->vTranslate  = (( Vector3 ) Vector3::UNIT_Z) * -1;
	this->vFocalPoint = Vector3::ZERO;
	this->vUpVector   = Vector3::UNIT_Y;
	this->cameraType  = camType;

	this->setViewport( 800, 600 );
	this->setClippingPlanes( 1.0f, 150.0f );
	this->setFOV( 30.0f );
}

Camera::Camera( const Camera& clone ): Entity( clone )
{
	this->vFocalPoint = clone.vFocalPoint;
	this->vUpVector   = clone.vUpVector;
	this->cameraType  = clone.cameraType;
	this->uiWidth     = clone.uiWidth;
	this->uiHeight    = clone.uiHeight;
	this->fNearPlane  = clone.fNearPlane;
	this->fFarPlane   = clone.fFarPlane;
	this->fFOV        = clone.fFOV;
}

Camera::Camera( Camera* ptrClone ): Entity( ptrClone )
{
	this->vFocalPoint = ptrClone->vFocalPoint;
	this->vUpVector   = ptrClone->vUpVector;
	this->cameraType  = ptrClone->cameraType;
	this->uiWidth     = ptrClone->uiWidth;
	this->uiHeight    = ptrClone->uiHeight;
	this->fNearPlane  = ptrClone->fNearPlane;
	this->fFarPlane   = ptrClone->fFarPlane;
	this->fFOV        = ptrClone->fFOV;
}

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

		gluLookAt( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z,
				   this->vFocalPoint.x, this->vFocalPoint.y, this->vFocalPoint.z,
				   this->vUpVector.x, this->vUpVector.y, this->vUpVector.z );
		break;
	}
	glPopMatrix();
}

void Camera::OnLoop( double dDeltaTime )
{
	this->TurnAround_H( 20.0f * ( float )dDeltaTime * 0.001f );
}

void Camera::setClippingPlanes( float fNear, float fFar )
{
	this->fNearPlane = fNear;
	this->fFarPlane  = fFar;
}

void Camera::setFOV( float fFOV )
{
	if( fFOV > 0.0f && fFOV <= 360.0f )
		this->fFOV = fFOV;
}

void Camera::setViewport( unsigned int uiWidth, unsigned int uiHeight )
{
	if( uiWidth > 0 && uiHeight > 0 )
	{
		this->uiWidth  = uiWidth;
		this->uiHeight = uiHeight;

		glViewport( 0.0f, 0.0f, uiWidth, uiHeight );
	}
}

void Camera::Yaw( float fAngle )
{
	fAngle /= 57.3f;

	Vector3 temp = this->vFocalPoint - this->vTranslate;

	this->vFocalPoint =	Vector3(
		temp.x * ( float )cos( fAngle ) + temp.z * ( float )sin( fAngle ),
		temp.y,
		temp.z * ( float )cos( fAngle ) - temp.x * ( float )sin( fAngle ) );

	this->vFocalPoint = this->vFocalPoint + this->vTranslate;
}

void Camera::Roll( float fAngle )
{
	fAngle /= 57.3f;

	Vector3 temp    = this->vUpVector;
	this->vUpVector = Vector3(
		temp.x * ( float )cos( fAngle ) - temp.y * ( float )sin( fAngle ),
		temp.x * ( float )sin( fAngle ) + temp.y * ( float )cos( fAngle ),
		temp.z );
;
}

void Camera::Pitch( float fAngle )
{
	fAngle /= 57.3f;

	Vector3 temp = this->vFocalPoint - this->vTranslate;

	this->vFocalPoint =	Vector3(
		temp.x ,
		temp.y * ( float )cos( fAngle ) - temp.z * ( float )sin( fAngle ),
		temp.y * ( float )sin( fAngle ) + temp.z * ( float )cos( fAngle ) );
	this->vFocalPoint = this->vFocalPoint + this->vTranslate;

	temp = this->vUpVector;
	this->vUpVector = Vector3(
		temp.x ,
		temp.y * ( float )cos( fAngle ) - temp.z * ( float )sin( fAngle ),
		temp.y * ( float )sin( fAngle ) + temp.z * ( float )cos( fAngle ) );

}

void Camera::TurnAround_H( float fAngle )
{
	fAngle /= 57.3f;

	Vector3 temp = this->vTranslate - this->vFocalPoint;
	this->vTranslate =	Vector3(
		temp.x * ( float )cos( fAngle ) + temp.z * ( float )sin( fAngle ),
		temp.y,
		temp.z * ( float )cos( fAngle ) - temp.x * ( float )sin( fAngle ) );

	this->vTranslate = this->vFocalPoint + this->vTranslate;
}

void Camera::TurnAround_V( float fAngle )
{
	fAngle /= 57.3f;

	Vector3 temp = this->vTranslate - this->vFocalPoint;
	this->vTranslate =	Vector3(
		temp.x ,
		temp.y * ( float )cos( fAngle ) - temp.z * ( float )sin( fAngle ),
		temp.y * ( float )sin( fAngle ) + temp.z * ( float )cos( fAngle ) );
	this->vTranslate = this->vFocalPoint + this->vTranslate;

	temp = this->vUpVector;
	this->vUpVector = Vector3(
		temp.x ,
		temp.y * ( float )cos( fAngle ) - temp.z * ( float )sin( fAngle ),
		temp.y * ( float )sin( fAngle ) + temp.z * ( float )cos( fAngle )
	);

}
