################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f103c6tx.s 

OBJS += \
./Startup/startup_stm32f103c6tx.o 

S_DEPS += \
./Startup/startup_stm32f103c6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/UTILS" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/MCAL/RCC" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/HAL/LCD" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/HAL/KEYPAD" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/Stm32f103c6x_Drivers/Inc/MCAL/GPIO" -gdwarf-2 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f103c6tx.d ./Startup/startup_stm32f103c6tx.o

.PHONY: clean-Startup

