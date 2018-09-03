/**
   \file Planet.h
   \brief Descricao da classe que instancia um BRep como um planeta que possui seu proprio pivo (rotacao em relacao a um ponto fixo)

   O pivo de cada planeta permite ser adicionado a uma hierarquia pertencente a um sistema planetario.<br>

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Setembro, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _PLANET_H_
#define _PLANET_H_

#include "PivotedBRep.h"

/**
  \class Planet
  \brief Instancia da classe objeto poligonal associada a um elemento pivot para animacao de um sistema planetario
  \sa PivotBRep(), BRep()
*/
class Planet: public PivotedBRep
{
public:
	Planet();
	Planet( const Planet& );
	Planet( Planet* );
	~Planet();

	void setRotationPeriod( unsigned int, unsigned int );
	void setTranslationPeriod( unsigned int, unsigned int );

	virtual void OnLoop( double );
};

#endif
