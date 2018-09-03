#ifndef _FLOAT_ATTRIBUTE_H_
#define _FLOAT_ATTRIBUTE_H_

#include "PoseAttribute.h"

/**
  \class FloatAttribute
  \brief Descricao da classe template para interpolacao de poses
  \sa Pose
*/
class FloatAttribute: public PoseAttribute
{
private:
	float Value;   ///< valor do atributo interpolavel

public:
	FloatAttribute( string = "", float = 0.0f );
	FloatAttribute( const FloatAttribute& );
	FloatAttribute( FloatAttribute * );

	void setValue( float );
	/**
	  \brief Retorna o valor corrente do atributo interpolavel
	  \return valor do atributo interpolavel
	*/
	inline float getValue() { return this->Value; }
};

#endif
