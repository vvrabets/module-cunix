typedef struct  node {
    void        *data;
    char        *key;
    struct node *next;
}node_t;

node_t  *list_create(void *data, char *key);

void    list_destroy(node_t **head, void (*fp)(void *data));

void    list_push(node_t *head, void *data, char* key);
void    list_unshift(node_t **head, void *data, char* key);

void    *list_pop(node_t **head);
void    *list_shift(node_t **head);
void    *list_remove(node_t **head, int pos);

void    list_print(node_t *head);
void    list_visitor(node_t *head, void (*fp)(void *data));


