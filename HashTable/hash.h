typedef struct hash_table hash_table;
unsigned long hashtable_hash(char *k);
hash_table *hashtable_create();
typedef struct hash_entry hash_entry;
hash_entry *hashtable_body_create(int capacity);
void hashtable_resize(hash_table *h, unsigned int capacity);
void hashtable_set(hash_table *h, char *key, void *value);
unsigned int hashtable_find_slot(hash_table *h, char *key);
void *hashtable_get(hash_table *h, char *key);
void hashtable_remove(hash_table *h, char *key);
void hashtable_destroy(hash_table *t);
struct hash_entry {
       char *key;
       void *value;
};

struct hash_table {
       int size;
       int capacity;
       struct hash_entry *table;
};
#define INTERFACE 0
