################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Managers/ConfigurationManager.cpp \
../Managers/LocalizationManager.cpp \
../Managers/MovementManager.cpp \
../Managers/WaypointManager.cpp 

OBJS += \
./Managers/ConfigurationManager.o \
./Managers/LocalizationManager.o \
./Managers/MovementManager.o \
./Managers/WaypointManager.o 

CPP_DEPS += \
./Managers/ConfigurationManager.d \
./Managers/LocalizationManager.d \
./Managers/MovementManager.d \
./Managers/WaypointManager.d 


# Each subdirectory must supply rules for building sources it contributes
Managers/%.o: ../Managers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


