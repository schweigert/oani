/**
   \file Object.h
   \brief Descricao da classe para objetos graficos compostos de várias primitivas

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _OBJECT_NOT_INCLUDED_
#define _OBJECT_NOT_INCLUDED_

#include "Entity.h"
#include "PrimitiveGL.h"
#include <vector>
using namespace std;

/**
   \class Object
   \brief Responsavel por manipular objetos compostos de multiplas primitivas<br>

   \sa Entity()
*/
class Object: public Entity
{
protected:
	vector<Entity*> listOfEntities;  ///< lista de ponteiros para entidades que compoem este objeto

public:
    Object();
    Object( const Object & );
    Object( Object* );
    ~Object();

    /**
        \brief Rotina responsavel pela construção do objeto
    */
    virtual void Initialize() = 0;

    virtual void OnRender();
    virtual void OnLoop( double );
};

#endif
