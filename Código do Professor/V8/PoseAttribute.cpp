/**
   \file PoseAttribute.cpp
   \brief Implementacao dos metodos da classe PoseAttribute

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Setembro, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#include "PoseAttribute.h"

/**
\brief Construtor padrao para a classe PoseAttribute
\param attrType tipo do atributo interpolavel
\param strLabelName nome do rotulo do atributo interpolavel
*/
PoseAttribute::PoseAttribute( PoseAttributeType attrType, string strLabelName ) 
{
	this->attrType = attrType;
	this->setLabel( strLabelName );
}
/**
\brief Construtor clonagem padrao para a classe PoseAttribute
\param oClone objeto a ser clonado
*/
PoseAttribute::PoseAttribute( const PoseAttribute& oClone ) 
{
	this->attrType = oClone.attrType;
	this->strLabel = oClone.strLabel;
}
/**
\brief Construtor clonagem para ponteiros da classe PoseAttribute
\param ptrClone ponteiro para um objeto a ser clonado
*/
PoseAttribute::PoseAttribute( PoseAttribute* ptrClone ) 
{
	this->attrType = ptrClone->attrType;
	this->strLabel = ptrClone->strLabel;
}
/**
 \brief Define o valor para o rotulo do atributo interpolavel
 \param strLabelName nome do rotulo do atributo interpolavel
*/
void PoseAttribute::setLabel( string strLabelName )
{
	this->strLabel = strLabelName;
}