/**
   \file PivotedBRep.h
   \brief Descricao da classe de gerenciamento de objetos BRep associado a um elemento pivot.

   Elementos Pivot permitem a definicao de hierarquias de objetos, desta forma criando coordenadas locais para fins de animacao de elemento todo-parte.<br>

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Setembro, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
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
