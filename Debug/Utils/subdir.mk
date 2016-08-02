################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utils/BaseUtils.cpp \
../Utils/PathPlanner.cpp \
../Utils/lodepng.cpp \
../Utils/pngUtil.cpp 

OBJS += \
./Utils/BaseUtils.o \
./Utils/PathPlanner.o \
./Utils/lodepng.o \
./Utils/pngUtil.o 

CPP_DEPS += \
./Utils/BaseUtils.d \
./Utils/PathPlanner.d \
./Utils/lodepng.d \
./Utils/pngUtil.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/%.o: ../Utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


