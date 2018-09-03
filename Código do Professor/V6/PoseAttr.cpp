/**
   \file PoseAttr.cpp
   \brief Implementacao dos metodos da classe PoseAttr

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Mar�o, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "PoseAttr.h"
#include "Entity.h"

/**
   \brief Construtor para a classe PoseAttr
   \param dAttrTime tempo (em segundos) na timeline para este atributo interpol�vel
   \param attrName  nome do atributo interpolavel
*/
PoseAttr::PoseAttr( double dAttrTime, PoseAttr::AttrName attrName )
{
    this->attrName = attrName;
    this->setTime( dAttrTime );
}
/**
  \brief Copy-constructor para a classe PoseAttr baseado em ponteiros
  \param ptrClone ponteiro para o objeto a ser clonado
*/
PoseAttr::PoseAttr( PoseAttr * ptrClone )
{
    this->attrName = ptrClone->attrName;
    this->setTime( ptrClone->dAttrTime );
}
/**
   \brief Define o tempo quando este atributo interpolavel ocorre. Valor fornecido em segundos
   \param dAttrTime momento no tempo (em segundos) quando ocorre este atributo interpolavel
*/
void PoseAttr::setTime( double dAttrTime )
{
    this->dAttrTime = dAttrTime;
}
