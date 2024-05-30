/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       :
// File          : stdTypes.h
// Date          : Sep 8, 2023
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#ifndef STDTYPES_H_
#define STDTYPES_H_

#include <stdint.h>

typedef int8_t 						sint8;
typedef uint8_t						uint8;

typedef int16_t 					sint16;
typedef uint16_t 					uint16;

typedef int32_t 				    sint32;
typedef uint32_t 					uint32;

typedef int64_t 					sint64;
typedef uint64_t  					uint64;



typedef volatile int8_t 					vsint8;
typedef volatile uint8_t					vuint8;

typedef volatile int16_t 					vsint16;
typedef volatile uint16_t 					vuint16;

typedef volatile int32_t 				    vsint32;
typedef volatile uint32_t 					vuint32;

typedef volatile int64_t 					vsint64;
typedef volatile uint64_t  					vuint64;


typedef float								float32;
typedef double								float64;
typedef long double 						float96;


#ifndef bool
typedef enum {
    FALSE = 0,
    TRUE
}bool;
#endif

#ifndef	STR_NULL
#define STR_NULL	'\0'
#endif

#ifndef	PTR_NULL
#define PTR_NULL	(void*)0
#endif


#endif
