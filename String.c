#include "String.h"

void __String_ExtendForNullTerminating(String *string)
{
  if(string->string_vector.size + 2 >= string->string_vector.capacity)
  {
    __Vector_Extend(&(string->string_vector));
  }
}

void String_Initialize(String *string, const char *s, size_t length)
{
  string->initialized = 1;
  vector_Initialize(&(string->string_vector), sizeof(char));
  for(int i=0;i<length;++i)
  {
  Vector_PushBack(&(string->string_vector), s + i);
  }
  string->size = length;
}

void String_Append(String *string, char ch)
{
  vector_PushBack(&(string->string_vector), &ch);
  string->size += 1;
  __String_ExtendForNullTerminating(string);
}

void String_Pop(String *string)
{
  if(string->size > 0)
  {
    Vector_PopBack(&(string->string_vector));
    string->size -= 1;
  }
}

void String_Insert(String *string, int index, char ch)
{
  Vector_Insert(&(string->string_vector), index, &ch);
  string->size += 1;
  __String_ExtendForNullTerminating(string);
}

void String_Remove(String *string, int index)
{
  Vector_Remove(&(string->string_vector), index);
  string->size -= 1;
}

void String_Clear(String *string)
{
  Vector_Clear(&(string->string_vector));
  string->size = 0;
}

void String_Destroy(String *string)
{
  string->initialized = 0;
  Vector_Destroy(&(string->string_vector));
  string->size = 0;
}

const char *String_CStr(String *string)
{
  return (const char*)Vector_At(&(string->string_vector), 0);
}

char String_At(String *string, int index)
{
  return *(char*)Vector_At(&(string->string_vector), index);
}

char *String_At(String *string, int index)
{
  return (char*)Vector_At(&(string->string_vector), index);
}

char String_Front(String *string)
{
  return *(char*)Vector_Front(&(string->string_vector));
}

char String_Back(String *string)
{
  return *(char*)Vector_Back(&(string->string_vector));
}

int String_Length(String *string)
{
  return string->size;
}

//for test
//#include <stdio.h>
// int main()
// {
//   String string;
//   String_Initialize(&string, "Testasdf", 8);
//   String_Remove(&string, 4);
//   printf("%s\n",string_CStr(&string));
//   printf("%c\n",string_At(&string, 1));
//   String_Append(&string, 'a');
//   String_Append(&string, 'b');
//   String_Insert(&string, 2, 'd');
//   printf("%s\n",string_CStr(&string));
// }
