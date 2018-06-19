#include "../include/linked_list.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>


node_t  *list_create(void *data){
  node_t *new_node = malloc(sizeof(node_t));
  if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void list_print(node_t *head){
  if(!head)
    printf("NULL");
  node_t* tmp = head;
  int i = 0;
  while(tmp!=NULL){
       printf("%d)%s\n", i, tmp->data);
       tmp=tmp->next;
       i++;
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

void list_push(node_t *head, void *data){
  node_t* tmp = head;
  while((tmp->next) != NULL){tmp = tmp->next;};
  tmp->next=list_create(data);
}

void  list_unshift(node_t **head, void *data){
  node_t* first = (node_t*) malloc(sizeof(node_t));
  first->data = data;
  first->next = *head;
  *head = first;
}

void nop(void* data){}
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


