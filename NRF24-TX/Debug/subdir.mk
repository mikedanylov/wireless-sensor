################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NRF24L01_HardAdapt.c \
../Record.c \
../TempSensHardAdapt.c \
../main.c 

OBJS += \
./NRF24L01_HardAdapt.o \
./Record.o \
./TempSensHardAdapt.o \
./main.o 

C_DEPS += \
./NRF24L01_HardAdapt.d \
./Record.d \
./TempSensHardAdapt.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=128000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


