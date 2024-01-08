################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/eeprom/eeprom_prog.c 

OBJS += \
./HAL/eeprom/eeprom_prog.o 

C_DEPS += \
./HAL/eeprom/eeprom_prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/eeprom/%.o: ../HAL/eeprom/%.c HAL/eeprom/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\COMMON" -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\APPLICATION" -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\MCAL" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


