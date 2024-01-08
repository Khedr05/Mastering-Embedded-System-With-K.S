################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/uart/subdir.mk
-include MCAL/twi/subdir.mk
-include MCAL/tmr/subdir.mk
-include MCAL/spi/subdir.mk
-include MCAL/gpio/subdir.mk
-include MCAL/gi/subdir.mk
-include MCAL/exti/subdir.mk
-include MCAL/adc/subdir.mk
-include HAL/ssd/subdir.mk
-include HAL/pb/subdir.mk
-include HAL/led/subdir.mk
-include HAL/lcd/subdir.mk
-include HAL/keypad/subdir.mk
-include HAL/eeprom/subdir.mk
-include HAL/dip/subdir.mk
-include APPLICATION/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Atmega32_Drivers
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Atmega32_Drivers.lss \

FLASH_IMAGE += \
Atmega32_Drivers.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: main-build

# Main-build Target
main-build: Atmega32_Drivers.elf secondary-outputs

# Tool invocations
Atmega32_Drivers.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Atmega32_Drivers.map -mmcu=atmega32 -o "Atmega32_Drivers.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Atmega32_Drivers.lss: Atmega32_Drivers.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Atmega32_Drivers.elf  >"Atmega32_Drivers.lss"
	@echo 'Finished building: $@'
	@echo ' '

Atmega32_Drivers.hex: Atmega32_Drivers.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Atmega32_Drivers.elf  "Atmega32_Drivers.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Atmega32_Drivers.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Atmega32_Drivers.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Atmega32_Drivers.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents main-build

-include ../makefile.targets
