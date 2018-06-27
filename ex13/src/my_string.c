#include<stdlib.h>
#include "../include/my_string.h"
#include<stdio.h>
#include<string.h>

stream_t *string_init()
{
  stream_t *s = malloc(sizeof(64));
  s->size = 0;
  s->str =  "";
  s->limit = BUF_SIZE;

  return s;
}

stream_t *string_create(char* str)
{
  stream_t *s = string_init();
  s->str = str;
  s->size = strlen(str);

  return s;
}

void string_append(stream_t *ptr, char* str)
{
  if(ptr != NULL){
    char *result = malloc(strlen(ptr->str) + strlen(str) + 1);
    strcpy(result, ptr->str);
    strcat(result, str);
    ptr->str = result;
  }
}

void string_destroy(stream_t *str)
{
  free(str);
  str=NULL;
}

/*int main()
{
  stream_t *s = string_create("Hello World");
  printf("%s\n",s->str);
  string_append(s, " Vova");
  printf("%s", s->str);
  string_destroy(s);

  return 0;
}*/
