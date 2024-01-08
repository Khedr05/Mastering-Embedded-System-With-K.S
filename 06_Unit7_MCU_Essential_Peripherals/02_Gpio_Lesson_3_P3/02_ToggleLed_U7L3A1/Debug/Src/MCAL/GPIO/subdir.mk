################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/GPIO/GPIO.c 

OBJS += \
./Src/MCAL/GPIO/GPIO.o 

C_DEPS += \
./Src/MCAL/GPIO/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/GPIO/%.o Src/MCAL/GPIO/%.su Src/MCAL/GPIO/%.cyclo: ../Src/MCAL/GPIO/%.c Src/MCAL/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/05_ToggleLed_U7L3A1/Inc/MCAL/GPIO" -I"D:/Embedded System Diploma/Mastring Embedded System With K.S/01_StmCube_Workspace/05_ToggleLed_U7L3A1/Inc/UTILS" -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-GPIO

clean-Src-2f-MCAL-2f-GPIO:
	-$(RM) ./Src/MCAL/GPIO/GPIO.cyclo ./Src/MCAL/GPIO/GPIO.d ./Src/MCAL/GPIO/GPIO.o ./Src/MCAL/GPIO/GPIO.su

.PHONY: clean-Src-2f-MCAL-2f-GPIO

