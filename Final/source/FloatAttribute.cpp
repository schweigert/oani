#include "FloatAttribute.h"

/**
\brief Construtor padrao para a classe FloatAttribute
\param strLabelName nome do rotulo do atributo interpolavel
\param value valor real do atributo interpolavel
*/
FloatAttribute::FloatAttribute( string strLabelName, float value ) : PoseAttribute( PoseAttribute::FLOAT, strLabelName )
{
	this->setValue( value );
}
/**
\brief Construtor clonagem padrao para a classe FloatAttribute
\param oClone objeto a ser clonado
*/
FloatAttribute::FloatAttribute( const FloatAttribute& oClone )  : PoseAttribute( oClone )
{
	this->Value = oClone.Value;
}
/**
\brief Construtor clonagem para ponteiros da classe FloatAttribute
\param ptrClone ponteiro para um objeto a ser clonado
*/
FloatAttribute::FloatAttribute( FloatAttribute* ptrClone ) : PoseAttribute( ptrClone )
{
	this->Value = ptrClone->Value;
}
/**
 \brief Define o valor para o atributo interpolavel
 \param fValue valor do atributo interpolavel
*/
void FloatAttribute::setValue( float fValue )
{
	this->Value = fValue;
}
