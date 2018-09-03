#ifndef _KEYFRAMING_H_
#define _KEYFRAMING_H_

#include "Interpolator.h"
#include "Pose.h"
#include "Vector3.h"
#include <vector>
using namespace std;

/**
  \class Keyframing
  \brief Classe que implementa o processo de animacao baseado em quadros-chave (Keyframing).<br>

  Este processo se utiliza de uma serie de poses posicionadas no tempo e interpoladas gerando-se quadros intermediarios (Principio da Animacao Pose-to-Pose)

  \sa Pose, Interpolator
*/
class Keyframing
{
private:
	vector< Pose* >                           listOfPoses; ///< lista de poses a serem interpoladas
	vector< Interpolator::InterpolationType > listOfIpos;  ///< lista dos tipos de interpolacao entre poses subsequentes
	unsigned int                              uiCurrPose;  ///< armazena o indice da pose sendo processada
	double                                    dAccumTime;  ///< armazena o tempo transcorrido desde o inicio da animacao
	bool                                      bLoop;       ///< flag que indica se a animacao deve ser reiniciada apos a execucao do ultimo frame

public:
	Keyframing( bool = false );
	Keyframing( Keyframing* );
	~Keyframing();

	void setLooping( bool );

	void addPose( Pose*, Interpolator::InterpolationType = Interpolator::LINEAR );
	Pose* getPose( unsigned int );

	Pose* OnLoop( double );
};

#endif
