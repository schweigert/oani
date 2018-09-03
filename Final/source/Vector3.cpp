#include "Vector3.h"
#include <math.h>

// ------------------------- CONSTANTES ---------------------------------------

const Vector3 Vector3::ZERO   = Vector3();
const Vector3 Vector3::UNIT_X = Vector3( 1.0f, 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::UNIT_Y = Vector3( 0.0f, 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::UNIT_Z = Vector3( 0.0f, 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::UNIT   = Vector3( 1.0f, 1.0f, 1.0f, 0.0f );

// formato RGBA
const Vector3 Vector3::BLACK   = Vector3( 0.0f, 0.0f, 0.0f, 1.0f );
const Vector3 Vector3::RED     = Vector3( 1.0f, 0.0f, 0.0f, 1.0f );
const Vector3 Vector3::YELLOW  = Vector3( 1.0f, 1.0f, 0.0f, 1.0f );
const Vector3 Vector3::GREEN   = Vector3( 0.0f, 1.0f, 0.0f, 1.0f );
const Vector3 Vector3::CYAN    = Vector3( 0.0f, 1.0f, 1.0f, 1.0f );
const Vector3 Vector3::BLUE    = Vector3( 0.0f, 0.0f, 1.0f, 1.0f );
const Vector3 Vector3::MAGENTA = Vector3( 1.0f, 0.0f, 1.0f, 1.0f );
const Vector3 Vector3::WHITE   = Vector3( 1.0f, 1.0f, 1.0f, 1.0f );


/**
  \brief Construtor para a classe Vector3
  Considera a origem dos eixos como origem do vetor.
  \param X ordenada do ponto limitrofe do vetor
  \param Y absissa do ponto limitrofe do vetor
  \param Z cota do ponto limitrofe do vetor
  \param W coordenada de normalizacao do vetor
*/
Vector3::Vector3( float X, float Y, float  Z, float W )
{
    this->x = X;
    this->y = Y;
    this->z = Z;
	this->w = W;
}
// --------------------------------------------------------------------
/**
  \brief Construtor de clonagem para a classe Vector3
  Cria uma copia exata de um objeto vetor ja existente.
  \param clone Objeto a ser clonado
*/
Vector3::Vector3( const Vector3& clone )
{
    this->x = clone.x;
    this->y = clone.y;
    this->z = clone.z;
	this->w = clone.w;
}
// --------------------------------------------------------------------
/**
  \brief Determina o comprimento do vetor
  \return float o comprimento do vetor
*/
float Vector3::Length()
{
   return (float)sqrt( x*x + y*y + z*z );
}
// --------------------------------------------------------------------
/**
  \brief Determina o vetor canonico equivalente na direcao do vetor
*/
void Vector3::Normalize()
{
     float fLength = this->Length(); ///< comprimento do vetor
     this->x /= fLength;
     this->y /= fLength;
     this->z /= fLength;
}
// --------------------------------------------------------------------
/**
  \brief Redimensiona o comprimento de um vetor por um dado fator
  \param fFactor fator de redimensionamento do comprimento do vetor
*/
void Vector3::Resize( float fFactor )
{
     this->x *= fFactor;
     this->y *= fFactor;
     this->z *= fFactor;
}
// --------------------------------------------------------------------
/**
  \brief Determina o produto escalar com outro vetor dado
  \param v3Vect vetor com o qual determinar o produto escalar
  \return float o produto escalar resultante
*/
float Vector3::DotProduct( Vector3 v3Vect )
{
    return this->x * v3Vect.x + this->y * v3Vect.y + this->z * v3Vect.z;
}
// --------------------------------------------------------------------
/**
  \brief Determina o produto vetor com outro vetor dado
  \param v3Vect vetor com o qual determinar o produto vetorial
  \return Vector3 o vetor resultante do produto vetorial
*/
Vector3 Vector3::CrossProduct( Vector3 v3Vect )
{
   return Vector3( this->y * v3Vect.z - this->z * v3Vect.y,
                   this->z * v3Vect.x - this->x * v3Vect.z,
                   this->x * v3Vect.y - this->y * v3Vect.x );
}
// --------------------------------------------------------------------
/**
  \brief Sobrecarga para o operador de soma de vetores
  \param v3Vect objeto Vector3 a ser somado
  \return Vector3 o novo vetor resultante da soma
*/
Vector3 Vector3::operator + ( Vector3 v3Vect )
{
   return Vector3( this->x + v3Vect.x, this->y + v3Vect.y, this->z + v3Vect.z );
}
// --------------------------------------------------------------------
/**
  \brief Sobrecarga para o operador de subtracao de vetores
  \param v3Vect objeto Vector3 a ser subtraido
  \return Vector3 o novo vetor resultante da subtracao
*/
Vector3 Vector3::operator - ( Vector3 v3Vect )
{
   return Vector3( this->x - v3Vect.x, this->y - v3Vect.y, this->z - v3Vect.z );
}
// --------------------------------------------------------------------
/**
  \brief Sobrecarga para o operador de multiplicacao de vetores.
  Esta operacao e equivalente ao produto vetorial entre vetores.
  \param v3Vect objeto Vector3 a ser multiplicado
  \return Vector3 o novo vetor resultante da multiplicado
  \sa CrossProduct()
*/
Vector3 Vector3::operator * ( Vector3 v3Vect )
{
   Vector3 temp( *this );
   return temp.CrossProduct( v3Vect );
}
// --------------------------------------------------------------------
/**
  \brief Sobrecarga para o operador de redimensionamento de vetores.
  Esta operacao e equivalente ao metodo Resize.
  \param fFactor fator de redimensionamento do vetor
  \return Vector3 o novo vetor redimensionado resultante
  \sa Resize()
*/
Vector3 Vector3::operator * ( float fFactor )
{
   Vector3 temp( *this );
   temp.Resize( fFactor );
   return temp;
}
// --------------------------------------------------------------------
/**
  \brief Sobrecarga para o operador de atribuicao de vetores.
  \param v3Vect Objeto a ser atribuido
  \return Vector3 o novo vetor atribuido resultante
*/
Vector3 Vector3::operator =( Vector3 v3Vect )
{
    this->x = v3Vect.x;
    this->y = v3Vect.y;
    this->z = v3Vect.z;
	return *this;
}
