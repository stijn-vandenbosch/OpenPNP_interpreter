################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/core/altcp.c \
../Middlewares/Third_Party/LwIP/src/core/altcp_alloc.c \
../Middlewares/Third_Party/LwIP/src/core/altcp_tcp.c \
../Middlewares/Third_Party/LwIP/src/core/def.c \
../Middlewares/Third_Party/LwIP/src/core/dns.c \
../Middlewares/Third_Party/LwIP/src/core/inet_chksum.c \
../Middlewares/Third_Party/LwIP/src/core/init.c \
../Middlewares/Third_Party/LwIP/src/core/ip.c \
../Middlewares/Third_Party/LwIP/src/core/mem.c \
../Middlewares/Third_Party/LwIP/src/core/memp.c \
../Middlewares/Third_Party/LwIP/src/core/netif.c \
../Middlewares/Third_Party/LwIP/src/core/pbuf.c \
../Middlewares/Third_Party/LwIP/src/core/raw.c \
../Middlewares/Third_Party/LwIP/src/core/stats.c \
../Middlewares/Third_Party/LwIP/src/core/sys.c \
../Middlewares/Third_Party/LwIP/src/core/tcp.c \
../Middlewares/Third_Party/LwIP/src/core/tcp_in.c \
../Middlewares/Third_Party/LwIP/src/core/tcp_out.c \
../Middlewares/Third_Party/LwIP/src/core/timeouts.c \
../Middlewares/Third_Party/LwIP/src/core/udp.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/core/altcp.o \
./Middlewares/Third_Party/LwIP/src/core/altcp_alloc.o \
./Middlewares/Third_Party/LwIP/src/core/altcp_tcp.o \
./Middlewares/Third_Party/LwIP/src/core/def.o \
./Middlewares/Third_Party/LwIP/src/core/dns.o \
./Middlewares/Third_Party/LwIP/src/core/inet_chksum.o \
./Middlewares/Third_Party/LwIP/src/core/init.o \
./Middlewares/Third_Party/LwIP/src/core/ip.o \
./Middlewares/Third_Party/LwIP/src/core/mem.o \
./Middlewares/Third_Party/LwIP/src/core/memp.o \
./Middlewares/Third_Party/LwIP/src/core/netif.o \
./Middlewares/Third_Party/LwIP/src/core/pbuf.o \
./Middlewares/Third_Party/LwIP/src/core/raw.o \
./Middlewares/Third_Party/LwIP/src/core/stats.o \
./Middlewares/Third_Party/LwIP/src/core/sys.o \
./Middlewares/Third_Party/LwIP/src/core/tcp.o \
./Middlewares/Third_Party/LwIP/src/core/tcp_in.o \
./Middlewares/Third_Party/LwIP/src/core/tcp_out.o \
./Middlewares/Third_Party/LwIP/src/core/timeouts.o \
./Middlewares/Third_Party/LwIP/src/core/udp.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/core/altcp.d \
./Middlewares/Third_Party/LwIP/src/core/altcp_alloc.d \
./Middlewares/Third_Party/LwIP/src/core/altcp_tcp.d \
./Middlewares/Third_Party/LwIP/src/core/def.d \
./Middlewares/Third_Party/LwIP/src/core/dns.d \
./Middlewares/Third_Party/LwIP/src/core/inet_chksum.d \
./Middlewares/Third_Party/LwIP/src/core/init.d \
./Middlewares/Third_Party/LwIP/src/core/ip.d \
./Middlewares/Third_Party/LwIP/src/core/mem.d \
./Middlewares/Third_Party/LwIP/src/core/memp.d \
./Middlewares/Third_Party/LwIP/src/core/netif.d \
./Middlewares/Third_Party/LwIP/src/core/pbuf.d \
./Middlewares/Third_Party/LwIP/src/core/raw.d \
./Middlewares/Third_Party/LwIP/src/core/stats.d \
./Middlewares/Third_Party/LwIP/src/core/sys.d \
./Middlewares/Third_Party/LwIP/src/core/tcp.d \
./Middlewares/Third_Party/LwIP/src/core/tcp_in.d \
./Middlewares/Third_Party/LwIP/src/core/tcp_out.d \
./Middlewares/Third_Party/LwIP/src/core/timeouts.d \
./Middlewares/Third_Party/LwIP/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/core/%.o: ../Middlewares/Third_Party/LwIP/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DUSE_HAL_DRIVER -DSTM32F746xx -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/BSP/inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/system" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/STM32F7xx_HAL_Driver/Inc" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/netif" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/system/arch" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Drivers/CMSIS/Include" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"D:/Documenten/STM32/EmbeddedSystems/OpenPNP_Interpreter/Middlewares/Third_Party/LwIP/src/include/compat/stdc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


