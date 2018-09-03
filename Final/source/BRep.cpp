
#include "BRep.h"
#include "BRepGroup.h"
#include "RigidBody.h"
#include <GL/glu.h>
#include <stdio.h>
#include "string.h"

/**
  \brief Construtor padrao para a classe BRep
  Cria um objeto BRep vazio
  \sa ColoredEntity(), Entity()
*/
BRep::BRep():TexturedEntity()
{
	this->uiDisplayListID = glGenLists( 1 );
	this->bHasDisplayList = false;
}
/**
  \brief Construtor de clonagem para a classe BRep
  Cria uma copia exata de um objeto poligono ja existente
  \param clone Objeto a ser clonado
*/
BRep::BRep( const BRep& clone ):TexturedEntity( clone )
{
	this->Geometry   = clone.Geometry;
	this->mapasUV    = clone.mapasUV;
	this->Normals    = clone.Normals;

	this->bHasDisplayList = clone.bHasDisplayList;

	for( vector<BRepGroup*>::iterator ptrGroup = (( BRep )clone).listOfGroups.begin(); ptrGroup != (( BRep )clone).listOfGroups.end(); ptrGroup++ )
		this->addGroup( new BRepGroup( (* ptrGroup ) ) );

	this->MaterialLibrary = clone.MaterialLibrary;
}
/**
  \brief Construtor de clonagem para a classe BRep
  Cria uma copia exata de um objeto poligono ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
BRep::BRep( BRep* ptrClone ):TexturedEntity( ptrClone )
{
	printf("Clonning BREP ");

	this->Geometry   = ptrClone->Geometry;
	this->mapasUV    = ptrClone->mapasUV;
	this->Normals    = ptrClone->Normals;

	this->bHasDisplayList = ptrClone->bHasDisplayList;

	for( vector<BRepGroup*>::iterator ptrGroup = ptrClone->listOfGroups.begin();
	     ptrGroup != ptrClone->listOfGroups.end(); ptrGroup++ )
		this->addGroup( new BRepGroup( (* ptrGroup ) ) );

	this->MaterialLibrary = ptrClone->MaterialLibrary;

	printf("... sucess\n");
}
/**
   \brief Destrutor para objetos da classe BRep
*/
BRep::~BRep()
{
	glDeleteLists( this->uiDisplayListID, 1 );

	for( vector<BRepGroup*>::iterator ptrGroup = this->listOfGroups.begin(); ptrGroup != this->listOfGroups.end(); ptrGroup++ )
		delete (* ptrGroup );

	for( vector<BRepMaterial*>::iterator ptrMaterial = this->MaterialLibrary.begin(); ptrMaterial != this->MaterialLibrary.end(); ptrMaterial++ )
		delete (* ptrMaterial );
}
/**
  \brief Adiciona um novo vertice ao final da lista de vertices do objeto
  \param newVec novo vertice a ser adicionado a geometria
*/
void BRep::addVertex( Vector3 newVec )
{
	this->Geometry.push_back( newVec );
}
/**
  \brief Modifica um vertice da lista de vertices do objeto
  \param newVec novo vertice que deve substituir o vertice corrente em uma posicao da lista geometria
  \param uiIndex indice do vertice a ser alterado na lista geometria
  \return flag que indica se houve sucesso na operacao
*/
bool BRep::setVertex( Vector3 newVec, unsigned int uiIndex )
{
	if( uiIndex < this->Geometry.size() )
	{
		this->Geometry[uiIndex] = newVec;
		return true;
	}
	return false;
}
/**
  \brief Retorna um dado vertice da geometria do objeto
  \param uiIndex indice do vertice a ser retornado na lista geometria
  \return um vertice da geometria do objeto ou vertice nulo caso indice invalido
*/
Vector3 BRep::getVertex( unsigned int uiIndex )
{
	if( uiIndex < this->Geometry.size() )
		return this->Geometry[uiIndex];
	return Vector3::ZERO;
}
/**
  \brief Adiciona uma nova coordenada de textura ao final da lista de coordenadas de textura do objeto
  \param newVec nova coordenada de textura a ser adicionada a lista de coordenadas de textura
*/
void BRep::addTexCoord( Vector3 newVec )
{
	this->mapasUV.push_back( newVec );
}
/**
  \brief Modifica uma coordenada de textura da lista de coordenadas de textura do objeto
  \param newVec nova coordenada de textura a ser adicionada a lista de coordenadas de textura
  \param uiIndex indice da coordenada de textura a ser alterada na lista de coordenadas de textura
  \return flag que indica se houve sucesso na operacao
*/
bool BRep::setTexCoord( Vector3 newVec, unsigned int uiIndex )
{
	if( uiIndex < this->mapasUV.size() )
	{
		this->mapasUV[uiIndex] = newVec;
		return true;
	}
	return false;
}
/**
  \brief Retorna uma dada coordenada de textura de um vertice do objeto
  \param uiIndex indice do vertice para o qual uma coordenada de textura deve ser retornada
  \return uma coordenada de textura de um vertice do objeto ou vetor nulo caso indice invalido
*/
Vector3 BRep::getTexCoord( unsigned int uiIndex )
{
	if( uiIndex < this->mapasUV.size() )
		return this->mapasUV[uiIndex];
	return Vector3::ZERO;
}
/**
  \brief Adiciona um novo vetor normal ao final da lista de vetores normais do objeto
  \param newVec novo vetor normal a ser adicionado a lista de vetores normais
*/
void BRep::addNormal( Vector3 newVec )
{
	this->Normals.push_back( newVec );
}
/**
  \brief Modifica um vetor normal da lista de vetores normais do objeto
  \param newVec novo vetor normal a ser adicionado a lista de vetores normais
  \param uiIndex indice do vetor normal a ser alterado na lista de vetores normais
  \return flag que indica se houve sucesso na operacao
*/
bool BRep::setNormal( Vector3 newVec, unsigned int uiIndex )
{
	if( uiIndex < this->Normals.size() )
	{
		this->Normals[uiIndex] = newVec;
		return true;
	}
	return false;
}
/**
  \brief Retorna um dada vetor normal de um vertice do objeto
  \param uiIndex indice do vertice para o qual um vetor normal deve ser retornado
  \return um vetor normal de um vertice do objeto ou vetor nulo caso indice invalido
*/
Vector3 BRep::getNormal( unsigned int uiIndex )
{
	if( uiIndex < this->Normals.size() )
		return this->Normals[uiIndex];
	return Vector3::ZERO;
}
/**
  \brief Adiciona uma nova entrada na lista de grupos de objetos poligonais
  \param entry nova entrada a ser adicionada ao objeto.
*/
void BRep::addGroup( BRepGroup* entry )
{
	this->listOfGroups.push_back( entry );
}
/**
  \brief Altera uma entrada na lista de grupos do objeto
  \param entry nova entrada a ser alterada no objeto.
  \param uiIndex posicao na lista de entradas que deve ser alterada
  \return flag que indica se houve sucesso na operacao
*/
bool BRep::setGroup( BRepGroup* entry, unsigned int uiIndex )
{
	if( uiIndex < this->listOfGroups.size() )
	{
		this->listOfGroups[ uiIndex ] = entry;
		return true;
	}
	return false;
}
/**
  \brief Retorna uma dada entrada da lista de grupos do objeto
  \param uiIndex posicao na lista de grupos que deve ser retornada
  \return ponteiro para o grupo correspondente a posicao solicitada ou NULL caso indice seja invalido
*/
BRepGroup* BRep::getGroup( unsigned int uiIndex )
{
	if( uiIndex < this->listOfGroups.size() )
	{
		return this->listOfGroups[uiIndex];
	}
	return NULL;
}
/**
  \brief Carrega uma primitiva grafica BRep a partir de um arquivo em formato wavefront (*.obj).<br>Arquivos wavefront podem ser construidos com a ferramenta Blender3D.
  \param strFileName nome do arquivo a ser carregado
  \return flag que indica sucesso ou nao da operacao
*/
bool BRep::LoadfromFile( string strFileName )
{
	FILE * ptrFileOBJ = fopen( strFileName.c_str(), "rt" );

	printf("Acessando o arquivo: %s ... ", strFileName.c_str());

	if( !ptrFileOBJ )
		return false;

	string strCurrentPath = strFileName.substr( 0, strFileName.find_last_of( "/\\" ) );

	int     flag;                    // armazena o resultado de cada opera�ao de leitura
	char    strMatLibFileName[100];  // armazena o nome do arquivo contendo a biblioteca de materiais
	char    strGroupID[100];         // nome do grupo BRep
	char    strSection[100];         // ID da se�ao sendo lida: g, v, vt, vn, usemtl, s ou f
	char    strCurrentMaterial[100]; // ID do material atualmente selecionado
	Vector3 newVec;                  // armazena os dados dos vetores sendo lidos

	bool bHasGeometrySection = false, ///< indica se a secao de pontos da geometria foi lida
		 bHasNormalsSection = false,  ///< indica se a secao de vetores normais foi lida
		 bHasUVSection = false;       ///< indica se a secao de mapas UV de textura foi lida

	BRepGroup *ptrNewGroup = NULL; // ponteiro para o novo grupo sendo lido

	printf("Aberto...");
	do
	{
		flag = fscanf( ptrFileOBJ, "%s", (char*)&strSection );
		if( flag < 1 ) break;

		if( strcmp( strSection, "mtllib" ) == 0 )
		{
			flag = fscanf( ptrFileOBJ, " %s\n", strMatLibFileName );
			if( flag < 1 ) break;

			if( strCurrentPath.length() > 0 )
				flag = this->LoadMaterialLibrary( strCurrentPath + "/" , strMatLibFileName );
			else
				flag = this->LoadMaterialLibrary( "", strMatLibFileName );
			if( flag < 1 ) break;
		}
		else if( strcmp( strSection, "g" ) == 0 || strcmp( strSection, "o" ) == 0 )
		{
			if( ptrNewGroup )
			{
				this->addGroup( ptrNewGroup );
				bHasGeometrySection = bHasNormalsSection = bHasUVSection = false;
			}

			flag = fscanf( ptrFileOBJ, " %s\n", (char*)&strGroupID );
			if( flag < 1 ) break;

			ptrNewGroup = new BRepGroup( string( strGroupID ) );
		}
		else if( strcmp( strSection, "v" ) == 0 )
		{
			bHasGeometrySection = true;

			flag = fscanf( ptrFileOBJ, " %f %f %f\n", &newVec.x, &newVec.y, &newVec.z );
			if( flag < 1 ) break;

			this->addVertex( newVec );
		}
		else if( strcmp( strSection, "vt" ) == 0 )
		{
			bHasUVSection = true;

			flag = fscanf( ptrFileOBJ, " %f %f\n", &newVec.x, &newVec.y );
			if( flag < 1 ) break;

			this->addTexCoord( newVec );
		}
		else if( strcmp( strSection, "vn" ) == 0 )
		{
			bHasNormalsSection = true;

			flag = fscanf( ptrFileOBJ, " %f %f %f\n", &newVec.x, &newVec.y, &newVec.z );
			if( flag < 1 ) break;

			this->addNormal( newVec );
		}
		else if( strcmp( strSection, "usemtl" ) == 0 )
		{
			flag = fscanf( ptrFileOBJ, " %s\n", strCurrentMaterial );
			if( flag < 1 ) break;
		}
		else if( strcmp( strSection, "s" ) == 0 || strcmp( strSection, "#" ) == 0 ) // n�o esta claro o que a se�ao "s" faz mas aparentemente nao faz falta :-P
		{
			char c;

			do {        // itera para eliminar todo o comentario ate o final da linha
				c = fgetc( ptrFileOBJ );
			} while ( c != '\n' && c != EOF );

			flag = c != EOF;
			if( flag < 1 ) break;
		}
		else if( strcmp( strSection, "f" ) == 0 )
		{
			BRepFace::FaceEntry oFace1, oFace2, oFace3;

			if( bHasGeometrySection )
				if( bHasNormalsSection )
					if( bHasUVSection )
						flag = fscanf( ptrFileOBJ, " %d/%d/%d %d/%d/%d %d/%d/%d\n", &oFace1.v, &oFace1.t, &oFace1.n, &oFace2.v, &oFace2.t, &oFace2.n, &oFace3.v, &oFace3.t, &oFace3.n );
					else
					{
						oFace1.t = oFace2.t = oFace3.t = 0;
						flag = fscanf( ptrFileOBJ, " %d//%d %d//%d %d//%d\n", &oFace1.v, &oFace1.n, &oFace2.v,&oFace2.n, &oFace3.v, &oFace3.n );
					}
			if( flag < 1 ) break;

			BRepFace newFace;
			newFace.setMaterialName( strCurrentMaterial );
			newFace.addEntry( oFace1 );
			newFace.addEntry( oFace2 );
			newFace.addEntry( oFace3 );
			ptrNewGroup->addFace( newFace );
		}
	}
	while( flag );

	// adiciona o ultimo grupo lido, caso exista um
	if( ptrNewGroup )
		this->addGroup( ptrNewGroup );

	fclose( ptrFileOBJ );

	this->GenerateList();

	printf("... Sucesso\n");

	return true;
}
/**
  \brief Carrega uma lista de materiais a partir de um arquivo em formato wavefront material library (*.mtl).<br>Arquivos wavefront podem ser construidos com a ferramenta Blender3D.
  \param strPath caminho do arquivo a ser carregado. Assume que todos os arquivos (*.obj, *.mtl *.bmp e/ou *.tga) estejam nesse mesmo caminho.
  \param strFileName nome do arquivo a ser carregado
  \return flag que indica sucesso ou nao da operacao
*/
bool BRep::LoadMaterialLibrary( string strPath, string strFileName )
{
	FILE * ptrFileMTL = fopen( ( strPath + strFileName ).c_str(), "rt" );

	if( !ptrFileMTL )
		return false;

	int flag;   // armazena o resultado de cada opera�ao de leitura
	float fValue;  // armazena os dados das constantes reais lidas
	char strSection[100];  // ID da se�ao sendo lida: newmtl, Ns, Ka, Kd, Ks, Ni, d, illum ou map_Kd
	char strCurrentMaterial[100];  // ID do material atualmente selecionado
	char strMapFile[100];  // nome do arquivo de textura associado a um material lido
	Vector3 newVec;  // armazena os dados dos vetores sendo lidos

	BRepMaterial *ptrNewMaterial = NULL; // ponteiro para o novo material sendo lido

	do
	{
		flag = fscanf( ptrFileMTL, "%s", (char*)&strSection );
		if( flag < 1 ) break;

		if( strcmp( strSection, "newmtl" ) == 0 )
		{
			// adiciona o ultimo material lido, caso exista um
			if( ptrNewMaterial )
				this->MaterialLibrary.push_back( ptrNewMaterial );

			flag = fscanf( ptrFileMTL, " %s\n", strCurrentMaterial );
			if( flag < 1 ) break;

			ptrNewMaterial = new BRepMaterial();
			ptrNewMaterial->strMaterialID = string( strCurrentMaterial );
		}
		else if( strcmp( strSection, "Ns" ) == 0 )
		{
			flag = fscanf( ptrFileMTL, " %f\n", &fValue );
			if( flag < 1 ) break;
			if( ptrNewMaterial )
				ptrNewMaterial->Ns = fValue;
		}
		else if( strcmp( strSection, "Ka" ) == 0 )
		{
			flag = fscanf( ptrFileMTL, " %f %f %f\n", &newVec.x, &newVec.y, &newVec.z );
			if( flag < 1 ) break;

			if( ptrNewMaterial )
				ptrNewMaterial->Ka = newVec;
		}
		else if( strcmp( strSection, "Kd" ) == 0 )
		{
			flag = fscanf( ptrFileMTL, " %f %f %f\n", &newVec.x, &newVec.y, &newVec.z );
			if( flag < 1 ) break;

			if( ptrNewMaterial )
				ptrNewMaterial->Kd = newVec;
		}
		else if( strcmp( strSection, "Ks" ) == 0 )
		{
			flag = fscanf( ptrFileMTL, " %f %f %f\n", &newVec.x, &newVec.y, &newVec.z );
			if( flag < 1 ) break;

			if( ptrNewMaterial )
				ptrNewMaterial->Ks = newVec;
		}
		else if( strcmp( strSection, "Ni" ) == 0 || strcmp( strSection, "d" ) == 0 || strcmp( strSection, "illum" ) == 0 ) // se�oes que serao desconsideradas
		{
			flag = fscanf( ptrFileMTL, " %f\n", &fValue );
			if( flag < 1 ) break;
		}
		else if( strcmp( strSection, "map_Kd" ) == 0 )
		{
			flag = fscanf( ptrFileMTL, " %s\n", strMapFile );
			if( flag < 1 ) break;

			if( ptrNewMaterial )
				ptrNewMaterial->uiTextureID = this->LoadTexture( strPath + strMapFile );
		}
		else if( strcmp( strSection, "#" ) == 0 )
		{
			char c;

			do {        // itera para eliminar todo o comentario ate o final da linha
				c = fgetc( ptrFileMTL );
			} while ( c != '\n' && c != EOF );

			flag = c != EOF;
			if( flag < 1 ) break;
		}
	}
	while( flag );

	// adiciona o ultimo material lido, caso exista um
	if( ptrNewMaterial )
		this->MaterialLibrary.push_back( ptrNewMaterial );

	fclose( ptrFileMTL );
	return true;
}
/**
\brief Retorna a quantidade de poligonos associada a este objeto
\return tamanho do vetor topologia deste objeto
*/
unsigned int BRep::getPolyCount()
{
	unsigned int uiPolyCount = 0;
	for( vector<BRepGroup*>::iterator ptrGroup = this->listOfGroups.begin(); ptrGroup != this->listOfGroups.end(); ptrGroup++ )
		uiPolyCount += (* ptrGroup )->getSize();
	return uiPolyCount;
}
/**
  \brief Desenha a primitiva atraves de comandos OPENGL
*/
void BRep::OnRender()
{
	glPushMatrix();

	glColor4f( this->vColor.x, this->vColor.y, this->vColor.z, this->vColor.w );

	glTranslatef( this->vTranslate.x, this->vTranslate.y, this->vTranslate.z );
	glRotatef( this->vRotate.x, 1.0f, 0.0f, 0.0f );
	glRotatef( this->vRotate.y, 0.0f, 1.0f, 0.0f );
	glRotatef( this->vRotate.z, 0.0f, 0.0f, 1.0f );
	glScalef( this->vScale.x, this->vScale.y, this->vScale.z );



	if( this->bHasDisplayList )
		glCallList( this->uiDisplayListID );

		if( this->listOfEntities.size() > 0 )
			for( vector<Entity*>::iterator ptrEntity = this->listOfEntities.begin();
				ptrEntity != this->listOfEntities.end(); ptrEntity++ )
				(* ptrEntity )->OnRender();


	glPopMatrix();
}
/**
  \brief Atualiza os parametros da primitiva. Deve ser usado para determinar as configuracoes da primitiva a cada novo frame da animacao
  \param fDeltaTime tempo transcorrido desde a ultima chamada de atualizacao da primitiva
*/
void BRep::GenerateList()
{
	glNewList( this->uiDisplayListID, GL_COMPILE );

	for( vector<BRepGroup*>::iterator ptrGroup = this->listOfGroups.begin(); ptrGroup != this->listOfGroups.end(); ptrGroup++ )
	{
		BRepMaterial * ptrCurrentMaterial = NULL;

		for( unsigned int uiFaceIndex = 0; uiFaceIndex < (* ptrGroup )->getSize(); uiFaceIndex++ )
		{
			BRepFace objFace = (* ptrGroup )->getFace( uiFaceIndex );

			if( !ptrCurrentMaterial || ptrCurrentMaterial->strMaterialID != objFace.getMaterialName() )
				for( vector<BRepMaterial*>::iterator ptrMaterial = this->MaterialLibrary.begin(); ptrMaterial != this->MaterialLibrary.end(); ptrMaterial++ )
					if( (* ptrMaterial )->strMaterialID == objFace.getMaterialName() )
					{
						ptrCurrentMaterial = (* ptrMaterial );
						break;
					}

			if( ptrCurrentMaterial )
			{
				float ambient[4] = { ptrCurrentMaterial->Ka.x, ptrCurrentMaterial->Ka.y, ptrCurrentMaterial->Ka.z, ptrCurrentMaterial->Ka.w };
				glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );

				float diffuse[4] = { ptrCurrentMaterial->Kd.x, ptrCurrentMaterial->Kd.y, ptrCurrentMaterial->Kd.z, ptrCurrentMaterial->Kd.w };
				glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );

				float specular[4] = { ptrCurrentMaterial->Ks.x, ptrCurrentMaterial->Ks.y, ptrCurrentMaterial->Ks.z, ptrCurrentMaterial->Ks.w };
				glMaterialfv( GL_FRONT, GL_SPECULAR, specular );

				glMaterialf( GL_FRONT, GL_SHININESS, ptrCurrentMaterial->Ns );

				if( ptrCurrentMaterial->uiTextureID > 0 )
					glBindTexture( GL_TEXTURE_2D, ptrCurrentMaterial->uiTextureID );
			}

			glBegin( GL_TRIANGLES );
			for( unsigned int idxFaceEntry = 0; idxFaceEntry < objFace.getSize(); idxFaceEntry++ )
			{
				BRepFace::FaceEntry objFaceEntry = objFace.getListOfEntries()[ idxFaceEntry ];

				Vector3 vGeo = this->Geometry[objFaceEntry.v-1], // busca o vertice corrente
						vNormal = this->Normals[objFaceEntry.n-1]; // busca o vetor normal corrente

				if( ptrCurrentMaterial->uiTextureID > 0 )
				{
					Vector3 vTex = this->mapasUV[objFaceEntry.t-1]; // busca a coordenada de textura corrente
					glTexCoord2f( vTex.x, vTex.y );
				}

				glNormal3f( vNormal.x, vNormal.y, vNormal.z );
				glVertex3f( vGeo.x, vGeo.y, vGeo.z );
			}
			glEnd();
		}

	}
	glEndList();
	this->bHasDisplayList = true;
	getDimensionsPD();
}
/**
  \brief Atualiza os parametros da primitiva. Deve ser usado para determinar as configuracoes da primitiva a cada novo frame da animacao
  \param uiDeltaTime tempo transcorrido desde a ultima chamada de atualizacao da primitiva
*/
void BRep::OnLoop( double dDeltaTime )
{
	TexturedEntity::OnLoop( dDeltaTime );
}
/**
\brief Retorna as dimensoes (minimo e maximo) deste objeto
\param minVertex coordenadas do ponto minimo da geometria do objeto
\param maxVertex coordenadas do ponto maximo da geometria do objeto
*/
void BRep::getLimits( Vector3 &minVertex, Vector3 &maxVertex )
{
	maxVertex = Vector3( -9999.0f, -9999.0f, -9999.0f );
	minVertex = maxVertex * -1.0f;

	for( vector<Vector3>::iterator vertex = this->Geometry.begin(); vertex != this->Geometry.end(); vertex++ )
	{
		if( minVertex.x > (* vertex ).x ) minVertex.x = (* vertex ).x;
		if( minVertex.y > (* vertex ).y ) minVertex.y = (* vertex ).y;
		if( minVertex.z > (* vertex ).z ) minVertex.z = (* vertex ).z;
		if( maxVertex.x < (* vertex ).x ) maxVertex.x = (* vertex ).x;
		if( maxVertex.y < (* vertex ).y ) maxVertex.y = (* vertex ).y;
		if( maxVertex.z < (* vertex ).z ) maxVertex.z = (* vertex ).z;
	}
}
/**
   \brief Determina o menor e o maior v�rtice da geometria desse objeto
*/
void BRep::getDimensionsPD()
{
	Vector3 maxVertex, minVertex;

	this->getLimits( minVertex, maxVertex );

	for( vector<Entity*>::iterator ptrChild = this->listOfEntities.begin(); ptrChild != this->listOfEntities.end(); ptrChild++ )
	{
		Vector3 maxChild, minChild;
		(( BRep* )(* ptrChild ))->getLimits( minChild, maxChild );

		if( minVertex.x > minChild.x ) minVertex.x = minChild.x;
		if( minVertex.y > minChild.y ) minVertex.y = minChild.y;
		if( minVertex.z > minChild.z ) minVertex.z = minChild.z;
		if( maxVertex.x < maxChild.x ) maxVertex.x = maxChild.x;
		if( maxVertex.y < maxChild.y ) maxVertex.y = maxChild.y;
		if( maxVertex.z < maxChild.z ) maxVertex.z = maxChild.z;
	}

	this->vDimension = (maxVertex - minVertex)*0.5f;
}

Vector3 BRep::getDimensions(){
	return this->vDimension;
}
