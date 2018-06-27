#include "my_string.c"
#include<stdio.h>

stream_t* fake_read()
{
  stream_t *s = string_create("@\n");
  string_append(s, "5 5\n");
  string_append(s, ".....\n.....\n.....\n.....\n.....\n");
  string_append(s, "4 4\n");
  string_append(s, "*...\n*...\n*...\n*...\n");

  return s;
}

/*int main()
{
  stream_t *s = fake_read();
  printf("%s", s->str);
  return 0;
}*/
