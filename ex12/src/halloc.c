#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

char mallocArray[55000] = {'\0'};
char *base = mallocArray;

char freeflag = 'f';
char allocate = 'a';

char* find_block(size_t size)
{
  char *mover;
  mover = base;

  long unsigned int num = 0;

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
  b_size = b_size - s - 5;
  temp = b + s + 5;
  *temp = freeflag;
  *(int *)(temp + 1) = b_size;
  *(int *)(b + 1) = s+5;
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
    *(int *)(base+1) = 54999 - 5;
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
    }else{
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

void main()
{
  char* addr1 = halloc(8);
  char* addr2;
  addr2 = halloc(400);
  char* addr3 = halloc(100);

  printf(" 8 %p \n",addr1);
  printf(" 400 %p \n",addr2);
  printf(" 100 %p \n",addr3);

  myfree(addr3);//100
  myfree(addr2);//400

  char* addr4 = halloc(500);
  printf(" 500 %p \n",addr4);
}

/*void main()
{
  char* addr1 = halloc(8);
  char *foo = (char *)halloc(20);
	assert( *foo >  0x0000000000000001);
	myfree(foo);
  printf("first assert\n");
  foo = (char *) halloc(10000000000000000000u);
	assert(foo == NULL);
	myfree(foo);
  printf("second assert\n");
  printf("stage 1 passed\n");
  int **a = (int **)halloc(sizeof(int)* 10000);
  printf("memory allocated\n");
	for (int i = 0; i < 1000; i++)
	{
    printf("we are in for already\n");
		int *tmp = (int *)halloc(sizeof(int));
    printf("memory allocated\n");
		*tmp = i;
		a[i] = tmp;
    printf("cicle %i\n", i);
	}
}*/
