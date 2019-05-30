#ifndef String_H
#define String_H
#include "Vector.h"
typedef struct _String
{
  int initialized;
  Vector string_vector;
  size_t size;
} String;

void __String_ExtendForNullTerminating(String *string);
void String_Init(String *string, const char *s, size_t length);
int String_Initialized(String *string);
void String_Append(String *string, const char ch);
void String_Pop(String *string);
void String_Insert(String *string, int index, const char ch);
void String_Remove(String *string, int index);
void String_Clear(String *string);
void String_Destroy(String *string);
const char *String_CStr(String *string);
char String_At(String *string, int index);
char *String_AtPtr(String *string, int index);
char String_Front(String *string);
char String_Back(String *string);
int String_Length(String *string);
#endif
