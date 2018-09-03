#include "BRepGroup.h"
#include <GL/glut.h>

/**
  \brief Construtor para a classe BRep.<br>Cria um objeto BRep vazio.
  \param strGroupID nome identificador do novo grupo
  \sa BRep(), BRepFace(), FaceEntry()
*/
BRepGroup::BRepGroup( string strGroupID )
{
	this->strGroupID = strGroupID;
}
/**
  \brief Construtor de clonagem para a classe BRepGroup.<br>
  Cria uma copia exata de um grupo poligonal ja existente
  \param clone Objeto a ser clonado
  \sa BRep(), BRepFace(), FaceEntry()
*/
BRepGroup::BRepGroup( const BRepGroup& clone )
{
	this->strGroupID = clone.strGroupID;
	this->Topology   = clone.Topology;
}
/**
  \brief Construtor de clonagem para a classe BRepGroup a partir de ponteiro.<br>
  Cria uma copia exata de um grupo poligonal ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
  \sa BRep(), BRepFace(), FaceEntry()
*/
BRepGroup::BRepGroup( BRepGroup* ptrClone )
{
	this->strGroupID = ptrClone->strGroupID;
	this->Topology   = ptrClone->Topology;
}
/**
  \brief Adiciona uma nova face ao final da lista de faces do objeto
  \param newVec nova face a ser adicionada a topologia. Uma face e definida como um vetor de FaceEntry
  \return flag que indica se houve sucesso na operacao
  \sa FaceEntry
*/
bool BRepGroup::addFace( BRepFace newVec )
{
	if( newVec.getSize() > 0 )
	{
		this->Topology.push_back( newVec );
		return true;
	}
	return false;
}
/**
  \brief Modifica uma face da lista de faces do objeto
  \param newVec nova face que deve substituir a face corrente em uma posicao da lista topologia
  \param uiIndex indice da face a ser alterada na lista topologia
  \return flag que indica se houve sucesso na operacao
*/
bool BRepGroup::setFace( BRepFace newVec, unsigned int uiIndex )
{
	if( uiIndex < this->Topology.size() )
	{
		this->Topology[uiIndex] = newVec;
		return true;
	}
	return false;
}
/**
  \brief Retorna uma dada face da topologia do objeto
  \param uiIndex indice da face a ser retornada na lista topologia
  \return uma face da topologia do objeto ou face vazia caso indice invalido
*/
BRepFace BRepGroup::getFace( unsigned int uiIndex )
{
	if( uiIndex < this->Topology.size() )
		return this->Topology[uiIndex];
	return BRepFace();
}
