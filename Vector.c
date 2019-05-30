#include "Vector.h"

void __Vector_Extend(Vector *v)
{
  if(v->array!=NULL)
  {
    void *newarray = calloc(v->capacity * 2, v->unitsize);
    v->capacity*=2;
    memcpy(newarray, v->array, v->size * v->unitsize);
    free(v->array);
    v->array = newarray;
  }
}

void __Vector_RShift(Vector *v, int index)
{
  if(v->size > 0 && index >= 0 && index < v->size)
  {
    v->size += 1;
    if(v->size > v->capacity)
    {
      __Vector_Extend(v);
    }
    memmove((char*)v->array + (index + 1) * v->unitsize,
            (char*)v->array + index * v->unitsize,
            (v->size - index) * v->unitsize);
  }
}

void __Vector_LShift(Vector *v, int index)
{
  if(index>=0 && index < v->size)
  {
    memmove((char*)v->array + index * v->unitsize,
            (char*)v->array + (index + 1) * v->unitsize,
            (v->size - index) * v->unitsize);
    v->size -= 1;
  }
}

void Vector_Initialize(Vector *v, size_t unitsize)
{
  v->initialized = 1;
  v->unitsize = unitsize;
  v->size = 0;
  v->capacity = VECTOR_DEFAULT_CAPACITY;
  v->array = calloc(v->capacity, v->unitsize);
}

int Vector_Initialized(Vector *v)
{
  return v->initialized;
}

void Vector_Clear(Vector *v)
{
  free(v->array);
  Vector_init(v, v->unitsize);
}

void Vector_Destroy(Vector *v)
{
  v->initialized = 0;
  v->size = 0;
  v->capacity = 0;
  free(v->array);
  v->array = NULL;
}

void Vector_Shrink(Vector *v)
{
  if(v->capacity > VECTOR_DEFAULT_CAPACITY)
  {
    Vector_Resize(v, v->capacity / 2);
  }
}

void Vector_Resize(Vector *v, size_t size)
{
  v->capacity = size;
  void* resized_array = malloc(v->capacity * v->unitsize);
  memcpy(resized_array, v->array, v->capacity * v->unitsize);
  free(v->array);
  v->array = resized_array;
  v->size = min(v->size, v->capacity);
}

void Vector_Insert(Vector *v, int index, const void *x)
{
  if(index >= 0 && index < v->size)
  {
    __Vector_RShift(v, index);
    memcpy((char*)v->array + index * v->unitsize, x, v->unitsize);
  }
  else if(index == v->size)
  {
    Vector_PushBack(v, x);
  }
}

void Vector_Remove(Vector *v, int index)
{
  __Vector_LShift(v, index);
  if(v->size < v->capacity / 3)
  {
    Vector_Shrink(v);
  }
}

void* Vector_At(Vector *v, int index)
{
  if(index >= 0 && index < v->size)
  {
    return (char*)v->array + index * v->unitsize;
  }
  else
  {
    return NULL;
  }
}

void* Vector_Front(Vector *v)
{
  return v->array;
}

void* Vector_Back(Vector *v)
{
  return (char*)v->array + (v->size - 1) * v->unitsize;
}

size_t Vector_Size(Vector *v)
{
  return v->size;
}

size_t Vector_Capacity(Vector *v)
{
  return v->capacity;
}

void Vector_PushBack(Vector *v, const void *x)
{
  v->size+=1;
  if(v->size > v->capacity)
  {
    __Vector_Extend(v);
  }
  memcpy((char*)v->array + (v->size - 1) * v->unitsize, x, v->unitsize);
}

void Vector_PopBack(Vector *v)
{
  if(v->size > 0)
  {
    v->size -= 1;
  }
}

// #include <stdio.h>
// void __DEBUG_Vector_Print(Vector *v)
// {
//   printf("Vector_Size = %ld\n",Vector_Size(v));
//   printf("Vector_Capacity = %ld\n",Vector_Capacity(v));
//   for(int i = 0; i < v->size; i++)
//   {
//     printf("%d ",*(short*)Vector_At(v, i));
//   }
//   puts("");
// }

// for test
// int main()
// {
//   Vector v;
//   Vector_init(&v, 2);
//   short a = 3, b = 10, c = 11, d = 50, e = 27, f = 15, g = 200;
//   printf("Vector_Insert(&v, 0, &a);\n");
//   Vector_Insert(&v, 0, &a);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_PushBack(&v, &b);\n");
//   Vector_PushBack(&v, &b);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_Insert(&v, 0, &c);\n");
//   Vector_Insert(&v, 0, &c);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_Insert(&v, 2, &d);\n");
//   Vector_Insert(&v, 2, &d);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_Insert(&v, 4, &e);\n");
//   Vector_Insert(&v, 4, &e);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_Insert(&v, 3, &f);\n");
//   Vector_Insert(&v, 3, &f);
//   __DEBUG_Vector_Print(&v);
//   printf("__Vector_Extend(&v);\n");
//   __Vector_Extend(&v);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_Shrink(&v);\n");
//   Vector_Shrink(&v);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_PushBack(&v, &g);\n");
//   Vector_PushBack(&v, &g);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_Remove(&v, 3);\n");
//   Vector_Remove(&v, 3);
//   __DEBUG_Vector_Print(&v);
//   printf("Vector_Clear(&v);\n");
//   Vector_Clear(&v);
//   __DEBUG_Vector_Print(&v);
// }
