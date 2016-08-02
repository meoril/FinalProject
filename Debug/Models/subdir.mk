################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Models/Map.cpp \
../Models/Node.cpp \
../Models/Particle.cpp \
../Models/Point.cpp \
../Models/Position.cpp \
../Models/Robot.cpp \
../Models/Size.cpp 

OBJS += \
./Models/Map.o \
./Models/Node.o \
./Models/Particle.o \
./Models/Point.o \
./Models/Position.o \
./Models/Robot.o \
./Models/Size.o 

CPP_DEPS += \
./Models/Map.d \
./Models/Node.d \
./Models/Particle.d \
./Models/Point.d \
./Models/Position.d \
./Models/Robot.d \
./Models/Size.d 


# Each subdirectory must supply rules for building sources it contributes
Models/%.o: ../Models/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


