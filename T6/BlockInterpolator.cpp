#include <stdio.h>

#include "BlockInterpolator.h"
#include "VectorAttribute.h"
#include "IntAttribute.h"
#include "FloatAttribute.h"
#include "Vector3.h"

#include <math.h>

/**
\brief Construtor padrao para a classe BlockInterpolator
*/
BlockInterpolator::BlockInterpolator() : Interpolator( Interpolator::POLYNOM )
{}


/**
  \brief Efetua o calculo da interpolacao de acordo com o metodo adotado (no caso: interpolacao Block)
  \param fFactor fator de interpolacao a ser usado: 0.0 significa ponto inicial e 1.0 o ponto final, valores fracionarios indicam pontos intermediarios
  \return o valor interpolado em funcao do fator fornecido
*/
PoseAttribute* BlockInterpolator::Interpolate( float t )
{
	switch( this->ptrStart->getType() )
	{
		case PoseAttribute::VECTOR:
		 {
			return new VectorAttribute(ptrStart->getLabel(), (( VectorAttribute* ) this->ptrEnd )->getValue() );
			break;
			}
		case PoseAttribute::INT:
		{
			return new IntAttribute(ptrStart->getLabel(),(( IntAttribute* ) this->ptrEnd )->getValue() );
			break;
			}
		case PoseAttribute::FLOAT:
		{
			return new FloatAttribute(ptrStart->getLabel(), (( FloatAttribute* ) this->ptrEnd )->getValue() );
			break;
		}
	}
	return NULL;
}
/**
  \brief Define o valor para o ponto inicial do intervalo de interpolacao
  \param vec ponto de inicio do intervalo de interpolacao
*/
void BlockInterpolator::setStart( PoseAttribute* vec )
{
	this->ptrStart = vec;
}
/**
  \brief Define o valor para o ponto final do intervalo de interpolacao
  \param vec ponto final do intervalo de interpolacao
*/
void BlockInterpolator::setEnd( PoseAttribute* vec )
{
	this->ptrEnd = vec;
}
