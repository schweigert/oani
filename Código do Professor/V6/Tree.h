/**
   \file Tree.h
   \brief Descreve o modelo para uma arvore

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _TREE_NOT_INCLUDED_
#define _TREE_NOT_INCLUDED_

#include "Object.h"

/**
   \class Tree
   \brief Responsavel por construir um objeto do tipo arvore<br>

   \sa Object()
*/
class Tree: public Object
{
public:
    Tree();
    Tree( const Tree & );
    Tree( Tree* );

    virtual void Initialize();
};

#endif

