#include "Vector3.h"
#include <math.h>

const Vector3 Vector3::ZERO   = Vector3();
const Vector3 Vector3::UNIT_X = Vector3( 1.0f, 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::UNIT_Y = Vector3( 0.0f, 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::UNIT_Z = Vector3( 0.0f, 0.0f, 1.0f, 0.0f );

const Vector3 Vector3::BLACK   = Vector3();
const Vector3 Vector3::RED     = Vector3( 1.0f, 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::YELLOW  = Vector3( 1.0f, 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::GREEN   = Vector3( 0.0f, 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::CYAN    = Vector3( 0.0f, 1.0f, 1.0f, 0.0f );
const Vector3 Vector3::BLUE    = Vector3( 0.0f, 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::MAGENTA = Vector3( 1.0f, 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::WHITE   = Vector3( 1.0f, 1.0f, 1.0f, 0.0f );


Vector3::Vector3(float X, float Y, float Z, float W)
{
  this->x = X;
  this->y = Y;
  this->z = Z;
  this->w = W;
}

Vector3::Vector3(const Vector3& clone)
{
  this->x = clone.x;
  this->y = clone.y;
  this->z = clone.z;
  this->w = clone.w;
}

float Vector3::Length()
{
  return (float)sqrt( x*x + y*y + z*z);
}

void Vector3::Normalize()
{
  float fLength = this->Length();
  this->x /= fLength;
  this->y /= fLength;
  this->z /= fLength;
}

void Vector3::Resize (float fFactor)
{
  this->x *= fFactor;
  this->y *= fFactor;
  this->z *= fFactor;
}

float Vector3::DotProduct( Vector3 v3Vect )
{
    return this->x * v3Vect.x + this->y * v3Vect.y + this->z * v3Vect.z;
}

Vector3 Vector3::CrossProduct( Vector3 v3Vect )
{
  return Vector3( this->y * v3Vect.z - this->z * v3Vect.y,
                  this->z * v3Vect.x - this->x * v3Vect.z,
                  this->x * v3Vect.y - this->y * v3Vect.x );
}

Vector3 Vector3::operator + ( Vector3 v3Vect )
{
  return Vector3( this->x + v3Vect.x, this->y + v3Vect.y, this->z + v3Vect.z );
}

Vector3 Vector3::operator - ( Vector3 v3Vect )
{
  return Vector3( this->x - v3Vect.x, this->y - v3Vect.y, this->z - v3Vect.z );
}

Vector3 Vector3::operator * ( Vector3 v3Vect )
{
  Vector3 temp( *this );
  return temp.CrossProduct( v3Vect );
}

Vector3 Vector3::operator * ( float fFactor )
{
  Vector3 temp( *this );
  temp.Resize( fFactor );
  return temp;
}

Vector3 Vector3::operator =( Vector3 v3Vect )
{
  this->x = v3Vect.x;
  this->y = v3Vect.y;
  this->z = v3Vect.z;
	return *this;
}
