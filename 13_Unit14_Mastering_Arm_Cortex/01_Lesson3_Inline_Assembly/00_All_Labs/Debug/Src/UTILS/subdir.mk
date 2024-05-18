################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/UTILS/common.c 

OBJS += \
./Src/UTILS/common.o 

C_DEPS += \
./Src/UTILS/common.d 


# Each subdirectory must supply rules for building sources it contributes
Src/UTILS/%.o Src/UTILS/%.su Src/UTILS/%.cyclo: ../Src/UTILS/%.c Src/UTILS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/09_U14L3A1/Src/MCAL/inc" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/09_U14L3A1/Src/UTILS/inc" -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-UTILS

clean-Src-2f-UTILS:
	-$(RM) ./Src/UTILS/common.cyclo ./Src/UTILS/common.d ./Src/UTILS/common.o ./Src/UTILS/common.su

.PHONY: clean-Src-2f-UTILS

