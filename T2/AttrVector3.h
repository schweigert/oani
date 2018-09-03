/**
   \file AttrVector3.h
   \brief Descricao da classe AttrVector3

   Esta classe tem por objetivo implementar a descri��o de um atribulo interpol�vel para uma anima��o pose-to-pose

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _ATTRVECTOR3_NOT_INCLUDED_
#define _ATTRVECTOR3_NOT_INCLUDED_

#include "PoseAttr.h"
#include "Vector3.h"

class AttrVector3: public PoseAttr
{
private:
    Vector3 Value;

public:
    AttrVector3( double, AttrVector3::AttrName );
    AttrVector3( Vector3, double, AttrVector3::AttrName );
    AttrVector3( AttrVector3* );

    void setValue( Vector3 );

	/**
	\brief Retorna o valor corrente desse atributo anim�vel
	\return valor corrente do atributo
	*/
    inline Vector3 getValue() { return this->Value; }

    void updateParent( Entity * );
};

#endif
