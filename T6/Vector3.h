#ifndef _VECTOR3_H_
#define _VECTOR3_H_

/**
   \class Vector3
   \brief Classe que implementa um vetor no espaco 3D e todas as operacoes realizaveis
   sobre eles.
*/
class Vector3
{
public:
       float x, ///< ordenada do vetor
	   		 y, ///< abcissa do vetor
			 z, ///< cota do vetor
			 w; ///< coordenada de normalizacao

	   static const Vector3 ZERO;
	   static const Vector3 UNIT_X;
	   static const Vector3 UNIT_Y;
	   static const Vector3 UNIT_Z;
     static const Vector3 UNIT;

	   static const Vector3 BLACK;
	   static const Vector3 RED;
	   static const Vector3 GREEN;
	   static const Vector3 BLUE;
	   static const Vector3 YELLOW;
	   static const Vector3 MAGENTA;
	   static const Vector3 CYAN;
	   static const Vector3 WHITE;

       Vector3( float = 0.0f, float = 0.0f, float = 0.0f, float = 0.0f );
       Vector3( const Vector3& );

       float   Length();
       void    Normalize();
       void    Resize( float );
       float   DotProduct( Vector3 );
       Vector3 CrossProduct( Vector3 );

       Vector3 operator + ( Vector3 );
       Vector3 operator - ( Vector3 );
       Vector3 operator * ( Vector3 ); // produto vetorial
       Vector3 operator * ( float );   // escala
	   Vector3 operator = ( Vector3 );
};

#endif
