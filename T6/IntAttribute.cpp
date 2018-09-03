#include "IntAttribute.h"

/**
\brief Construtor padrao para a classe IntAttribute
\param strLabelName nome do rotulo do atributo interpolavel
\param value valor inteiro do atributo interpolavel
*/
IntAttribute::IntAttribute( string strLabelName, int value ) : PoseAttribute( PoseAttribute::INT, strLabelName )
{
	this->setValue( value );
}
/**
\brief Construtor clonagem padrao para a classe IntAttribute
\param oClone objeto a ser clonado
*/
IntAttribute::IntAttribute( const IntAttribute& oClone )  : PoseAttribute( oClone )
{
	this->Value = oClone.Value;
}
/**
\brief Construtor clonagem para ponteiros da classe IntAttribute
\param ptrClone ponteiro para um objeto a ser clonado
*/
IntAttribute::IntAttribute( IntAttribute* ptrClone ) : PoseAttribute( ptrClone )
{
	this->Value = ptrClone->Value;
}
/**
 \brief Define o valor para o atributo interpolavel
 \param iValue valor do atributo interpolavel
*/
void IntAttribute::setValue( int iValue )
{
	this->Value = iValue;
}
