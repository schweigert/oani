#ifndef _PIVOT_H_
#define _PIVOT_H_

#include "Entity.h"

/**
  \class Pivot
  \brief Elemento pivot (entidade vazia) responsavel por criar hierarquias de entidades, a fim de produzir coordenadas locais para animacao de objetos todo-parte
*/
class Pivot: public Entity
{
public:
	Pivot();
	Pivot( const Pivot& );
	Pivot( Pivot* );

	virtual void OnLoop( double );
	void OnRender();
};

#endif
