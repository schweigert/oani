#ifndef _VECTOR3_NOT_COMPILED_
#define _VECTOR3_NOT_COMPILED_

class Vector3
{
public:
  float x,y,z,w;

  static const Vector3 ZERO;
  static const Vector3 UNIT_X;
  static const Vector3 UNIT_Y;
  static const Vector3 UNIT_Z;

  static const Vector3 BLACK;
  static const Vector3 RED;
  static const Vector3 GREEN;
  static const Vector3 BLUE;
  static const Vector3 YELLOW;
  static const Vector3 MAGENTA;
  static const Vector3 CYAN;
  static const Vector3 WHITE;

  Vector3 (float = 0.0f, float = 0.0f, float = 0.0f, float = 0.0f);
  Vector3( const Vector3&);

  float Length();
  void Normalize();
  void Resize( float );
  float DotProduct ( Vector3 );
  Vector3 CrossProduct ( Vector3 );

  Vector3 operator + (Vector3);
  Vector3 operator - (Vector3);
  Vector3 operator * (Vector3);
  Vector3 operator * (float);
  Vector3 operator = (Vector3);
};

#endif
