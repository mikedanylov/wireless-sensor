################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../hd44780.c \
../main.c \
../nrf24.c \
../radioPinFunctions.c 

OBJS += \
./ADC.o \
./hd44780.o \
./main.o \
./nrf24.o \
./radioPinFunctions.o 

C_DEPS += \
./ADC.d \
./hd44780.d \
./main.d \
./nrf24.d \
./radioPinFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


