#ifndef _BREP_H_
#define _BREP_H_

#include "TexturedEntity.h"
#include "BRepGroup.h"
#include "BRepMaterial.h"
#include <vector>
#include <string>

using namespace std; // biblioteca C++ para estruturas de dados

/**
   \class BRep
   \brief Classe que representa um objeto composto por uma lista de grupos de malhas poligonais como um objeto geometrico espacial. E uma especializacao de uma entidade fisica.
   \sa TexturedEntity(), Entity()
*/
class BRep: public TexturedEntity
{
private:
	bool                  bHasDisplayList; ///< flag que indica se a display list de comandos OPENGL ja foi criada com sucesso

	vector<Vector3>       Geometry;        ///< lista de vertices que descrevem os limites fisicos de um objeto poligonal
	vector<Vector3>       mapasUV;         ///< descreve as coordenadas UV associadas a cada vertice do objeto
	vector<Vector3>       Normals;         ///< descreve os vetores normais associados a cada vertice do objeto

	vector<BRepGroup*>    listOfGroups;    ///< lista de grupos de BReps que compoem este objeto
	vector<BRepMaterial*> MaterialLibrary; ///< lista de materiais associados com este objeto

	bool LoadMaterialLibrary( string, string );
	void GenerateList();

	Vector3 vDimension;

public:
	BRep();
	BRep( const BRep& );
	BRep( BRep* );
	~BRep();

	void addVertex( Vector3 );
	bool setVertex( Vector3, unsigned int );
	Vector3 getVertex( unsigned int );
	/**
	\brief Retorna a quantidade de vertices do objeto
	\return o tamanho do vetor geometria associado a este objeto
	*/
	inline unsigned int getGeometrySize() { return this->Geometry.size(); }
	void getLimits( Vector3&, Vector3& );
	Vector3 getDimensions();
	void getDimensionsPD();

	unsigned int getPolyCount();

	void addTexCoord( Vector3 );
	bool setTexCoord( Vector3, unsigned int );
	Vector3 getTexCoord( unsigned int );

	void addNormal( Vector3 );
	bool setNormal( Vector3, unsigned int );
	Vector3 getNormal( unsigned int );

	void addGroup( BRepGroup* );
	bool setGroup( BRepGroup*, unsigned int );
	BRepGroup* getGroup( unsigned int );

	void OnLoop( double );
	void OnRender();

	bool LoadfromFile( string );
};

#endif
