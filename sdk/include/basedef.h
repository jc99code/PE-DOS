
#ifndef _BASEDEF_H_
#define _BASEDEF_H_

#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

#include "inttypes.h"

typedef INT8 CHAR;
typedef UINT8 UCHAR;
typedef INT16 SHORT;
typedef UINT16 USHORT;
typedef INT32 INT;
typedef UINT32 UINT;

typedef char BYTE;
typedef short WORD;
typedef long DWORD;

typedef void *HANDLE;

#endif
