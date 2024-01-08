################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/dip/dip_prog.c 

OBJS += \
./HAL/dip/dip_prog.o 

C_DEPS += \
./HAL/dip/dip_prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/dip/%.o: ../HAL/dip/%.c HAL/dip/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\COMMON" -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\APPLICATION" -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\MCAL" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


