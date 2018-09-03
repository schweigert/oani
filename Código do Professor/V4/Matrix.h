#ifndef _MATRIX_NOT_INCLUDED_
#define _MATRIX_NOT_INCLUDED_

class Matrix {
private:
  double** dMat;
  unsigned int uiRows, uiLines;

public:
  Matrix(unsigned int, unsigned int);
  ~Matrix();

  unsigned int getRows();
  unsigned int getLines();

  double determinant();
  double determinant3x3();

  void swapLine(unsigned int, unsigned int);
};

#endif
