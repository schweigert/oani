#ifndef _INTERPOLATOR_H_
#define _INTERPOLATOR_H_

#include "PoseAttribute.h"

/**
   \class Interpolator
   \brief Classe abstrata que agrupa todos os tipos de interpoladores suportados pelo sistema
   \sa LinearInterpolator
*/
class Interpolator
{
public:
	enum InterpolationType
	{
		LINEAR, ///< interpolacao linear
		POLYNOM,///< interpolacao polinomial
		BLOCK
	};

protected:
	InterpolationType ipoType; ///< tipo de interpolacao sendo executada

public:
	/**
	\brief Construtor padrao para a classe Interpolator
	\param ipoType tipo de interpolacao a ser executada
	*/
	Interpolator( Interpolator::InterpolationType ipoType )
	{
		this->ipoType = ipoType;
	}

	virtual PoseAttribute* Interpolate( float ) = 0;
};

#endif
