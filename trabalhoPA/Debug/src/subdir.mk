################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/Arquivo.o \
../src/Main.o \
../src/StringsUtil.o 

C_SRCS += \
../src/Arquivo.c \
../src/Main.c \
../src/StringsUtil.c 

OBJS += \
./src/Arquivo.o \
./src/Main.o \
./src/StringsUtil.o 

C_DEPS += \
./src/Arquivo.d \
./src/Main.d \
./src/StringsUtil.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include -O0 -g3 -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


