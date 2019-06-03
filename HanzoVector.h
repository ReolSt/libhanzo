#ifndef HANZO_VECTOR_H
#define HANZO_VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "HanzoCall.h"

#define HANZO_VECTOR_DEFAULT_CAPACITY 64

typedef struct __Hanzo_Vector{
  int initialized;
  size_t unitsize;
  size_t capacity;
  size_t size;
  void *array;

  void (*Initialize)(struct __Hanzo_Vector *, size_t);
  int (*IsInitialized)(struct __Hanzo_Vector *);
  void (*Clear)(struct __Hanzo_Vector *);
  void (*Destroy)(struct __Hanzo_Vector *);
  void (*Shrink)(struct __Hanzo_Vector *);
  void (*Resize)(struct __Hanzo_Vector *, size_t);
  void (*Insert)(struct __Hanzo_Vector *, int, const void *);
  void (*Remove)(struct __Hanzo_Vector *, int);
  void * (*At)(struct __Hanzo_Vector *, int);
  void * (*Front)(struct __Hanzo_Vector *);
  void * (*Back)(struct __Hanzo_Vector *);
  size_t (*Size)(struct __Hanzo_Vector *);
  size_t (*Capacity)(struct __Hanzo_Vector *);
  void (*PushBack)(struct __Hanzo_Vector *, const void *);
  void (*PopBack)(struct __Hanzo_Vector *);

} HanzoVector;

void __HanzoVector_Extend(HanzoVector * vector);
void __HanzoVector_RShift(HanzoVector * vector, int index);
void __HanzoVector_LShift(HanzoVector * vector, int index);

void HanzoVector_Initialize(HanzoVector * vector, size_t unitsize);
int HanzoVector_IsInitialized(HanzoVector * vector);
void HanzoVector_Clear(HanzoVector * vector);
void HanzoVector_Destroy(HanzoVector * vector);
void HanzoVector_Shrink(HanzoVector * vector);
void HanzoVector_Resize(HanzoVector * vector, size_t size);
void HanzoVector_Insert(HanzoVector * vector, int index, const void * x);
void HanzoVector_Remove(HanzoVector * vector, int index);
void* HanzoVector_At(HanzoVector * vector, int index);
void* HanzoVector_Front(HanzoVector * vector);
void* HanzoVector_Back(HanzoVector * vector);
size_t HanzoVector_Size(HanzoVector * vector);
size_t HanzoVector_Capacity(HanzoVector * vector);
void HanzoVector_PushBack(HanzoVector * vector, const void * x);
void HanzoVector_PopBack(HanzoVector * vector);
#endif
