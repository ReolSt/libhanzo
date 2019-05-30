#include "HashTable.h"

int HashTable_Initialized(HashTable *hash_table)
{
  return hash_table->initialized;
}
HashFunction HashTable_GetHashFunction(HashTable *hash_table)
{
  return hash_table->hash_func;
}
void HashTable_SetHashFunction
(
  HashTable *hash_table,
  HashFunction hash_func
)
{
  hash_table->hash_func = hash_func;
}
CompareFunction HashTable_GetCompareFunction(HashTable *hash_table)
{
  return hash_table->comp_func;
}
void HashTable_SetCompareFunction
(
  HashTable *hash_table,
  CompareFunction comp_func
)
{
  hash_table->comp_func = comp_func;
}
void HashTable_Insert(HashTable *hash_table, void *data);
void *HashTable_Search(HashTable *hash_table, void *data);
void HashTable_Clear(HashTable *hash_table);
void HashTable_Destroy(HashTable *hash_table);
