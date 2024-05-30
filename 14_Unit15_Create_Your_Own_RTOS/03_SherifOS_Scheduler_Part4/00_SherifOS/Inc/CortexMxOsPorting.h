/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : CortexMxOsPorting.h
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef CORTEXMXOSPORTING_H_
#define CORTEXMXOSPORTING_H_

#include "core_cm3.h"

extern int _estack;
extern int _eheap;

#define MAIN_STACK_SIZE 		3072

#define OS_SET_PSP(addr)  		__asm volatile("MOV R0,%0 \n\t MSR PSP,R0" : :"r"(addr))
#define OS_GET_PSP(addr)  		__asm volatile("MRS R0,PSP \n\t MOV %0,R0" :"=r"(addr))

#define OS_SWITCH_SP_TO_PSP		__asm volatile("MRS R0,CONTROL \n\t MOV R1,#0x02 \n\t ORR R0,R0,R1 \n\t MSR CONTROL,R0")
#define OS_SWITCH_SP_TO_MSP		__asm volatile("MRS R0,CONTROL \n\t MOV R1,#0x05 \n\t AND R0,R0,R1 \n\t MSR CONTROL,R0")

#define OS_GENERATE_EXCEPTION   __asm volatile("SVC #0x3")

#define OS_SWITCH_TO_PRIVILEGED __asm("MRS R3,CONTROL \n\t LSR R3,R3,#0x1 \n\t LSL R3,R3,#0x1 \n\t MSR CONTROL,R3")
#define OS_SWITCH_TO_UNPRIVILEGED __asm("MRS R3,CONTROL \n\t ORR R3,R3,#0x1 \n\t MSR CONTROL,R3")





void triggerOsPendSV(void);
void StartTicker(void);

#endif /* CORTEXMXOSPORTING_H_ */
