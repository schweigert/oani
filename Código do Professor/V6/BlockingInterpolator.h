/**
   \file BlockingInterpolator.h
   \brief Descricao da classe BlockingInterpolator

   Esta classe tem por objetivo implementar uma interpola�ao Blocking entre atributos fornecidos

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Abril, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _BLOCKINGINTERPOLATOR_NOT_INCLUDED_
#define _BLOCKINGINTERPOLATOR_NOT_INCLUDED_

#include "Interpolator.h"

class BlockingInterpolator : public Interpolator
{
protected:
    double dPrecision; ///< precisao do calculo da interpola��o

public:
    BlockingInterpolator();
    BlockingInterpolator( const BlockingInterpolator & );
    BlockingInterpolator( BlockingInterpolator* );

    void setPrecision( double );
    void OnLoop( double );
};

#endif
