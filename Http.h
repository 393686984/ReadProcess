#pragma once
#include "WSKSocket.h"
 char *join(const char *a, const char *b);
VOID Post(IN ULONG IP1, IN ULONG IP2, IN ULONG IP3, IN ULONG IP4, IN const char * url, IN const char * path, IN ULONG Port, IN const char * PostData, IN const char * Other, OUT PVOID RecvBuffer, IN ULONG RecvSize);
