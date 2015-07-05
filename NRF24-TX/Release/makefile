################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ds18b20/subdir.mk
-include UART/subdir.mk
-include NRF24L01/subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
NRF24-TX.lss \

FLASH_IMAGE += \
NRF24-TX.hex \

EEPROM_IMAGE += \
NRF24-TX.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: NRF24-TX.elf secondary-outputs

# Tool invocations
NRF24-TX.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,NRF24-TX.map -mmcu=atmega328p -o "NRF24-TX.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

NRF24-TX.lss: NRF24-TX.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S NRF24-TX.elf  >"NRF24-TX.lss"
	@echo 'Finished building: $@'
	@echo ' '

NRF24-TX.hex: NRF24-TX.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex NRF24-TX.elf  "NRF24-TX.hex"
	@echo 'Finished building: $@'
	@echo ' '

NRF24-TX.eep: NRF24-TX.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex NRF24-TX.elf  "NRF24-TX.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: NRF24-TX.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p NRF24-TX.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) NRF24-TX.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
