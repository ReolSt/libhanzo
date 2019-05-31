#ifndef HANZO_HASHTABLE_H
#define HANZO_HASHTABLE_H
#include "Vector.h"

typedef struct __Hanzo_Hash_Table
{
  int initialized;
  size_t unitsize;
  Vector table;
  HashFunction hash_func;
} HashTable;

typedef unsigned int (*HashFunction)(void *, size_t);
typedef int (*CompareFunction)(void *, void *, size_t);
void HashTable_Initialize
(
  HashTable *hash_table,
  size_t unitsize
);
void HashTable_Initialize
(
  HashTable *hash_table,
  HashFunction hash_func,
  CompareFunction comp_func,
  size_t unitsize
);
ReturnValue HashTable_Initialized(HashTable *hash_table);
HashFunction HashTable_GetHashFunction(HashTable *hash_table);
void HashTable_SetHashFunction
(
  HashTable *hash_table,
  HashFunction hash_func
);
CompareFunction HashTable_GetCompareFunction(HashTable *hash_table);
void HashTable_SetCompareFunction
(
  HashTable *hash_table,
  CompareFunction comp_func
);
void HashTable_Insert(HashTable *hash_table, void *data);
void *HashTable_Search(HashTable *hash_table, void *data);
void HashTable_Clear(HashTable *hash_table);
void HashTable_Destroy(HashTable *hash_table);

unsigned int HashFunc_DEFAULT(void *, size_t unitsize);
int CompFunc_DEFAULT(void *, void *, size_t unitsize);
#endif
