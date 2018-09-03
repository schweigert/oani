/**
   \file PoseAttr.cpp
   \brief Implementacao dos metodos da classe PoseAttr

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "PoseAttr.h"
#include "Entity.h"

/**
   \brief Construtor para a classe PoseAttr
   \param Value valor do atributo animavel
   \param dAttrTime tempo (em segundos) na timeline para este atributo interpolável
   \param attrName  nome do atributo interpolavel
*/
PoseAttr::PoseAttr( Vector3 Value, double dAttrTime, PoseAttr::AttrName attrName )
{
    this->setValue( Value );
    this->attrName = attrName;
    this->setTime( dAttrTime );
}
/**
   \brief Define o tempo quando este atributo interpolavel ocorre. Valor fornecido em segundos
   \param dAttrTime momento no tempo (em segundos) quando ocorre este atributo interpolavel
*/
void PoseAttr::setTime( double dAttrTime )
{
    this->dAttrTime = dAttrTime;
}
/**
  \brief Atualiza o respectivo parametro interpolavel de um determinado objeto Entity
  \param ptrParent ponteiro para o objeto a ser atualizado
*/
void PoseAttr::updateParent( Entity * ptrParent )
{
    if( !ptrParent )
        return;

    switch( this->attrName )
    {
    case PoseAttr::TRANSLATE: ptrParent->setTranslate( this->Value ); break;
    case PoseAttr::ROTATE:    ptrParent->setRotate( this->Value );    break;
    case PoseAttr::SCALE:     ptrParent->setScale( this->Value );     break;
    }
}
/**
   \brief Atualiza o valor desse atributo interpolavel
   \param Value novo valor desse atributo interpolavel
*/
void PoseAttr::setValue( Vector3 Value )
{
    this->Value = Value;
}
