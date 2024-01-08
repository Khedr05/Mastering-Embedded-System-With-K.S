################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/adc/adc_prog.c 

OBJS += \
./MCAL/adc/adc_prog.o 

C_DEPS += \
./MCAL/adc/adc_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/adc/%.o: ../MCAL/adc/%.c MCAL/adc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\COMMON" -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\APPLICATION" -I"D:\Programing\Embedded System Diploma\ITI\ITI_Eclipse_Workspace\00_Atmega32\00_Gpio_Driver\MCAL" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


