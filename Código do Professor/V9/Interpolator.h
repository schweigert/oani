/**
   \file Interpolator.h
   \brief Descricao da classe abstrata de interpoladores

   Esta classe tem por objetivo agrupar todos os tipos de interpoladores suportados pela ferramenta<br>

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Setembro, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
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
	typedef enum InterpolationType 
	{ 
		LINEAR ///< interpolacao linear 
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