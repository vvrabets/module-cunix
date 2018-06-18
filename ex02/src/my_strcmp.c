#include "test.h"

int my_strcmp(char *s1, char *s2){
  unsigned char *str1 = (unsigned char *)s1;
  unsigned char *str2 = (unsigned char *)s2; 
  unsigned char c1,c2;
  do{
    c1=*str1++;
    c2=*str2++;
    if(c1 == '\0' || c2 == '\0'){
      return c1 - c2 > 0 ? 1: c1 - c2 < 0 ? -1: 0;
    };
  }while (c1==c2);
  return c1 - c2 > 0 ? 1: c1 - c2 < 0 ? -1: 0;
}