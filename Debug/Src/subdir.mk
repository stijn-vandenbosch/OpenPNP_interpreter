################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/actuators.c \
../Src/buttons.c \
../Src/coms.c \
../Src/ethernetif.c \
../Src/gcode.c \
../Src/lwip.c \
../Src/main.c \
../Src/motion.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/actuators.o \
./Src/buttons.o \
./Src/coms.o \
./Src/ethernetif.o \
./Src/gcode.o \
./Src/lwip.o \
./Src/main.o \
./Src/motion.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/actuators.d \
./Src/buttons.d \
./Src/coms.d \
./Src/ethernetif.d \
./Src/gcode.d \
./Src/lwip.d \
./Src/main.d \
./Src/motion.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DUSE_HAL_DRIVER -DSTM32F746xx -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/BSP/inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/system" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/netif" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/system/arch" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/CMSIS/Include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/stdc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


