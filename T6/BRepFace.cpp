#include "BRepFace.h"

// --------------------------------------------- FaceEntry() -------------------------------------------------------
/**
  \brief Construtor para a classe FaceEntry
  Cria um objeto FaceEntry nulo
  \sa BRepFace(), BRepGroup, BRep()
*/
BRepFace::FaceEntry::FaceEntry()
{
	this->n = this->t = this->v = 0;
}
/**
  \brief Construtor de clonagem para a classe FaceEntry
  Cria uma copia exata de uma entrada ja existente
  \param clone Objeto a ser clonado
  \sa BRepFace(), BRepGroup, BRep()
*/
BRepFace::FaceEntry::FaceEntry( const BRepFace::FaceEntry& clone )
{
	this->n = clone.n;
	this->t = clone.t;
	this->v = clone.v;
}
// ---------------------------------------------- BRepFace() -------------------------------------------------------
/**
  \brief Construtor para a classe BRepFace
  Cria um objeto BRepFace nulo
  \sa FaceEntry(), BRepGroup(), BRep()
*/
BRepFace::BRepFace()
{}
/**
  \brief Construtor de clonagem para a classe BRepFace
  Cria uma copia exata de uma face poligonal ja existente
  \param clone Objeto a ser clonado
  \sa FaceEntry(), BRepGroup(), BRep()
*/
BRepFace::BRepFace( const BRepFace& clone )
{
	this->listOfEntries = clone.listOfEntries;
	this->strMaterial = clone.strMaterial;
}
/**
  \brief Adiciona uma nova entrada na lista de entradas de uma face poligonal
  \param entry nova entrada a ser adicionada a face. Uma entrada e composta por tres valores: vertice, textura e normal.
*/
void BRepFace::addEntry( BRepFace::FaceEntry entry )
{
	this->listOfEntries.push_back( entry );
}
/**
  \brief Altera uma entrada na lista de entradas de uma face poligonal
  \param entry nova entrada a ser alterada na face. Uma entrada e composta por tres valores: vertice, textura e normal.
  \param uiIndex posicao na lista de entradas que deve ser alterada
  \return flag que indica se houve sucesso na operacao
*/
bool BRepFace::setEntry( BRepFace::FaceEntry entry, unsigned int uiIndex )
{
	if( uiIndex < this->listOfEntries.size() )
	{
		this->listOfEntries[uiIndex] = entry;
		return true;
	}
	return false;
}
/**
  \brief Retorna uma dada entrada da lista de entradas de uma face poligonal
  \param uiIndex posicao na lista de entradas que deve ser retornada
  \return a entrada correspondente a posicao solicitada ou uma entrada nula caso indice seja invalido
*/
BRepFace::FaceEntry BRepFace::getEntry( unsigned int uiIndex )
{
	if( uiIndex < this->listOfEntries.size() )
	{
		return this->listOfEntries[uiIndex];
	}
	return BRepFace::FaceEntry();
}
/**
   \brief Associa um nome de material com a face, para efeito de renderizacao
   \param strMaterialID identificador do nome do material a ser associado com a face
*/
void BRepFace::setMaterialName( string strMaterialID )
{
	this->strMaterial = strMaterialID;
}
