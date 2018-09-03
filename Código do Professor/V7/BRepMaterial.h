/**
   \file BRepMaterial.h
   \brief Descricao da classe de descricao de materiais de objetos.

   Materiais sao registros que armazenam as informacoes pertinentes ao calculo do modelo de iluminacao e shading de objeto poligonais.<br>
   Atualmente as seguintes informacoes sao armazenadas em um material: ID, constante de reflexao da iluminacao ambiente (Ka), constante de 
   reflexao difusa (Kd), constante de reflexao especular (Ks), constante de espalhamento especular (Ns) e nome do arquivo de imagem utilizado 
   pelo mapa UV.

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Agosto, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
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
