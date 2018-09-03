#include "TexturedEntity.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

////// Defines
#define BITMAP_ID 0x4D42		// the universal bitmap ID

/**
  \brief Construtor para a classe TexturedEntity.<br>
  Cria um objeto vazio sem textura
*/
TexturedEntity::TexturedEntity():ColoredEntity()
{
	this->uiDisplayListID = 0;
}
/**
  \brief Construtor de clonagem para a classe TexturedEntity.<br>
  Cria uma copia exata de um objeto entidade fisica texturizada ja existente
  \param clone Objeto a ser clonado
*/
TexturedEntity::TexturedEntity( const TexturedEntity& clone ): ColoredEntity( clone )
{
	this->uiDisplayListID = clone.uiDisplayListID;
}
/**
  \brief Construtor de clonagem para a classe TexturedEntity a partir de ponteiros.<br>
  Cria uma copia exata de um objeto entidade fisica texturizada ja existente
  \param ptrClone Ponteiro para o objeto a ser clonado
*/
TexturedEntity::TexturedEntity( TexturedEntity* ptrClone ): ColoredEntity( ptrClone )
{
	this->uiDisplayListID = ptrClone->uiDisplayListID;
}
/**
  \brief Carrega um mapa de textura para a memoria a partir de um arquivo de imagem em formato suportado.<br>Atualmente apenas os formatos BMP e TGA sao suportados.
  \param strFileName nome do arquivo de imagem a ser carregado
  \return identificador do mapa de textura lido
*/
unsigned int TexturedEntity::LoadTexture( string strFileName )
{
	unsigned int uiTextureID = 0; // identificador do mapa de textura lido

	string strExtension = strFileName.substr( strFileName.find_last_of( "." ) + 1 );

	if( strcasecmp( strExtension.c_str(), "bmp" ) == 0 )
	{
		BITMAPINFOHEADER	bitmapInfoHeader;	// bitmap info header
		unsigned char*		bitmapData;		// the bitmap data

		bitmapData = this->LoadBitmapFile( strFileName, &bitmapInfoHeader );

		if( bitmapData )
		{
			glGenTextures( 1, &uiTextureID );
			glBindTexture( GL_TEXTURE_2D, uiTextureID );
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, bitmapData );

			free( bitmapData );
		}
	}
	else if( strcasecmp( strExtension.c_str(), "tga" ) == 0 )
	{
		myTGA = (TGAFILE*)malloc( sizeof(TGAFILE) );

		this->LoadTGAFile( strFileName, myTGA );

		if( myTGA )
		{
			glGenTextures( 1, &uiTextureID );
			glBindTexture( GL_TEXTURE_2D, uiTextureID );
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myTGA->imageWidth, myTGA->imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myTGA->imageData);
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, myTGA->imageWidth, myTGA->imageHeight, GL_RGB, GL_UNSIGNED_BYTE, myTGA->imageData );

			free( myTGA );
		}
	}

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );

	return uiTextureID;
}
/**
   \brief Returns a pointer to the bitmap image of the bitmap specified by filename. Also returns the bitmap header information. No support for 8-bit bitmaps.<br>
   Esta rotina foi retirada do livro "OPENGL Game Programming" de Kevin Hawkings & Dave Astle, Editora Prima Tech (2001).
   \param strFileName nome do arquivo de textura a ser carregado
   \param bitmapInfoHeader ponteiro para o cabecalho de um arquivo bitmap contendo informacoes gerais sobre o arquivo lido
   \return matriz de bytes lidos
*/
unsigned char * TexturedEntity::LoadBitmapFile( string strFileName, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;								// the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	unsigned int		imageIdx = 0;			// image index counter
	unsigned char		tempRGB;				// swap variable

	// open filename in "read binary" mode
	filePtr = fopen( strFileName.c_str(), "rb" );
	if ( filePtr == NULL )
		return NULL;

	size_t lixo;

	// read the bitmap file header
	lixo = fread( &bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr );

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	lixo = fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	lixo = fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
}
/**
   \brief loads the TGA file "filename" into the tgaFile data structure.<br>
   Esta rotina foi retirada do livro "OPENGL Game Programming" de Kevin Hawkings & Dave Astle, Editora Prima Tech (2001).
   \param strFileName nome do arquivo de textura a ser carregado
   \param tgaFile ponteiro para o arquivo TGA contendo informacoes gerais sobre o arquivo lido
   \return flag que indica sucesso ou nao da operacao
*/
int TexturedEntity::LoadTGAFile( string strFileName, TGAFILE *tgaFile )
{
	FILE *filePtr;
	unsigned char ucharBad;		// garbage unsigned char data
	short int	  sintBad;		// garbage short int data
	long		  imageSize;		// size of the TGA image
	int			  colorMode;	// 4 for RGBA or 3 for RGB
	long		  imageIdx;		// counter variable
	unsigned char colorSwap;		// swap variable

	// open the TGA file
	filePtr = fopen(strFileName.c_str(), "rb");
	if (!filePtr)
		return 0;

	size_t lixo;

	// read first two bytes of garbage
	lixo = fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	lixo = fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// read in the image type
	lixo = fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

	// for our purposes, the image type should be either a 2 (color) or a 3 (greyscale)
	if ((tgaFile->imageTypeCode != 2) && (tgaFile->imageTypeCode != 3))
	{
		fclose(filePtr);
		return 0;
	}

	// read 13 bytes of garbage data
	lixo = fread(&sintBad, sizeof(short int), 1, filePtr);
	lixo = fread(&sintBad, sizeof(short int), 1, filePtr);
	lixo = fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	lixo = fread(&sintBad, sizeof(short int), 1, filePtr);
	lixo = fread(&sintBad, sizeof(short int), 1, filePtr);

	// read image dimensions
	lixo = fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
	lixo = fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

	// read image bit depth
	lixo = fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

	// read 1 byte of garbage data
	lixo = fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	// colorMode -> 3 = BGR, 4 = BGRA
	colorMode = tgaFile->bitCount / 8;
	imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

	// allocate memory for image data
	tgaFile->imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

	// read in image data
	lixo = fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

	// change BGR to RGB so OpenGL can read the image data
	for (imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = tgaFile->imageData[imageIdx];
		tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
		tgaFile->imageData[imageIdx + 2] = colorSwap;
	}

	// close the file
	fclose(filePtr);

	return 1;
}
/**
	\brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
	Esta rotina deve ser sobrecarregada para cada tipo de entidade em particular.
*/
void TexturedEntity::OnLoop( double dDeltaTime )
{
	ColoredEntity::OnLoop( dDeltaTime );
}
