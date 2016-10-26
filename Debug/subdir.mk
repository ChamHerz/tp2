################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../file.c \
../parser.c \
../principal.c \
../scanner.c \
../tp2.c 

OBJS += \
./file.o \
./parser.o \
./principal.o \
./scanner.o \
./tp2.o 

C_DEPS += \
./file.d \
./parser.d \
./principal.d \
./scanner.d \
./tp2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


