#ifndef _POSE_H_
#define _POSE_H_

#include "PoseAttribute.h"
#include "Vector3.h"
#include <vector>
using namespace std;

/**
  \class Pose
  \brief Descricao de uma pose de uma entidade animavel em um dado instante de tempo
  \sa PoseAttribute
*/
class Pose
{
private:
	vector<PoseAttribute*> listOfPoseAttribs; ///< lista de atributos interpolaveis
	double                 dMomentInTime;    ///< momento no tempo (em milisegundos) quando essa pose deve ocorrer durante a animacao

public:
	Pose();
	Pose( const Pose& );
	Pose( Pose* );

	void setTime( double );
	/**
	  \brief retorna o momento quando essa pose deve ocorrer no tempo
	  \return valor em milisegundos do momento no tempo que essa pose ocorre durante a animacao
	*/
	inline double getTime() { return this->dMomentInTime; }
	/**
	  \brief Retorna o numero de atributos interpolaveis associado a esta pose
	  \return retorna o tamanho do vetor pose
	*/
	inline unsigned int getSize() { return this->listOfPoseAttribs.size(); }

	void addPoseAttribute( PoseAttribute* );
	bool setPoseAttribute( PoseAttribute*, unsigned int );
	PoseAttribute* getPoseAttribute( unsigned int );
	PoseAttribute* getPoseAttribute( string );
	bool hasPoseAttributeName( string );
};

#endif
