################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/st7735/dwt_stm32_delay.c \
../Src/st7735/st7735.c 

OBJS += \
./Src/st7735/dwt_stm32_delay.o \
./Src/st7735/st7735.o 

C_DEPS += \
./Src/st7735/dwt_stm32_delay.d \
./Src/st7735/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Src/st7735/%.o: ../Src/st7735/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -I"/Users/lymes/Development/workspace/STM32VFO/Inc" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/Users/lymes/Development/workspace/STM32VFO/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


