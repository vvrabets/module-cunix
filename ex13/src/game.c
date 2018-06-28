#include<stdio.h>
#include<stdlib.h>
#include "../include/filler.h"
#include "filler.c"
#include "parser.c"

int main()
{
  filler_t* filler = malloc(sizeof(filler_t));
  create_filler(filler);
  req_t *r = malloc(sizeof(req_t));
  r = parse_all(filler->current_stream->str);
  printf("%c", r->symbol);

  return 0;
}