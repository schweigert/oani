#include <stdio.h>

#include "PolynomInterpolator.h"
#include "VectorAttribute.h"
#include "IntAttribute.h"
#include "FloatAttribute.h"
#include "Vector3.h"

#include <math.h>

/**
\brief Construtor padrao para a classe PolynomInterpolator
*/
PolynomInterpolator::PolynomInterpolator() : Interpolator( Interpolator::POLYNOM )
{}


float PolynomInterpolator::polyInterpolate (float v1, float v2, float x)
{
	float r = (v2-v1)*(- pow(x, 3) + pow (x, 2) + x) + v1;
	return r;
}

/**
  \brief Efetua o calculo da interpolacao de acordo com o metodo adotado (no caso: interpolacao Polynom)
  \param fFactor fator de interpolacao a ser usado: 0.0 significa ponto inicial e 1.0 o ponto final, valores fracionarios indicam pontos intermediarios
  \return o valor interpolado em funcao do fator fornecido
*/
PoseAttribute* PolynomInterpolator::Interpolate( float t )
{
	switch( this->ptrStart->getType() )
	{
		case PoseAttribute::VECTOR:
		 {
	    float vx1 , vx2;
			float vy1 , vy2;
			float vz1 , vz2;
			float vw1 , vw2;

			vx1 = (( VectorAttribute* ) this->ptrStart )->getValue().x;
			vy1 = (( VectorAttribute* ) this->ptrStart )->getValue().y;
			vz1 = (( VectorAttribute* ) this->ptrStart )->getValue().z;
			vw1 = (( VectorAttribute* ) this->ptrStart )->getValue().w;

			vx2 = (( VectorAttribute* ) this->ptrEnd )->getValue().x;
			vy2 = (( VectorAttribute* ) this->ptrEnd )->getValue().y;
			vz2 = (( VectorAttribute* ) this->ptrEnd )->getValue().z;
			vw2 = (( VectorAttribute* ) this->ptrEnd )->getValue().w;

			float xf = polyInterpolate(vx1, vx2, t);
			float yf = polyInterpolate(vy1, vy2, t);
			float zf = polyInterpolate(vz1, vz2, t);
			float wf = polyInterpolate(vw1, vw2, t);

			return new VectorAttribute( ptrStart->getLabel(), Vector3(xf, yf, zf, wf) );
			break;
		}
		case PoseAttribute::INT:
		{
			int vi1, vi2;

			vi1 = (int)( (( IntAttribute* ) this->ptrStart )->getValue());
			vi2 = (int)( (( IntAttribute* ) this->ptrEnd )->getValue());

			int vif = (int)polyInterpolate((float)vi1, (float)vi2, t);

			return new IntAttribute( ptrStart->getLabel(), vif);
			break;
		}
		case PoseAttribute::FLOAT:
		{
		float vf1, vf2;

		vf1 = (float)(( ( FloatAttribute* ) this->ptrStart )->getValue());
		vf2 = (float)(( ( FloatAttribute* ) this->ptrEnd )->getValue());


		float vff = polyInterpolate(vf1, vf2, t);

		return new FloatAttribute( ptrStart->getLabel(), vff);
		break;
		}
	}
	return NULL;
}
/**
  \brief Define o valor para o ponto inicial do intervalo de interpolacao
  \param vec ponto de inicio do intervalo de interpolacao
*/
void PolynomInterpolator::setStart( PoseAttribute* vec )
{
	this->ptrStart = vec;
}
/**
  \brief Define o valor para o ponto final do intervalo de interpolacao
  \param vec ponto final do intervalo de interpolacao
*/
void PolynomInterpolator::setEnd( PoseAttribute* vec )
{
	this->ptrEnd = vec;
}
