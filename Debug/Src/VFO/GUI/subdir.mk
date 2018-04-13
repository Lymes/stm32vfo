################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/VFO/GUI/Background.cpp \
../Src/VFO/GUI/FrequencyString.cpp \
../Src/VFO/GUI/Utils.cpp 

OBJS += \
./Src/VFO/GUI/Background.o \
./Src/VFO/GUI/FrequencyString.o \
./Src/VFO/GUI/Utils.o 

CPP_DEPS += \
./Src/VFO/GUI/Background.d \
./Src/VFO/GUI/FrequencyString.d \
./Src/VFO/GUI/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Src/VFO/GUI/%.o: ../Src/VFO/GUI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -I"/Users/lymes/Development/workspace/STM32VFO/Inc" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


