#ifndef _CAMERA_NOT_INCLUDED_
#define _CAMERA_NOT_INCLUDED_

#include "Entity.h"

class Camera: public Entity
{
public:

	enum CameraType {
		ORTOGRAPHIC = 0,
		PERSPECTIVE
	};

private:
	Camera::CameraType cameraType;
	unsigned int       uiWidth,
			           uiHeight;
	float              fNearPlane,
		               fFarPlane,
		               fFOV;
	Vector3            vFocalPoint,
		           	   vUpVector;

public:
	Camera( Camera::CameraType = Camera::PERSPECTIVE );
	Camera( const Camera& );
	Camera( Camera* );

	void setViewport( unsigned int, unsigned int );
	void setClippingPlanes( float, float );

	inline float getNearPlane() { return this->fNearPlane; }

	inline float getFarPlane() { return this->fFarPlane; }

	void setFOV( float );

	inline float getFOV() { return this->fFOV; }

	void Yaw( float );
	void Pitch( float );
	void Roll( float );
	void TurnAround_H( float );
	void TurnAround_V( float );

	void LookAt( Vector3 );

	inline Vector3 getFocalPoint() { return this->vFocalPoint; }

	void setUp( Vector3 );

	inline Vector3 getOrientation() { return this->vUpVector; }

	void OnRender();
	void OnLoop( double );
};

#endif
