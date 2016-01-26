#include <stdio.h>
#include <math.h>

int main(void){
  float alpha = 1.0;
  int npoints = 1000;
  float dt = 1.0/npoints;
  int i;
  float y0 = 1.0;
  float yn;
  float T=0;

  for(i=1;i<npoints;i++){
    yn = y0*pow((1-alpha*dt),i);
    T=T+dt;
    printf("%f %f\n",T,yn);
  }



  return 0;
}
