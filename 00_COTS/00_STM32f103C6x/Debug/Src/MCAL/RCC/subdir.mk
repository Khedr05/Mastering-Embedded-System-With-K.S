################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/RCC/RCC.c 

OBJS += \
./Src/MCAL/RCC/RCC.o 

C_DEPS += \
./Src/MCAL/RCC/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/RCC/%.o Src/MCAL/RCC/%.su Src/MCAL/RCC/%.cyclo: ../Src/MCAL/RCC/%.c Src/MCAL/RCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/UTILS" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/MCAL/RCC" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/HAL/KEYPAD" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/HAL/LCD" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/MCAL/GPIO" -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-RCC

clean-Src-2f-MCAL-2f-RCC:
	-$(RM) ./Src/MCAL/RCC/RCC.cyclo ./Src/MCAL/RCC/RCC.d ./Src/MCAL/RCC/RCC.o ./Src/MCAL/RCC/RCC.su

.PHONY: clean-Src-2f-MCAL-2f-RCC

