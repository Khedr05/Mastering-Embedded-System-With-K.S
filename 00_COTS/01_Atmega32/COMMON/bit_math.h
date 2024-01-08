/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Gpio_Driver
// File          : bit_math.h
// Date          : 31 Jul 2023 */ GitHub        : https://github.com/sherifkhadr
/*************************************************************************/
#ifndef COMMON_BIT_MATH_H_
#define COMMON_BIT_MATH_H_

#define SET_BIT(REG, BIT_NUMBER) (REG |= (1 << BIT_NUMBER))
#define GET_BIT(REG, BIT_NUMBER) ((REG >> BIT_NUMBER) & 1)
#define CLR_BIT(REG, BIT_NUMBER) (REG &= (~(1 << BIT_NUMBER)))
#define TOG_BIT(REG, BIT_NUMBER) (REG ^= (1 << BIT_NUMBER))

#endif /* COMMON_BIT_MATH_H_ */
