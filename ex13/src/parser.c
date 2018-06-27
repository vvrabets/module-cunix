#include "reader.c"
#include "../include/filler.h"
#include<stdio.h>
#include<stdlib.h>

req_t* parse_all(char *all)
{
  req_t *r = malloc(sizeof(req_t));
  map_t *m = malloc(sizeof(map_t));
  elem_t *e = malloc(sizeof(elem_t));
  stream_t *s = fake_read();
  char *sp;
  int i = 1;

  sp = strtok(s->str, "\n");
  r->symbol = s->str[0];
  //printf("%c\n", r->symbol);
  while (sp) {
    if(i == 1){
      sp = strtok(NULL," ");
      m->h = atoi(sp);
      //printf("%i", m->h);
    }
    if(i == 2){
      m->w = atoi(sp);
      //printf(" %i\n", m->w);
    }
    if(i == 3){
      m->array = calloc (m->h,sizeof(char*));
      int j = 0;
      while(j < m->h){
        char *result = malloc(strlen(sp) + 1);
        strcpy(result, sp);
        strcat(result, "\n");
        m->array[j] = result;
        //printf("%s", m->array[j]);
        if(j < m->h-2)
          sp = strtok(NULL, "\n");
        j++;
      }
    }
    if(i == 4){
      sp = strtok(NULL," ");
      e->h = atoi(sp);
      //printf("%i", e->h);
    }
    if(i == 5){
      e->w = atoi(sp);
      //printf(" %i\n", e->w);
    }
    if(i == 6){
      e->array = calloc (e->h,sizeof(char*));
      int j = 0;
      while(j < e->h){
        char *result = malloc(strlen(sp) + 1);
        strcpy(result, sp);
        strcat(result, "\n");
        e->array[j] = result;
        //printf("%s", e->array[j]);
        if(j < e->h-2)
          sp = strtok(NULL, "\n");
        j++;
        }
    }
    sp = strtok(NULL, "\n");
    i++;
	}

  r->map = *m;
  r->elem = *e;

  return r;
}

pos_t parse_size(char *answer)
{
  pos_t p ;
  char* sp;
  sp = strtok(answer, " ");
  p.x = atoi(sp);
  sp = strtok(answer, "\n");
  p.y = atoi(sp);
  return p;
}

int main()
{
  stream_t *s = fake_read();
  req_t *r = parse_all(s->str);

  return 0;
}
