################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f103c8tx.s 

OBJS += \
./Startup/startup_stm32f103c8tx.o 

S_DEPS += \
./Startup/startup_stm32f103c8tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/00_Github/Mastering-Embedded-System-With-K.S/14_Unit15_Create_Your_Own_RTOS/00_SherifOS_Scheduler_Part1/SherifOs/CMSIS_V5" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/00_Github/Mastering-Embedded-System-With-K.S/14_Unit15_Create_Your_Own_RTOS/00_SherifOS_Scheduler_Part1/SherifOs/Inc" -gdwarf-2 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f103c8tx.d ./Startup/startup_stm32f103c8tx.o

.PHONY: clean-Startup

