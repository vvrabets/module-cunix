#include"linked_list.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

node_t  *list_create(void *data){
  node_t *node = malloc(sizeof(node_t));
  node -> data = malloc(strlen((char*)data+1));
  strcpy(node->data, data);
  node->next=NULL;
};

void dest_rc(node_t **head,void (*fp)(void *data)){
  if((**head).next==NULL){
    return ;
  }else{
    (*head)++;
    dest_rc(head, fp);
    free((**head).next);};
};

void list_destroy(node_t **head, void (*fp)(void *data)){
  if(!(*head)){
    return ;
  }else{
    dest_rc(head, fp);
    free((*head));
  };
};

void list_push(node_t *head, void *data){
    node_t * new_node;
    new_node = malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = head;
    head = new_node;
};

void list_unshift(node_t **head, void *data){
  node_t* first = (node_t*) malloc(sizeof(node_t));
  first->data = data;
  first->next = *head;
  *head = first;
};

void nop(void* data){}
void *list_pop(node_t **head){
  node_t* p = *head;
  while(p->next->next != NULL){
    p = p->next;
  }
  node_t* p_del = p+1;
  list_destroy(&(p_del), &nop);
  p->next = NULL;
};

void *list_shift(node_t **head){
  node_t* new_head = (*head)->next;
  free((*head)->data);
  free(*head);
  *head = new_head;
};

void *list_remove(node_t **head, int pos){
  node_t* p = (*head)+pos;
  if(p == *head)
   list_shift(head);
  if(p->next == NULL){
    list_pop(head);
  }
  else{
    (*head - 1)->data = (*head - 1)->data;
    free((*head)->data);
    free(*head);
  };
};

void    list_print(node_t *head){
  node_t * current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    };
};

void    list_visitor(node_t *head, void (*fp)(void *data)){
  node_t* p = head;
  while(p != NULL){
    (*fp)(p->next);
    p=p->next;
  }
};
