/* 

Author 				:		"Sherif_Ashraf"

Date                :		"12-1-2023"

Version             :		"v-1.0"

Program Description :		"Define New Data Types"

*/





#ifndef DATATYPES_H_
#define DATATYPES_H_



typedef signed char  						Schar8_t;
typedef unsigned char 						Uchar8_t;


typedef signed short int 					Sint16_t;
typedef unsigned short int 					Uint16_t;
typedef signed int 							Sint32_t; 
typedef unsigned int 						Uint32_t;
typedef signed long long int  				Sint64_t;
typedef unsigned long long int  			Uint64_t;



typedef volatile signed short int 			VSint16_t;
typedef volatile unsigned short int 		VUint16_t;
typedef volatile signed int 				VSint32_t; 
typedef volatile unsigned int 				VUint32_t;
typedef volatile signed long long int  		VSint64_t;
typedef volatile unsigned long long int  	VUint64_t;


typedef float								float32_t;
typedef double								float64_t;
typedef long double 						float96_t;


#ifndef TRUE
#define TRUE   1
#endif


#ifndef FALSE
#define FALSE 	0
#endif 


#endif