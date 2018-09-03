#ifndef _BREP_FACE_H_

#define _BREP_FACE_H_

#include <vector>
#include <string>
using namespace std;

/**
\class BRepFace
\brief Descreve um poligono de um objeto BRep como uma lista de entradas do tipo FaceEntry
\sa FaceEntry()
*/
class BRepFace
{
public:
	/**
	\class FaceEntry
	\brief Descreve uma entrada de um poligono de um objeto BRep. Cada entrada e definida por tres indices: coordenada geometrica, coordenada de textura e vetor normal.
	*/
	class FaceEntry
	{
	public:
		unsigned int v, ///< indice do vertice na lista geometria
 					 n, ///< indice do vetor normal associado a este vertice
					 t; ///< indice da coordenada de textura associada a este vertice

		FaceEntry();
		FaceEntry( const FaceEntry& );
	};

private:
	vector<BRepFace::FaceEntry> listOfEntries; ///< lista de entradas que descrevem uma face poligonal
	string strMaterial; ///< nome do material a ser utilizado para renderizar esta face

public:
	BRepFace();
	BRepFace( const BRepFace& );

	void addEntry( BRepFace::FaceEntry );
	bool setEntry( BRepFace::FaceEntry, unsigned int );
	BRepFace::FaceEntry getEntry( unsigned int );

	/**
	\brief Retorna a lista de entradas que compoem esta face
	\return lista de entradas da face
	*/
	inline vector<BRepFace::FaceEntry> getListOfEntries() { return this->listOfEntries; }
	/**
	\brief Retorna o tamanho da lista de entradas que compoem esta face
	\return numero de entradas da face
	*/
	inline unsigned int getSize() { return this->listOfEntries.size(); }

	void setMaterialName( string );
	/**
	\brief Retorna o nome do material associado a esta face
	\return string contendo o identificador do material na biblioteca de materiais a ser utilizado para renderizar esta face
	*/
	inline string getMaterialName() { return this->strMaterial; }
};

#endif
