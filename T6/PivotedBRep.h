#ifndef _PIVOTED_BREP_H_
#define _PIVOTED_BREP_H_

#include "Pivot.h"
#include <string>
using namespace std;

/**
  \class PivotedBRep
  \brief Classe do tipo objeto poligonal associada a um elemento pivot para animacao em coordenadas locais
  \sa Pivot(), BRep()
*/
class PivotedBRep: public Pivot
{
public:
	PivotedBRep();
	PivotedBRep( const PivotedBRep& );
	PivotedBRep( PivotedBRep* );
	//~PivotedBRep();

	void OnLoad( string );

	virtual void OnLoop( double );
};

#endif
