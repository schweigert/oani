#include "VectorAttribute.h"

/**
\brief Construtor padrao para a classe VectorAttribute
\param strLabelName nome do rotulo do atributo interpolavel
\param value valor do vetor do atributo interpolavel
*/
VectorAttribute::VectorAttribute( string strLabelName, Vector3 value ) : PoseAttribute( PoseAttribute::VECTOR, strLabelName )
{
	this->setValue( value );
}
/**
\brief Construtor clonagem padrao para a classe VectorAttribute
\param oClone objeto a ser clonado
*/
VectorAttribute::VectorAttribute( const VectorAttribute& oClone )  : PoseAttribute( oClone )
{
	this->Value = oClone.Value;
}
/**
\brief Construtor clonagem para ponteiros da classe VectorAttribute
\param ptrClone ponteiro para um objeto a ser clonado
*/
VectorAttribute::VectorAttribute( VectorAttribute* ptrClone ) : PoseAttribute( ptrClone )
{
	this->Value = ptrClone->Value;
}
/**
 \brief Define o valor para o atributo interpolavel
 \param vecValue valor do vetor do atributo interpolavel
*/
void VectorAttribute::setValue( Vector3 vecValue )
{
	this->Value = vecValue;
}
