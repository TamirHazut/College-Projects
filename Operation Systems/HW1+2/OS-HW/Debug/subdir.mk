################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../general.c \
../hw1.c \
../hw2.c \
../main.c \
../stack.c 

OBJS += \
./general.o \
./hw1.o \
./hw2.o \
./main.o \
./stack.o 

C_DEPS += \
./general.d \
./hw1.d \
./hw2.d \
./main.d \
./stack.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


