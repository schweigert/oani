#ifndef _BREPMATERIAL_H_
#define _BREPMATERIAL_H_

#include "Vector3.h"
#include <vector>
#include <string>

using namespace std; // biblioteca C++ para estruturas de dados

/**
\class BRepMaterial
\brief Descreve um material associado a um objeto BRep.<br>Um material e um registro contendo informacao pertinentes ao processo de iluminacao das faces de um BRep.
\sa BRep()
*/
class BRepMaterial
{
public:
	string strMaterialID; ///< identificador do nome do material
	Vector3 Ka, ///< constante de iluminacao ambiente
			Kd, ///< constante de iluminacao difusa
			Ks; ///< constante de iluminacao especular
	float   Ns; ///< constante de espalhamento especular
	unsigned int uiTextureID; ///< identificador do mapa de textura associado a este material

	BRepMaterial();
	BRepMaterial( const BRepMaterial& );
};

#endif
