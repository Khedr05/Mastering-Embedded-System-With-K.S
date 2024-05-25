################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CortexMxOsPorting.c \
../Src/Fifo.c \
../Src/Scheduler.c \
../Src/main.c 

OBJS += \
./Src/CortexMxOsPorting.o \
./Src/Fifo.o \
./Src/Scheduler.o \
./Src/main.o 

C_DEPS += \
./Src/CortexMxOsPorting.d \
./Src/Fifo.d \
./Src/Scheduler.d \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/13_SherifOS/CMSIS_V5" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/13_SherifOS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/CortexMxOsPorting.cyclo ./Src/CortexMxOsPorting.d ./Src/CortexMxOsPorting.o ./Src/CortexMxOsPorting.su ./Src/Fifo.cyclo ./Src/Fifo.d ./Src/Fifo.o ./Src/Fifo.su ./Src/Scheduler.cyclo ./Src/Scheduler.d ./Src/Scheduler.o ./Src/Scheduler.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su

.PHONY: clean-Src

