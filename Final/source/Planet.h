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
