#include <stdio.h>

int main(void){
  unsigned int id;
  int min,i;
  float x;

  //min = 1073741824;
  min = 100;
  for(i=0;i<1000;i++){
    for (id=min;id<min+100;id++){
      x = (*(float*)&id);
      printf("%.20e\n", x);
    }
    min = min + 1000000;
  }
  return 0;
}
