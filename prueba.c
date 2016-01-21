#include <stdio.h>

int main(){
  int a,b;
  //char c;
  a = 2000000000;
  b = 3;
  long long c = a*((long long)b); // cambia b a long long
  printf("%lld\n",c); //lld convencion para imprimir long long
  return 0;
}
