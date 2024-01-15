/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : common.h
// Date          : Jan 6, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef UTILS_COMMON_H_
#define UTILS_COMMON_H_

#include <stdint.h>


// Bit Math Lib

#define SET_BIT(REG, BIT_NUMBER) (REG |= (1 << BIT_NUMBER))
#define GET_BIT(REG, BIT_NUMBER) ((REG >> BIT_NUMBER) & 1)
#define CLR_BIT(REG, BIT_NUMBER) (REG &= (~(1 << BIT_NUMBER)))
#define TOG_BIT(REG, BIT_NUMBER) (REG ^= (1 << BIT_NUMBER))


#define SET_BITS(REG,MSK)			(REG) |=  (MSK)
#define CLR_BITS(REG,MSK)			(REG) &= ~(MSK)
#define TOG_BITS(REG,MSK)			(REG) ^=  (MSK)

#define SET_ALL_BITS(REG)			(REG) =  (0xFFFFFFFF)
#define CLR_ALL_BITS(REG)			(REG) =  (0x00000000)
#define TOG_ALL_BITS(REG)			(REG) ^= (0xFFFFFFFF)

// Standard Data Type Lib

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

#ifndef	NULL_STR
#define NULL_STR	'\0'
#endif

#ifndef	NULL_PTR
#define NULL_PTR	(void*)0
#endif

// Delay Lib

#define F_CPU		8000000UL

void Udelay_ms(uint16 milliseconds);


// API Error States

/*@ref API Error States*/
typedef enum
{
	UAPI_NOK = 0,
	UAPI_OK,
	UAPI_NULL_PTR,
	UAPI_NULL_STR,
	UAPI_INVALID_PARM
}COMMON_uddtApiState_t;

/*@ref API Error States
 *
 * UAPI_NOK 		 : API Failure
 * UAPI_OK  	  	 : API Success
 * UAPI_NULL_PTR 	 : API Detect Null Pointer
 * UAPI_NULL_STR 	 : API Detect Null String
 * UAPI_INVALID_PARM : API Detect Invalid Parameter
 */

#endif /* UTILS_COMMON_H_ */
