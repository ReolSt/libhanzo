#include "HanzoString.h"

void __HanzoString_ExtendForNullTerminating(HanzoString *string)
{
  if(string->string_vector.size + 2 >= string->string_vector.capacity)
  {
    __HanzoVector_Extend(&(string->string_vector));
  }
}

void HanzoString_Initialize(HanzoString *string, const char *s, size_t length)
{
  HanzoVector_Initialize(&(string->string_vector), sizeof(char));
  for(int i=0;i<length;++i)
  {
  HanzoVector_PushBack(&(string->string_vector), s + i);
  }
  string->size = length;
//function pointers
  string->Initialize = HanzoString_Initialize;
  string->IsInitialized = HanzoString_IsInitialized;
  string->Append = HanzoString_Append;
  string->PushBack = HanzoString_PushBack;
  string->PopBack = HanzoString_PopBack;
  string->Insert = HanzoString_Insert;
  string->Remove = HanzoString_Remove;
  string->Clear = HanzoString_Clear;
  string->Destroy = HanzoString_Destroy;
  string->CStr = HanzoString_CStr;
  string->At = HanzoString_At;
  string->AtPtr = HanzoString_AtPtr;
  string->Front = HanzoString_Front;
  string->Back = HanzoString_Back;
  string->Length =HanzoString_Length;
//
  string->initialized = 1;
}

int HanzoString_IsInitialized(HanzoString *string)
{
  return string->initialized;
}

void HanzoString_Clear(HanzoString *string)
{
  HanzoVector_Clear(&(string->string_vector));
  string->size = 0;
}

void HanzoString_Destroy(HanzoString *string)
{
  string->initialized = 0;
  HanzoVector_Destroy(&(string->string_vector));
  string->size = 0;
}

void HanzoString_PushBack(HanzoString *string, char ch)
{
  HanzoVector_PushBack(&(string->string_vector), &ch);
  string->size += 1;
  __HanzoString_ExtendForNullTerminating(string);
}


void HanzoString_PopBack(HanzoString *string)
{
  if(string->size > 0)
  {
    HanzoVector_PopBack(&(string->string_vector));
    string->size -= 1;
  }
}

void HanzoString_Append(HanzoString *string, const char * s, size_t length)
{
  for(int i = 0; i < length; ++i)
  {
    HanzoString_PushBack(string, s[i]);
  }
}

void HanzoString_Insert(HanzoString *string, int index, char ch)
{
  HanzoVector_Insert(&(string->string_vector), index, &ch);
  string->size += 1;
  __HanzoString_ExtendForNullTerminating(string);
}

void HanzoString_Remove(HanzoString *string, int index)
{
  HanzoVector_Remove(&(string->string_vector), index);
  string->size -= 1;
}

const char *HanzoString_CStr(HanzoString *string)
{
  return (const char*)HanzoVector_At(&(string->string_vector), 0);
}

char HanzoString_At(HanzoString *string, int index)
{
  return *(char*)HanzoVector_At(&(string->string_vector), index);
}

char *HanzoString_AtPtr(HanzoString *string, int index)
{
  return (char*)HanzoVector_At(&(string->string_vector), index);
}

char HanzoString_Front(HanzoString *string)
{
  return *(char*)HanzoVector_Front(&(string->string_vector));
}

char HanzoString_Back(HanzoString *string)
{
  return *(char*)HanzoVector_Back(&(string->string_vector));
}

int HanzoString_Length(HanzoString *string)
{
  return string->size;
}

// for test
// #include <stdio.h>
// #include "HanzoCall.h"
// int main()
// {
//   HanzoString string;
//   HanzoString_Initialize(&string, "Testasdf", 8);
//   string.Remove(&string, 4);
//   printf("%s\n",string.CStr(&string));
//   printf("%c\n",string.At(&string, 1));
//   string.PushBack(&string, 'a');
//   string.PushBack(&string, 'b');
//   HanzoCall(string, Insert, 2, 'd');
//   printf("%s\n",string.CStr(&string));
// }
