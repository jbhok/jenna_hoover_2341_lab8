################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/balloon.cpp \
../src/canimation.cpp \
../src/jenna_hoover_2341_lab8.cpp \
../src/plane.cpp \
../src/planebullet.cpp 

OBJS += \
./src/balloon.o \
./src/canimation.o \
./src/jenna_hoover_2341_lab8.o \
./src/plane.o \
./src/planebullet.o 

CPP_DEPS += \
./src/balloon.d \
./src/canimation.d \
./src/jenna_hoover_2341_lab8.d \
./src/plane.d \
./src/planebullet.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


