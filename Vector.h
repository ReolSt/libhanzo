#ifndef Vector_H
#define Vector_H
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <cmath>

#define Vector_DEFAULT_CAPACITY 64

typedef struct _Vector{
  int initialized;
  size_t unitsize;
  size_t capacity;
  size_t size;
  void *array;
} Vector;

void __Vector_Extend(Vector *v);
void __Vector_RShift(Vector *v, int index);
void __Vector_LShift(Vector *v, int index);

void Vector_Initialize(Vector *v, size_t unitsize);
int Vector_Initialized(Vecot *v);
void Vector_Clear(Vector *v);
void Vector_Destroy(Vector *v);
void Vector_Shrink(Vector *v);
void Vector_Resize(Vector *v, size_t size);
void Vector_Insert(Vector *v, int index, const void *x);
void Vector_Remove(Vector *v, int index);
void* Vector_At(Vector *v, int index);
void* Vector_Front(Vector *v);
void* Vector_Back(Vector *v);
size_t Vector_Size(Vector *v);
size_t Vector_Capacity(Vector *v);
void Vector_PushBack(Vector *v, const void *x);
void Vector_PopBack(Vector *v);
#endif
