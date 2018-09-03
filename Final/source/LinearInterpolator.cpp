#include <stdio.h>

#include "LinearInterpolator.h"
#include "VectorAttribute.h"
#include "IntAttribute.h"
#include "FloatAttribute.h"


/**
\brief Construtor padrao para a classe LinearInterpolator
*/
LinearInterpolator::LinearInterpolator() : Interpolator( Interpolator::LINEAR )
{}
/**
  \brief Efetua o calculo da interpolacao de acordo com o metodo adotado (no caso: interpolacao linear)
  \param fFactor fator de interpolacao a ser usado: 0.0 significa ponto inicial e 1.0 o ponto final, valores fracionarios indicam pontos intermediarios
  \return o valor interpolado em funcao do fator fornecido
*/
PoseAttribute* LinearInterpolator::Interpolate( float fFactor )
{
	switch( this->ptrStart->getType() )
	{
	case PoseAttribute::VECTOR:
		return new VectorAttribute( ptrStart->getLabel(), (( VectorAttribute* ) this->ptrStart )->getValue() * ( 1.0f - fFactor ) + (( VectorAttribute* ) this->ptrEnd )->getValue() * fFactor );
		break;

	case PoseAttribute::INT:
		return new IntAttribute( ptrStart->getLabel(), int( (( IntAttribute* ) this->ptrStart )->getValue() * ( 1.0f - fFactor ) + (( IntAttribute* ) this->ptrEnd )->getValue() * fFactor ) );
		break;

	case PoseAttribute::FLOAT:
		return new FloatAttribute( ptrStart->getLabel(), (( FloatAttribute* ) this->ptrStart )->getValue() * ( 1.0f - fFactor ) + (( FloatAttribute* ) this->ptrEnd )->getValue() * fFactor );
		break;
	}
	return NULL;
}
/**
  \brief Define o valor para o ponto inicial do intervalo de interpolacao
  \param vec ponto de inicio do intervalo de interpolacao
*/
void LinearInterpolator::setStart( PoseAttribute* vec )
{
	this->ptrStart = vec;
}
/**
  \brief Define o valor para o ponto final do intervalo de interpolacao
  \param vec ponto final do intervalo de interpolacao
*/
void LinearInterpolator::setEnd( PoseAttribute* vec )
{
	this->ptrEnd = vec;
}
