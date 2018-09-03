#ifndef _TEXTURED_ENTITY_H_
#define _TEXTURED_ENTITY_H_

// #include <windows.h>
#include "ColoredEntity.h"
#include <string>

#include <stdio.h>
#include <stdlib.h>



// for Linux platform, plz make sure the size of data type is correct for BMP spec.
// if you use this on Windows or other platforms, plz pay attention to this.
typedef int LONG;
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned short WORD;

// __attribute__((packed)) on non-Intel arch may cause some unexpected error, plz be informed.

typedef struct tagBITMAPFILEHEADER
{
    WORD    bfType; // 2  /* Magic identifier */
    DWORD   bfSize; // 4  /* File size in bytes */
    WORD    bfReserved1; // 2
    WORD    bfReserved2; // 2
    DWORD   bfOffBits; // 4 /* Offset to image data, bytes */
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    DWORD    biSize; // 4 /* Header size in bytes */
    LONG     biWidth; // 4 /* Width of image */
    LONG     biHeight; // 4 /* Height of image */
    WORD     biPlanes; // 2 /* Number of colour planes */
    WORD     biBitCount; // 2 /* Bits per pixel */
    DWORD    biCompress; // 4 /* Compression type */
    DWORD    biSizeImage; // 4 /* Image size in bytes */
    LONG     biXPelsPerMeter; // 4
    LONG     biYPelsPerMeter; // 4 /* Pixels per meter */
    DWORD    biClrUsed; // 4 /* Number of colours */
    DWORD    biClrImportant; // 4 /* Important colours */
} __attribute__((packed)) BITMAPINFOHEADER;

/*
typedef struct tagRGBQUAD
{
    unsigned char    rgbBlue;
    unsigned char    rgbGreen;
    unsigned char    rgbRed;
    unsigned char    rgbReserved;
} RGBQUAD;
* for biBitCount is 16/24/32, it may be useless
*/

typedef struct
{
        BYTE    b;
        BYTE    g;
        BYTE    r;
} RGB_data; // RGB TYPE, plz also make sure the order


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
