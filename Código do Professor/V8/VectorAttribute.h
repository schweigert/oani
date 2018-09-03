/**
   \file VectorAttribute.h
   \brief Classe que define o tipo de pose a ser armazenado para animacao keyframing como sendo Vector3 

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Setembro, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _VECTOR_ATTRIBUTE_H_
#define _VECTOR_ATTRIBUTE_H_

#include "PoseAttribute.h"

/**
  \class VectorAttribute
  \brief Descricao da classe template para interpolacao de poses
  \sa Pose
*/
class VectorAttribute: public PoseAttribute
{
private:
	Vector3 Value;   ///< valor do atributo interpolavel

public:
	VectorAttribute( string = "", Vector3 = Vector3::ZERO );
	VectorAttribute( const VectorAttribute& );
	VectorAttribute( VectorAttribute * );

	void setValue( Vector3 );
	/**
	  \brief Retorna o valor corrente do atributo interpolavel
	  \return valor do atributo interpolavel
	*/
	inline Vector3 getValue() { return this->Value; }
};

#endif
