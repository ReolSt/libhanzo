#include "HashTable.h"
#include <memory.h>
#include <limit.h>

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
void HashTable_Insert(HashTable *hash_table, void *data)
{

}
void *HashTable_Search(HashTable *hash_table, void *data)
{

}
void HashTable_Clear(HashTable *hash_table)
{

}
void HashTable_Destroy(HashTable *hash_table)
{

}

unsigned int HashFunc_DEFAULT(void *, size_t unitsize)
{

}

int __HashFunc_IsLittleEndian()
{
  unsigned int x = 1;
  char *c = (char*) &x;
  return (int)*c;
}

int CompFunc_DEFAULT(void *da, void *db, size_t unitsize)
{
  char *a = (char*)da, *b = (char*)db;
  if(IsLittleEndian())
  {
    char la[unitsize], lb[unitsize];
    for(int i=0; i < unitsize; i += 2)
    {
      la[i] = a[i + 1];
      la[i + 1] = a[i];
      lb[i] = b[i + 1];
      lb[i + 1] = b[i];
    }
    for(int i=unitsize - 1; i >= 0; --i)
    {
      if(*(a + i) > *(b + i))
      {
        return 1;
      }
      else if(*(a + i) < *(b + i))
      {
        return -1;
      }
    }
    return 0;
  }
  else
  {
    for(int i = 0; i < unitsize; ++i)
    {
      if(*(a + i) > *(b + i))
      {
        return 1;
      }
      else if(*(a + i) < *(b + i))
      {
        return -1;
      }
    }
    return 0;
  }
}
