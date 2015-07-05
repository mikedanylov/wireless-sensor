################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NRF24L01/nrf24.c \
../NRF24L01/radioPinFunctions.c 

OBJS += \
./NRF24L01/nrf24.o \
./NRF24L01/radioPinFunctions.o 

C_DEPS += \
./NRF24L01/nrf24.d \
./NRF24L01/radioPinFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
NRF24L01/%.o: ../NRF24L01/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=128000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


