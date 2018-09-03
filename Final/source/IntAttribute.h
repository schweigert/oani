#ifndef _INT_ATTRIBUTE_H_
#define _INT_ATTRIBUTE_H_

#include "PoseAttribute.h"

/**
  \class IntAttribute
  \brief Descricao da classe template para interpolacao de poses
  \sa Pose
*/
class IntAttribute: public PoseAttribute
{
private:
	int Value;   ///< valor do atributo interpolavel

public:
	IntAttribute( string = "", int = 0 );
	IntAttribute( const IntAttribute& );
	IntAttribute( IntAttribute * );

	void setValue( int );
	/**
	  \brief Retorna o valor corrente do atributo interpolavel
	  \return valor do atributo interpolavel
	*/
	inline int getValue() { return this->Value; }
};

#endif
