#include"../include/hash.h"
#include"../include/linked_list.h" 
#include<stdlib.h>
#include <string.h>

hashtable_t *hash_create(unsigned int size){
  hashtable_t *newhash;
  if (size > 0) {
    newhash = malloc(sizeof(hashtable_t));
    newhash->size = size;
    newhash->table = malloc(size*sizeof(node_t));
    for (unsigned int i = 0; i < size; i++)
      newhash->table[i] = NULL;
    return newhash;
  }
  else
    return NULL;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data)){
  node_t *tmp;
  for(unsigned int i=0; i<ht->size; i++){
    if(ht->table!=NULL){
      tmp = ht->table[i];
      list_destroy(&tmp, fp);
    }
    free(ht->table);
    free(ht);
  }
}

unsigned int hash_func(char *key){
  int result = 0;
  if (key == NULL)
    return 0;
  while (*key != '\0') {
    result += *key;
    key++;
  }
  return result;
}



void hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data)){
  int i = hash_func(key) % ht->size;
  fp(ptr);
  if (ht->table[i] == NULL)
    ht->table[i] = list_create(ptr);
  else
    list_push(ht->table[i], ptr);
}

void *hash_get(hashtable_t *ht, char *key){
  int i = hash_func(key) % ht->size;
  if(ht->table==NULL)
    return NULL;
  node_t *tmp = ht->table[i];
  return tmp = tmp->data ;
}

