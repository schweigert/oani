#include "BRepMaterial.h"

/**
  \brief Construtor padrao para objetos da classe BRepMaterial
*/
BRepMaterial::BRepMaterial()
{
	this->Ka = Vector3( 0.2f, 0.2f, 0.2f );
	this->Kd = Vector3::WHITE;
	this->Ks = Vector3::WHITE;
	this->Ns = 10.0f;
	this->uiTextureID = 0;
}
/**
   \brief Construtor de copia para objetos da classe BRepMaterial
   \param clone objeto a ser clonado
*/
BRepMaterial::BRepMaterial( const BRepMaterial& clone )
{
	this->strMaterialID = clone.strMaterialID;
	this->Ka = clone.Ka;
	this->Kd = clone.Kd;
	this->Ks = clone.Ks;
	this->Ns = clone.Ns;
	this->uiTextureID = clone.uiTextureID;
}
