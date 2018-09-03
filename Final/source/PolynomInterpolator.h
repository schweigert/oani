#ifndef _Polynom_INTERPOLATOR_H_
#define _Polynom_INTERPOLATOR_H_

#include "Interpolator.h"

/**
   \class PolynomInterpolator
   \brief Classe especializada que implementa interpolacao Polynom
*/
class PolynomInterpolator: public Interpolator
{
private:
	PoseAttribute * ptrStart, ///< valor inicial do intervalo de interpolacao
				        * ptrEnd;   ///< valor final do intervalo de interpolacao

	float polyInterpolate (float v1, float v2, float t);

public:
	PolynomInterpolator();

	void setStart( PoseAttribute* );
	/**
	  \brief Retorna o valor corrente do inicio do intervalo de interpolacao
	  \return valor do inicio do intervalo de interpolacao
	*/
	inline PoseAttribute* getStart() { return this->ptrStart; }

	void setEnd( PoseAttribute* );
	/**
	  \brief Retorna o valor corrente do final do intervalo de interpolacao
	  \return valor do final do intervalo de interpolacao
	*/
	inline PoseAttribute* getEnd() { return this->ptrEnd; }

	PoseAttribute* Interpolate( float );
};

#endif
