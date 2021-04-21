################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Analog\ Devices/CrossCore\ Embedded\ Studio\ 2.9.4/Blackfin/lib/src/drivers/source/spi/adi_spi.c 

SRC_OBJS += \
./system/drivers/spi/adi_spi.doj 

C_DEPS += \
./system/drivers/spi/adi_spi.d 


# Each subdirectory must supply rules for building sources it contributes
system/drivers/spi/adi_spi.doj: C:/Analog\ Devices/CrossCore\ Embedded\ Studio\ 2.9.4/Blackfin/lib/src/drivers/source/spi/adi_spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn -c -file-attr ProjectName="Master" -proc ADSP-BF537 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-27d490b83e24dd5cbd83fbc990f628ce.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "system/drivers/spi/adi_spi.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


