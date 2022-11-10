
#ifndef _INTTYPES_H_
#define _INTTYPES_H_

typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;
typedef signed int INT32;
typedef unsigned int UINT32;
typedef signed long long INT64;
typedef unsigned long long UINT64;

#if defined(_M_AMD64)
typedef long long INT_PTR;
typedef unsigned long long UINT_PTR;
#else
typedef long INT_PTR;
typedef unsigned long UINT_PTR;
#endif

#endif
