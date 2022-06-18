##
# @author Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
# @version 0.1
#
# @copyright Copyright Cristóvão Zuppardo Rufino (c) 2022
# Please see LICENCE file to information regarding licensing


TARGET = hw-totp-fw

# Debug build?
DEBUG = 1

# Build path
BUILD_DIR = /tmp/build/

# Binaries
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
BIN = $(CP) -O binary -S

# Source files
# C sources
C_SOURCES += \
	src/main.c \
	src/hw_init.c

C_SOURCES += \
	external/STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c \
	external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_gpio.c \
	external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usart.c \
	external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rcc.c \
	external/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c


# AS sources
ASM_SOURCES += \
	external/STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s

# MCU
MCU = -mcpu=cortex-m3 -mthumb

# AS defines
AS_DEFS +=

# AS includes
AS_INCLUDES += \
	-I. \
	-Iexternal/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc \
	-Iexternal/STM32CubeF1/Drivers/CMSIS/Include \
	-Iexternal/STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Include

AS_INCLUDES +=

# AS flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) -Wall -fdata-sections -ffunction-sections

# C defines
C_DEFS += \
	-DUSE_FULL_LL_DRIVER \
	-DHSE_VALUE=8000000 \
	-DHSE_STARTUP_TIMEOUT=100 \
	-DLSE_STARTUP_TIMEOUT=5000 \
	-DLSE_VALUE=32768 \
	-DHSI_VALUE=8000000 \
	-DLSI_VALUE=40000 \
	-DVDD_VALUE=3300 \
	-DPREFETCH_ENABLE=1 \
	-DSTM32F103xB

# C includes
C_INCLUDES += \
	-I. \
	-Iexternal/STM32CubeF1/Drivers/STM32F1xx_HAL_Driver/Inc \
	-Iexternal/STM32CubeF1/Drivers/CMSIS/Include \
	-Iexternal/STM32CubeF1/Drivers/CMSIS/Device/ST/STM32F1xx/Include

# C flags
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -O0 -ggdb -Werror
else
CFLAGS += -Os
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# Link script
LDSCRIPT = src/STM32F103C8_FLASH.ld

# Libraries
LIBS = -lc -lm -lnosys
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) \
	-Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# Default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# Build the application
# List of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# List of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@
	
$(BUILD_DIR):
	mkdir -pv $@

# Flashes built code to microcontroller
write:
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x08000000

clean:
	-rm -fR $(BUILD_DIR)
  
-include $(wildcard $(BUILD_DIR)/*.d)