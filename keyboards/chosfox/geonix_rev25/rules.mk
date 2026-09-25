BOARD = FS026
MCU = cortex-m0
ARMV = 6
MCU_FAMILY = ES32
MCU_SERIES = FS026
MCU_LDSCRIPT ?= FS026
MCU_STARTUP ?= FS026
USE_FPU ?= no

EEPROM_CUSTOM = custom
EEPROM_DRIVER = custom
NO_USB_STARTUP_CHECK = yes
BLUETOOTH_CUSTOM = yes

# Opt out of closed-source library; use open-source rdmctmzt_common instead
NO_CLOSED_SOURCE_LIB = yes

# Include open-source common library
VPATH += lib/rdmctmzt_common
EXTRAINCDIRS += $(TOP_DIR)/lib/rdmctmzt_common
SRC += rdmctmzt_common.c \
	keyboard_common.c \
	three_mode.c \
	user_battery.c \
	user_eeprom.c \
	user_emi.c \
	user_led_custom.c \
	user_led_zone.c \
	user_logo_led.c \
	user_spi.c \
	user_system.c

# Include dynamic keymap support
SRC += quantum/dynamic_keymap.c

# Include FS026 SPI driver
VPATH += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md
SRC += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md/md_spi.c

RAW_ENABLE = yes
