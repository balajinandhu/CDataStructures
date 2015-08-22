#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "hash.h"

using namespace std;

#if INTERFACE // Need to figure out!
struct hash_entry {
       char *key;
       void *value;
};

struct hash_table {
       int size;
       int capacity;
       struct hash_entry *table;
};
#endif

#define HASHTABLE_INITIAL_CAPACITY 2
/*implementation of djb2(k=33) hash function*/
unsigned long hashtable_hash(char *k){
         unsigned long hash = 5381;
         int c;
         while((c=*k++)){
                     hash=(hash<<5+hash)+c;
         }
         return hash;
}

hash_table *hashtable_create(){
           hash_table *ht = (hash_table *) malloc(sizeof(hash_table));
           ht->size = 0;
           ht->capacity = HASHTABLE_INITIAL_CAPACITY;
           ht->table = hashtable_body_create(ht->capacity);
return ht;
}

hash_entry *hashtable_body_create(int capacity){
           return (hash_entry *)calloc(capacity,sizeof(hash_entry));
}
void hashtable_set(hash_table *h, char *key, void *value) {
     int index = hashtable_find_slot(h, key);
     if(h->table[index].key!=NULL)
     {
                 h->table[index].value = value;                                  
     }
     else
     {
         h->size++;
         if((float) h->size/h->capacity > 0.8){
                    hashtable_resize(h, 2*h->capacity);
         }
              index = hashtable_find_slot(h, key);
              h->table[index].key = key;
              h->table[index].value = value;
     }


}

void hashtable_resize(hash_table *h, unsigned int capacity)
{
     int i;
     assert(capacity >= h->size);
     hash_entry *old_body = h->table;
     unsigned int old_capacity = h->capacity;
     h->table = hashtable_body_create(capacity);
     h->capacity = capacity;
     
     
     for(i=0;i<old_capacity;i++)
     {
             if(old_body[i].key != NULL) {
                          hashtable_set(h, old_body[i].key, old_body[i].value);
             }
     }
}


unsigned int hashtable_find_slot(hash_table *h, char *key){
         int index = hashtable_hash(key) % h->capacity;
         while(h->table[index].key != NULL && strcmp(h->table[index].key, key) != 0){
                                //use linear probing
                    index = (index + 1) % h->capacity;
         }
         return index;
}

void *hashtable_get(hash_table *h, char *key){
     int index = hashtable_find_slot(h, key);
     if(h->table[index].key != NULL){
               return h->table[index].value;
     }
     else
               return NULL;
}

void hashtable_remove(hash_table *h, char *key)
{
         int index = hashtable_find_slot(h, key);
         if(h->table[index].key != NULL) {
             h->table[index].key = NULL;
             h->table[index].value = NULL;
             h->size--;
         }
}
void hashtable_destroy(hash_table *t){
     free(t->table);
     free(t);
}

int main(int argc, char *argv[])
{
  hash_table *ht = hashtable_create();
  hashtable_set(ht, "hello", (int *)123);
  hashtable_set(ht, "bye", (int *)0);
  printf("%u", hashtable_get(ht, "hello"));
  printf("\n%u", hashtable_get(ht, "bye"));
  system("PAUSE");	
  return 0;
}                  
