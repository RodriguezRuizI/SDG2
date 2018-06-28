################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../detector.c \
../fsm.c \
../kbhit.c \
../keypad.c \
../piMusicBox_1.c \
../tmr.c 

OBJS += \
./detector.o \
./fsm.o \
./kbhit.o \
./keypad.o \
./piMusicBox_1.o \
./tmr.o 

C_DEPS += \
./detector.d \
./fsm.d \
./kbhit.d \
./keypad.d \
./piMusicBox_1.d \
./tmr.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"C:\SysGCC\Raspberry\include" -O0 -g3 -Wall -Werror -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


