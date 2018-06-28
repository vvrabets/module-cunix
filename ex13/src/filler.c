#include<stdio.h>
#include<stdlib.h>
#include "reader.c"

//status means: 0 - reading , 1 - writing
//find_enemy is useless

void create_filler(filler_t *filler)
{
  stream_t *s = fake_read();
  filler->current_stream = s;
  filler->status = 0;
  filler->find_enemy = 0;
}

void destroy_filler(filler_t *filler)
{
  free(filler);
  filler=NULL;
}

/*int main()
{
  filler_t* filler = malloc(sizeof(filler_t));
  create_filler(filler);
  printf("%s", filler->current_stream->str);
  destroy_filler(filler);
  printf("%s", filler->current_stream->str);

  return 0;
}*/
