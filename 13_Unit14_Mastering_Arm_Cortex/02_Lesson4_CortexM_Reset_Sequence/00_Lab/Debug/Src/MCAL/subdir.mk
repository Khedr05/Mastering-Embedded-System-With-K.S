################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/EXTI.c \
../Src/MCAL/GPIO.c \
../Src/MCAL/NVIC.c \
../Src/MCAL/RCC.c 

OBJS += \
./Src/MCAL/EXTI.o \
./Src/MCAL/GPIO.o \
./Src/MCAL/NVIC.o \
./Src/MCAL/RCC.o 

C_DEPS += \
./Src/MCAL/EXTI.d \
./Src/MCAL/GPIO.d \
./Src/MCAL/NVIC.d \
./Src/MCAL/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/%.o Src/MCAL/%.su Src/MCAL/%.cyclo: ../Src/MCAL/%.c Src/MCAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/10_U14L4A1/Src/MCAL/inc" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/10_U14L4A1/Src/UTILS/inc" -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL

clean-Src-2f-MCAL:
	-$(RM) ./Src/MCAL/EXTI.cyclo ./Src/MCAL/EXTI.d ./Src/MCAL/EXTI.o ./Src/MCAL/EXTI.su ./Src/MCAL/GPIO.cyclo ./Src/MCAL/GPIO.d ./Src/MCAL/GPIO.o ./Src/MCAL/GPIO.su ./Src/MCAL/NVIC.cyclo ./Src/MCAL/NVIC.d ./Src/MCAL/NVIC.o ./Src/MCAL/NVIC.su ./Src/MCAL/RCC.cyclo ./Src/MCAL/RCC.d ./Src/MCAL/RCC.o ./Src/MCAL/RCC.su

.PHONY: clean-Src-2f-MCAL

