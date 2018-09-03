#ifndef _BREP_GROUP_H_
#define _BREP_GROUP_H_

#include "Vector3.h"
#include <vector>
#include <string>
#include "BRepFace.h"
#include "BRepMaterial.h"

using namespace std; // biblioteca C++ para estruturas de dados

/**
\class BRepGroup
\brief Descreve um sub-objeto BRep de forma analoga a um objeto BRep: geometria + mapas UV + vetores normais + topologia
*/
class BRepGroup
{
private:
	string strGroupID;  ///< identificador do nome do grupo
	vector<BRepFace> Topology; ///< lista de faces poligonais que compoem este objeto

public:
	BRepGroup( string = "" );
	BRepGroup( const BRepGroup& );
	BRepGroup( BRepGroup* );

	bool addFace( BRepFace );
	bool setFace( BRepFace, unsigned int );
	BRepFace getFace( unsigned int );
	/**
	\brief Retorna a quantidade de faces associadas a este grupo
	\return quantidade de faces do grupo
	*/
	inline unsigned int getSize() { return this->Topology.size(); }
};

#endif
