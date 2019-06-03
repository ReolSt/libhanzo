#ifndef HANZO_FILE_STREAM_H
#define HANZO_FILE_STREAM_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#include "HanzoCall.h"

typedef struct __Hanzo_File_Stream
{
  int initialized;
  int descriptor;
  FILE *stream;

  void (*Initialize)(struct __Hanzo_File_Stream *, int, const char *);
  int (*IsInitialized)(struct __Hanzo_File_Stream *);
  void (*Destroy)(struct __Hanzo_File_Stream *);
  int (*GetDescriptor)(struct __Hanzo_File_Stream *);
  FILE * (*GetStream)(struct __Hanzo_File_Stream *);
  ssize_t (*Write)(struct __Hanzo_File_Stream *, const void *, size_t);
  int (*Puts)(struct __Hanzo_File_Stream *, const char *);
  int (*Printf)(struct __Hanzo_File_Stream *, const char *, ...);
  ssize_t (*Read)(struct __Hanzo_File_Stream *, void *, size_t);
  int (*Scanf)(struct __Hanzo_File_Stream *, const char *, ...);
  char * (*Gets)(struct __Hanzo_File_Stream *, char *, int);
} HanzoFileStream;

void HanzoFileStream_Initialize(HanzoFileStream * file_stream, int fd, const char * mode);
int HanzoFileStream_IsInitialized(HanzoFileStream * file_stream);
void HanzoFileStream_Destroy(HanzoFileStream * file_stream);
int HanzoFileStream_GetDescriptor(HanzoFileStream * file_stream);
FILE * HanzoFileStream_GetStream(HanzoFileStream * file_stream);
ssize_t HanzoFileStream_Write(HanzoFileStream * file_stream, const void * buf, size_t count);
int HanzoFileStream_Puts(HanzoFileStream * file_stream, const char * str);
int HanzoFileStream_Printf(HanzoFileStream * file_stream, const char * format, ...);
ssize_t HanzoFileStream_Read(HanzoFileStream * file_stream, void * buf, size_t count);
int HanzoFileStream_Scanf(HanzoFileStream * file_stream, const char * format, ...);
char * HanzoFileStream_Gets(HanzoFileStream * file_stream, char * str, int num);

#endif
