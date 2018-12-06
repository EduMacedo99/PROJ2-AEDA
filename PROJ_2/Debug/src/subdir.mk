################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bilhete.cpp \
../src/Maquina.cpp \
../src/PROJ_2.cpp \
../src/PontosVenda.cpp \
../src/Utente.cpp 

OBJS += \
./src/Bilhete.o \
./src/Maquina.o \
./src/PROJ_2.o \
./src/PontosVenda.o \
./src/Utente.o 

CPP_DEPS += \
./src/Bilhete.d \
./src/Maquina.d \
./src/PROJ_2.d \
./src/PontosVenda.d \
./src/Utente.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


