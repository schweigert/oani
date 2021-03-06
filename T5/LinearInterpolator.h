/**
   \file LinearInterpolator.h
   \brief Especializacao da classe de interpoladores para o tipo linear

   Interpolacao linear segue a forma PT = START * (1 - factor) + END * factor<br>

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Setembro, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _LINEAR_INTERPOLATOR_H_
#define _LINEAR_INTERPOLATOR_H_

#include "Interpolator.h"

/**
   \class LinearInterpolator
   \brief Classe especializada que implementa interpolacao linear
*/
class LinearInterpolator: public Interpolator
{
private:
	PoseAttribute * ptrStart, ///< valor inicial do intervalo de interpolacao
				  * ptrEnd;   ///< valor final do intervalo de interpolacao

public:
	LinearInterpolator();

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
