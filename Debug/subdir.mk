################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ADCconv.cpp \
../CircBuffer.cpp \
../Debugger.cpp \
../GPIO_Pin.cpp \
../GPIO_Port.cpp \
../Queue.cpp \
../UART.cpp \
../main.cpp 

OBJS += \
./ADCconv.o \
./CircBuffer.o \
./Debugger.o \
./GPIO_Pin.o \
./GPIO_Port.o \
./Queue.o \
./UART.o \
./main.o 

CPP_DEPS += \
./ADCconv.d \
./CircBuffer.d \
./Debugger.d \
./GPIO_Pin.d \
./GPIO_Port.d \
./Queue.d \
./UART.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


