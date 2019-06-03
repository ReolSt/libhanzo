#include "HanzoVector.h"

#ifndef max
#define max(a,b) (((a) (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif


void __HanzoVector_Extend(HanzoVector * vector)
{
  if(vector->array!=NULL)
  {
    void *newarray = calloc(vector->capacity * 2, vector->unitsize);
    vector->capacity*=2;
    memcpy(newarray, vector->array, vector->size * vector->unitsize);
    free(vector->array);
    vector->array = newarray;
  }
}

void __HanzoVector_RShift(HanzoVector * vector, int index)
{
  if(vector->size > 0 && index >= 0 && index < vector->size)
  {
    vector->size += 1;
    if(vector->size > vector->capacity)
    {
      __HanzoVector_Extend(vector);
    }
    memmove((char*)vector->array + (index + 1) * vector->unitsize,
            (char*)vector->array + index * vector->unitsize,
            (vector->size - index) * vector->unitsize);
  }
}

void __HanzoVector_LShift(HanzoVector * vector, int index)
{
  if(index>=0 && index < vector->size)
  {
    memmove((char*)vector->array + index * vector->unitsize,
            (char*)vector->array + (index + 1) * vector->unitsize,
            (vector->size - index) * vector->unitsize);
    vector->size -= 1;
  }
}

void HanzoVector_Initialize(HanzoVector * vector, size_t unitsize)
{
  vector->unitsize = unitsize;
  vector->size = 0;
  vector->capacity = HANZO_VECTOR_DEFAULT_CAPACITY;
  vector->array = calloc(vector->capacity, vector->unitsize);
//function pointers
  vector->Initialize = HanzoVector_Initialize;
  vector->IsInitialized = HanzoVector_IsInitialized;
  vector->Clear = HanzoVector_Clear;
  vector->Destroy = HanzoVector_Destroy;
  vector->Shrink = HanzoVector_Shrink;
  vector->Resize = HanzoVector_Resize;
  vector->Insert = HanzoVector_Insert;
  vector->Remove = HanzoVector_Remove;
  vector->At = HanzoVector_At;
  vector->Front = HanzoVector_Front;
  vector->Back = HanzoVector_Back;
  vector->Size = HanzoVector_Size;
  vector->Capacity = HanzoVector_Capacity;
  vector->PushBack = HanzoVector_PushBack;
  vector->PopBack = HanzoVector_PopBack;
//
  vector->initialized = 1;
}

int HanzoVector_IsInitialized(HanzoVector * vector)
{
  return vector->initialized;
}

void HanzoVector_Clear(HanzoVector * vector)
{
  free(vector->array);
  HanzoVector_Initialize(vector, vector->unitsize);
}

void HanzoVector_Destroy(HanzoVector * vector)
{
  vector->initialized = 0;
  vector->size = 0;
  vector->capacity = 0;
  free(vector->array);
  vector->array = NULL;
}

void HanzoVector_Shrink(HanzoVector * vector)
{
  if(vector->capacity > HANZO_VECTOR_DEFAULT_CAPACITY)
  {
    HanzoVector_Resize(vector, vector->size + 1);
  }
}

void HanzoVector_Resize(HanzoVector * vector, size_t size)
{
  vector->capacity = size;
  void* resized_array = malloc(vector->capacity * vector->unitsize);
  memcpy(resized_array, vector->array, vector->capacity * vector->unitsize);
  free(vector->array);
  vector->array = resized_array;
  vector->size = min(vector->size, vector->capacity);
}

void HanzoVector_Insert(HanzoVector * vector, int index, const void *x)
{
  if(index >= 0 && index < vector->size)
  {
    __HanzoVector_RShift(vector, index);
    memcpy((char*)vector->array + index * vector->unitsize, x, vector->unitsize);
  }
  else if(index == vector->size)
  {
    HanzoVector_PushBack(vector, x);
  }
}

void HanzoVector_Remove(HanzoVector * vector, int index)
{
  __HanzoVector_LShift(vector, index);
}

void* HanzoVector_At(HanzoVector * vector, int index)
{
  if(index >= 0 && index < vector->size)
  {
    return (char*)vector->array + index * vector->unitsize;
  }
  else
  {
    return NULL;
  }
}

void* HanzoVector_Front(HanzoVector * vector)
{
  return vector->array;
}

void* HanzoVector_Back(HanzoVector * vector)
{
  return (char*)vector->array + (vector->size - 1) * vector->unitsize;
}

size_t HanzoVector_Size(HanzoVector * vector)
{
  return vector->size;
}

size_t HanzoVector_Capacity(HanzoVector * vector)
{
  return vector->capacity;
}

void HanzoVector_PushBack(HanzoVector * vector, const void *x)
{
  vector->size+=1;
  if(vector->size > vector->capacity)
  {
    __HanzoVector_Extend(vector);
  }
  memcpy((char*)vector->array + (vector->size - 1) * vector->unitsize, x, vector->unitsize);
}

void HanzoVector_PopBack(HanzoVector * vector)
{
  if(vector->size > 0)
  {
    memset((char*)vector->array + (vector->size - 1) * vector->unitsize, 0, vector->unitsize);
    vector->size -= 1;
  }
}

// #include <stdio.h>
// void __DEBUG_HanzoVector_Print(HanzoVector * vector)
// {
//   printf("HanzoVector_Size = %ld\n",HanzoVector_Size(vector));
//   printf("HanzoVector_Capacity = %ld\n",HanzoVector_Capacity(vector));
//   for(int i = 0; i < vector->size; i++)
//   {
//     printf("%d ",*(short*)HanzoVector_At(vector, i));
//   }
//   puts("");
// }

// for test
// int main()
// {
//   HanzoVector vector;
//   HanzoVector_Initialize(&vector, 2);
//   short a = 3, b = 10, c = 11, d = 50, e = 27, f = 15, g = 200;
//   printf("HanzoVector_Insert(&vector, 0, &a);\n");
//   vector.Insert(&vector, 0, &a);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_PushBack(&vector, &b);\n");
//   vector.PushBack(&vector, &b);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 0, &c);\n");
//   vector.Insert(&vector, 0, &c);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 2, &d);\n");
//   vector.Insert(&vector, 2, &d);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 4, &e);\n");
//   vector.Insert(&vector, 4, &e);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 3, &f);\n");
//   vector.Insert(&vector, 3, &f);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("__HanzoVector_Extend(&vector);\n");
//   __HanzoVector_Extend(&vector);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Shrink(&vector);\n");
//   vector.Shrink(&vector);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_PushBack(&vector, &g);\n");
//   vector.PushBack(&vector, &g);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Remove(&vector, 3);\n");
//   vector.Remove(&vector, 3);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Clear(&vector);\n");
//   vector.Clear(&vector);
//   __DEBUG_HanzoVector_Print(&vector);
// }
