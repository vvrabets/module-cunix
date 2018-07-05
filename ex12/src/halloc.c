#include <stdio.h>
#include <stdbool.h>
#include "test.h"
//9223372036854775807
char mallocArray[55000] = {'\0'};
char *base = mallocArray;

char freeflag = 'f';
char allocate = 'a';

char* find_block(size_t size)
{
  char *mover;
  mover = base;

  long unsigned int num ;

  while(true)
  {
    num = *(int *)(mover+1);
    if(*mover == freeflag && num >= size + 5)
    {
      return (mover);
    }else if(!mover)
    {
      return NULL;
    }else{
    if( mover + num + size >= mallocArray + 54999)
    {
      printf("Memory Overflow\n");
      return NULL;
    }
      mover = mover + num;
    }

    }

  return (mover);
}

void split_block(char* b, size_t s)
{
  char* temp;
  int b_size = *(int *)(b + 1);
  b_size = b_size - s ;
  temp = b + s ;
  *temp = freeflag;
  *(int *)(temp + 1) = b_size;
  *(int *)(b + 1) = s;
  *b = allocate;
}

void *halloc(size_t size)
{
  if(size <= 0)
  {
    return NULL;
  }

  if(!*base)
  {
    *base = freeflag;
    *(int *)(base+1) = 54999 ;
  }

  size_t s = size;
  char* b = find_block(s);
  if(b)
  {
    if(*(long unsigned int *)(b+1) >= size)
    {
      split_block(b,s);
    }
  }else{
    return NULL;
  }
  return (b);
}

void myfree(char* address)
{
  char *mover, *previous, *next;
  mover = base;
  int num = *(int *)(mover + 1);
  while(true)
  {
    num = *(int *)(mover + 1);
    if(mover == address)
    {
      break;
    }else if(!*mover)
    {
      break;
    }else
      {
        previous = mover;
        mover = mover + num;
        next = mover + *(int *)(mover + 1);
      }
    }
    if(*next == freeflag)
    {
      *mover = freeflag;
      *(int *)(mover + 1) = *(int *)(mover + 1) + *(int *)(next + 1);
    }
    if(*previous == freeflag)
    {
      *mover = freeflag;
      *(int *)(previous + 1) = *(int *)(mover + 1) + *(int *)(previous + 1);
    }else{
      *address = freeflag;
    }
}

