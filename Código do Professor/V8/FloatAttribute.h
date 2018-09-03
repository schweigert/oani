/**
   \file FloatAttribute.h
   \brief Classe que define o tipo de pose a ser armazenado para animacao keyframing como sendo inteiro 

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Setembro, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
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
