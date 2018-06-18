#include<stdio.h>
#include<stdlib.h>
#include"../include/binary_tree.h"
#include <string.h>

node_t  *allocnode(){
    node_t* node =(node_t*) malloc(sizeof(node_t));
    node->key = NULL;
    node->data = NULL;
    node->left = NULL;
    node->right = NULL;
}

node_t  *insert_rec(node_t *root, char *key, void *data){
    if(root == NULL){
        node_t* tmp = allocnode();
        nd->key = key;
        nd->data = data;
        nd->left = NULL;
        nd->right = NULL;
        return nd;
    }
    if(strcmp(key, root->key) <= 0)
        root->left = insert_rec(root->left, key, data);
    else
        root->right = insert_rec(root->right, key, data);
    return root;
}

node_t *insert(node_t *root, char *key, void *data){
    node_t* tmp = insert_rec(root, key, data);
    return nd;
}

void print_node(node_t *node){
  if(node == NULL)
       return;
   printf("Key: %s\n",node->key);
   printf("Data: %s\n",node->data); 
   if(node->left)
      printf("Left: %s\n", node->left->key);
   else
      printf("Left: NULL\n");
   if(node->right)
      printf("Right: %s\n", node->right->key);
   else
      printf("Right: NULL\n");

}

void visit_tree(node_t *node, void (*fp)(node_t *root)){
    if(node == NULL)
        return;
    (*fp)(node);
    visit_tree(node->left, fp);
    visit_tree(node->right, fp);
}

node_t* destroy_tree_rec (node_t *node, void (*fdestroy)(node_t * root)){
   if(node == NULL)
       return NULL;
   (*fdestroy)(node);
   node_t* next = destroy_tree_rec(node->left, fdestroy);
    if(next != NULL)
        free(next);
    next = destroy_tree_rec(node->right, fdestroy);
    if(next != NULL)
        free(next);
    return node;
}

void destroy_tree(node_t *node, void (*fdestroy)(node_t *root)){
    destroy_tree_rec(node, fdestroy);
    if(node) free(node);
}

