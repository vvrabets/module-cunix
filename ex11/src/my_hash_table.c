#include<stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../include/my_hash_table.h"
#include "../include/my_linked_list.h"

hashtable_t *hash_create(unsigned int size)
{
  hashtable_t *new;

	if(size <= 0)
    return NULL;

	new = malloc(sizeof(hashtable_t));
  new->size = size;
  new->table = malloc(size*sizeof(void*));

  for(int i = 0; i < size; i++)
		new->table[i] = NULL;

  return new;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
  node_t *p;

	for(int i = 0; i < ht->size; i++)
		if(ht->table[i] != NULL){
			p = ht->table[i];
			list_destroy(&p, fp);
	  }

	free(ht->table);
	free(ht);
}

unsigned int hash_func(char *key)
{
  int  sum = 0;
	if(key == NULL)
		return 0;
  for(int i = 0; key[i] != '\0'; i++)
		sum += key[i];
	return sum;
}

void hash_set(hashtable_t *ht, char *key, void *ptr)
{
  if (ht == NULL){
    return;
  }
  unsigned int k = hash_func(key) % ht->size;
  if (ht->table[k] == NULL){
    ht->table[k] = list_create(ptr, key);
  }

  list_push(ht->table[k], ptr, key);
}

void *hash_get(hashtable_t *ht, char *key)
{
  int k = hash_func(key) % ht->size;
  node_t    *p;
	if(ht->table[k] == NULL)
		return NULL;
	p = ht->table[k];
	return p->data;
}

void *print_table(hashtable_t *ht){
  if(ht == NULL)
    return NULL;

  for(int i = 0; i < ht->size; i++)
    if(ht->table[i] != NULL)
      list_print((node_t *)ht->table[i]);
  printf("\n");
}
