################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Control_ECU.c \
../adc.c \
../buzzer.c \
../dc_motor.c \
../external_eeprom.c \
../gpio.c \
../main.c \
../pwm.c \
../timers.c \
../twi.c \
../uart.c 

OBJS += \
./Control_ECU.o \
./adc.o \
./buzzer.o \
./dc_motor.o \
./external_eeprom.o \
./gpio.o \
./main.o \
./pwm.o \
./timers.o \
./twi.o \
./uart.o 

C_DEPS += \
./Control_ECU.d \
./adc.d \
./buzzer.d \
./dc_motor.d \
./external_eeprom.d \
./gpio.d \
./main.d \
./pwm.d \
./timers.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


