#include "../include/my_linked_list.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

node_t  *list_create(void *data, char *key){
  node_t 	*head;
  head = malloc(sizeof(node_t));
	head->data = data;
  head->key = key;
	head->next = NULL;
  return head;
}

void list_print(node_t *head){
  node_t 	*tmp = head;
	while( tmp != NULL){
    printf("\n%s: %s", tmp->key, tmp->data);
    tmp = tmp->next;
  }
}

void dest_r(node_t *head, void (*fp)(void *data)){
    if(head == NULL)
        return;
    dest_r(head->next, fp);
    (*fp)(head->data);
    free(head);
    head = NULL;
    return;
}

void  list_destroy(node_t **head, void (*fp)(void *data)){
  dest_r(*head, fp);
  *head = NULL;
}

void list_push(node_t *head, void *data, char *key){
  if(head == NULL)
    return;

	node_t *tmp = head;
  node_t *ptr = malloc(sizeof(node_t));

  while(tmp->next != NULL)
		tmp = tmp->next;

  ptr->key = key;
	ptr->data = data;
	ptr->next = NULL;
  tmp->next = ptr;
}

void  list_unshift(node_t **head, void *data, char *key){
  node_t* first = (node_t*) malloc(sizeof(node_t));
  first->data = data;
  first->key = key;
  first->next = *head;
  *head = first;
}


void free_data(void* data){
    free(data);
}


void *list_pop(node_t **head){
  node_t *temp = *head;
    if (temp) {
        *head = temp->next;
    }
    return temp;
}

void *list_shift(node_t **head){
  node_t* new_head = (*head)->next;
  free((*head)->data);
  free(*head);
  *head = new_head;
}

void *list_remove(node_t **head, int pos){
  if(!*head)
    return NULL;
  node_t fp;
  fp.next = *head;
  node_t* p = &fp;
  for(int i = 0; i < pos; i++)
      p = p->next;
  free(p->next->data);
  node_t* to_remove = p->next;
  p->next = p->next->next;
  free(to_remove);
  return *head;
}

void list_visitor(node_t *head, void (*fp)(void *data)){
  node_t* tmp = head;
  while(tmp != NULL){
    (*fp)(tmp->next);
    tmp=tmp->next;
  }
}
