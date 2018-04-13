################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/VFO/ConfigHelpers.cpp \
../Src/VFO/Configuration.cpp \
../Src/VFO/GUIController.cpp \
../Src/VFO/GUIMainView.cpp \
../Src/VFO/GUISetupView.cpp \
../Src/VFO/GUIView.cpp \
../Src/VFO/VFOController.cpp 

OBJS += \
./Src/VFO/ConfigHelpers.o \
./Src/VFO/Configuration.o \
./Src/VFO/GUIController.o \
./Src/VFO/GUIMainView.o \
./Src/VFO/GUISetupView.o \
./Src/VFO/GUIView.o \
./Src/VFO/VFOController.o 

CPP_DEPS += \
./Src/VFO/ConfigHelpers.d \
./Src/VFO/Configuration.d \
./Src/VFO/GUIController.d \
./Src/VFO/GUIMainView.d \
./Src/VFO/GUISetupView.d \
./Src/VFO/GUIView.d \
./Src/VFO/VFOController.d 


# Each subdirectory must supply rules for building sources it contributes
Src/VFO/%.o: ../Src/VFO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -I"/Users/lymes/Development/workspace/STM32VFO/Inc" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


