#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Entity.h"

/**
   \class Camera
   \brief Responsavel por manipular a camera virtual (tanto ortografica quanto perspectiva) do OPENGL.<br>

   Permite movimentos de camera em angulos Euler: roll, pitch e yaw, bem como movimentos em torno de um ponto de interesse.

   \sa Entity()
*/
class Camera: public Entity
{
public:
	/**
	\brief Lista de possiveis tipos de cameras suportados
	*/
	enum CameraType {
		ORTOGRAPHIC = 0, ///< camera ortografica produz projecao paralela dos objetos
		PERSPECTIVE      ///< camera perspectiva produz projecao frustum dos objetos (ponto de fuga)
	};

private:
	bool boolLookAt;
	Camera::CameraType cameraType;   ///< tipo corrente da camera
	unsigned int       uiWidth,      ///< largura da viewport corrente
			           uiHeight;     ///< altura da viewport corrente
	float              fNearPlane,   ///< plano de corte inicial (distancia minima de visualizacao)
		               fFarPlane,    ///< plano de corte maximo (distancia maxima de visualizacao)
		               fFOV;         ///< angulo do campo visual da camera perspectiva (<i>Field of View</i>)
	Vector3            vFocalPoint,  ///< ponto focal da camera que e o ponto para onde a camera esta "olhando"
			           vUpVector;    ///< indica a orientacao da camera, ou seja, a parte de cima


  Entity* entLookAt;

public:
	Camera( Camera::CameraType = Camera::PERSPECTIVE, bool = false );
	Camera( const Camera& );
	Camera( Camera* );

	void setViewport( unsigned int, unsigned int );
	void setClippingPlanes( float, float );
	/**
	\brief Retorna o valor corrente do plano de corte inicial da camera.
	\return distancia minima de visualizacao da camera
	*/
	inline float getNearPlane() { return this->fNearPlane; }
	/**
	\brief Retorna o valor corrente do plano de corte maximo da camera.
	\return distancia maxima de visualizacao da camera
	*/
	inline float getFarPlane() { return this->fFarPlane; }

	void setFOV( float );
	/**
	\brief Retorna o valor corrente do campo visual da camera. Usado apenas para camera do tipo PERSPECTIVA
	\return angulo do campo visual
	*/
	inline float getFOV() { return this->fFOV; }

	void Yaw( float );
	void Pitch( float );
	void Roll( float );
	void TurnAround_H( float );
	void TurnAround_V( float );

	void LookAt( Vector3 );
	void LookAt( Entity* );
	/**
	\brief Retorna o valor corrente do ponto focal da camera.
	\return Ponto de interesse para o qual a camera esta apontando
	*/
	inline Vector3 getFocalPoint() { return this->vFocalPoint; }

	void setUp( Vector3 );
	/**
	\brief Retorna o valor corrente do vetor orientacao da camera.
	\return direcao da orientacao da camera (parte superior)
	*/
	inline Vector3 getOrientation() { return this->vUpVector; }

	void OnRender();
	void OnLoop( double );
};

#endif
