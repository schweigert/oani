
#ifndef _POSE_ATTRIBUTE_H_
#define _POSE_ATTRIBUTE_H_

#include "Vector3.h"
#include <string>
using namespace std;

/**
  \class PoseAttribute
  \brief Descricao da classe template para interpolacao de poses
  \sa Pose
*/
class PoseAttribute
{
public:
	enum PoseAttributeType
	{
		VECTOR = 0, ///< atributo interpolavel do tipo Vector3
		FLOAT,      ///< atributo interpolavel do tipo real
		INT         ///< atributo interpolavel do tipo inteiro
	};

protected:
	PoseAttributeType attrType;  ///< tipo do atributo interpolavel
	string strLabel; ///< nome do atributo interpolavel

public:
	PoseAttribute( PoseAttributeType = PoseAttribute::INT, string = "" );
	PoseAttribute( const PoseAttribute& );
	PoseAttribute( PoseAttribute * );

	void setLabel( string );
	/**
	  \brief Retorna o valor corrente do nome do atributo interpolavel
	  \return valor do nome do atributo interpolavel
	*/
	inline string getLabel() { return this->strLabel; }
	/**
	  \brief Retorna o valor do tipo do atributo interpolavel
	  \return tipo do atributo interpolavel
	*/
	PoseAttributeType getType() { return this->attrType; }
};

#endif
