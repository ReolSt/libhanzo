#ifndef HANZO_STRING_H
#define HANZO_STRING_H

#include "HanzoCall.h"
#include "HanzoVector.h"

typedef struct __Hanzo_String
{
  int initialized;
  HanzoVector string_vector;
  size_t size;

  void (*Initialize)(struct __Hanzo_String *, const char *s, size_t);
  int (*IsInitialized)(struct __Hanzo_String *);
  void (*Clear)(struct __Hanzo_String *);
  void (*Destroy)(struct __Hanzo_String *);
  void (*Append)(struct __Hanzo_String *, const char *, size_t);
  void (*PushBack)(struct __Hanzo_String *, char);
  void (*PopBack)(struct __Hanzo_String *);
  void (*Insert)(struct __Hanzo_String *, int, const char);
  void (*Remove)(struct __Hanzo_String *, int);
  const char * (*CStr)(struct __Hanzo_String *);
  char (*At)(struct __Hanzo_String *, int);
  char * (*AtPtr)(struct __Hanzo_String *, int);
  char (*Front)(struct __Hanzo_String *);
  char (*Back)(struct __Hanzo_String *);
  int (*Length)(struct __Hanzo_String *);
} HanzoString;

void __HanzoString_ExtendForNullTerminating(HanzoString * string);
void HanzoString_Initialize(HanzoString * string, const char * s, size_t length);
int HanzoString_IsInitialized(HanzoString * string);
void HanzoString_Clear(HanzoString * string);
void HanzoString_Destroy(HanzoString * string);
void HanzoString_PushBack(HanzoString * string, char ch);
void HanzoString_PopBack(HanzoString * string);
void HanzoString_Append(HanzoString * string, const char * s, size_t length);
void HanzoString_Insert(HanzoString * string, int index,  char ch);
void HanzoString_Remove(HanzoString * string, int index);
const char * HanzoString_CStr(HanzoString * string);
char HanzoString_At(HanzoString * string, int index);
char * HanzoString_AtPtr(HanzoString * string, int index);
char HanzoString_Front(HanzoString * string);
char HanzoString_Back(HanzoString * string);
int HanzoString_Length(HanzoString * string);
#endif
