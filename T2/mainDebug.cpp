#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

int main(void){

  Matrix* m = new Matrix(3);

  double* valor = NULL;

  m->SetValue(1,1,10.0);
  m->SetValue(1,2,-7.0);
  m->SetValue(1,3,5.0);
  m->SetValue(1,4,9.0);

  m->SetValue(2,1,3.0);
  m->SetValue(2,2,6.0);
  m->SetValue(2,3,0.0);
  m->SetValue(2,4,-9.0);

  m->SetValue(3,1,9.0);
  m->SetValue(3,2,3.0);
  m->SetValue(3,3,-2.0);
  m->SetValue(3,4,-1.0);

  valor = m->GaussMethod();

  for(int i = 0; i < 3; i++){
    printf("%lf\n",valor[i]);
  }

  delete m;

  return 0;
}
