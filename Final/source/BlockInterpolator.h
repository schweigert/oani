#ifndef _Block_INTERPOLATOR_H_
#define _Block_INTERPOLATOR_H_

#include "Interpolator.h"

/**
   \class BlockInterpolator
   \brief Classe especializada que implementa interpolacao Block
*/
class BlockInterpolator: public Interpolator
{
private:
	PoseAttribute * ptrStart, ///< valor inicial do intervalo de interpolacao
				        * ptrEnd;   ///< valor final do intervalo de interpolacao



public:
	BlockInterpolator();

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
