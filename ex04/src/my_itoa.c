//#include "test.h"
#include<stdio.h>

int my_itoa(int nmb){
  int a_as_int = (int)'a';
  return a_as_int;
};

int main(){
  int output=my_itoa(123);
  printf("%i", output);
return 0;
};
