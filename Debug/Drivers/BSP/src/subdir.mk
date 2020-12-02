################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/src/font12.c \
../Drivers/BSP/src/font16.c \
../Drivers/BSP/src/font20.c \
../Drivers/BSP/src/font24.c \
../Drivers/BSP/src/font8.c \
../Drivers/BSP/src/stm32746g_discovery.c \
../Drivers/BSP/src/stm32746g_discovery_lcd.c \
../Drivers/BSP/src/stm32746g_discovery_sdram.c \
../Drivers/BSP/src/stm32746g_discovery_ts.c 

OBJS += \
./Drivers/BSP/src/font12.o \
./Drivers/BSP/src/font16.o \
./Drivers/BSP/src/font20.o \
./Drivers/BSP/src/font24.o \
./Drivers/BSP/src/font8.o \
./Drivers/BSP/src/stm32746g_discovery.o \
./Drivers/BSP/src/stm32746g_discovery_lcd.o \
./Drivers/BSP/src/stm32746g_discovery_sdram.o \
./Drivers/BSP/src/stm32746g_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/src/font12.d \
./Drivers/BSP/src/font16.d \
./Drivers/BSP/src/font20.d \
./Drivers/BSP/src/font24.d \
./Drivers/BSP/src/font8.d \
./Drivers/BSP/src/stm32746g_discovery.d \
./Drivers/BSP/src/stm32746g_discovery_lcd.d \
./Drivers/BSP/src/stm32746g_discovery_sdram.d \
./Drivers/BSP/src/stm32746g_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/src/%.o: ../Drivers/BSP/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/BSP/inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/system" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/netif" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/posix" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/system/arch" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


