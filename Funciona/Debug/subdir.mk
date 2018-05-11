################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../estados.c \
../fsm.c \
../piMusicBox_4.c \
../tmr.c 

OBJS += \
./estados.o \
./fsm.o \
./piMusicBox_4.o \
./tmr.o 

C_DEPS += \
./estados.d \
./fsm.d \
./piMusicBox_4.d \
./tmr.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"C:\SysGCC\Raspberry\include" -I"C:\SysGCC\Raspberry\include\wiringPi" -O0 -g3 -Wall -Werror -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


