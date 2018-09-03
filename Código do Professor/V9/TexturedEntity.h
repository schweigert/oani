/**
   \file TexturedEntity.h
   \brief Descricao da classe TexturedEntity

   Esta classe representa todos os elementos fisicos da cena que apresentam mapeamento de textura UV<br>

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Agosto, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _TEXTURED_ENTITY_H_
#define _TEXTURED_ENTITY_H_

#include <windows.h>
#include "ColoredEntity.h"
#include <string>
using namespace std;

/**
  \struct TGAFILE
  \brief Estrutura de armazenamento dos dados de um arquivo formato TGA
*/
typedef struct
{
     unsigned char imageTypeCode;
     short int     imageWidth;
     short int     imageHeight;
     unsigned char bitCount;
     unsigned char *imageData;
} TGAFILE;

/**
   \class TexturedEntity
   \brief Classe que tem por objetivo agrupar todos os elementos fisicos com mapeamento de textura na cena. E uma especializacao para a classe ColoredEntity.
   \sa ColoredEntity(), Entity()
*/
class TexturedEntity: public ColoredEntity
{
protected:
     unsigned int uiDisplayListID;  ///< identificador para a display list que engloba os comandos OPENGL dessa entidade

private:
	TGAFILE *myTGA; ///< ponteiro para um arquivo de imagem em formato TGA a ser lido

	unsigned char* LoadBitmapFile( string, BITMAPINFOHEADER * );
	int			   LoadTGAFile( string, TGAFILE * );

public:
	  TexturedEntity();
	  TexturedEntity( const TexturedEntity& );
	  TexturedEntity( TexturedEntity* );

	  unsigned int LoadTexture( string );
	  virtual void OnLoop( double );
};

#endif
