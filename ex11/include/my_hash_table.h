
typedef struct  hashtable {
  unsigned int  size;
  void          **table;
}               hashtable_t;

hashtable_t     *hash_create(unsigned int size);
void            hash_destroy(hashtable_t *ht, void (*fp)(void *data));
unsigned int    hash_func(char *key);

void            hash_set(hashtable_t *ht, char *key, void *ptr);
void            *hash_get(hashtable_t *ht, char *key);
void            *print_table(hashtable_t *ht);