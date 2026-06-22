WIRELESS_ENABLE ?= yes
WIRELESS_DIR = $(TOP_DIR)/keyboards/epomaker/tide49/linker/wireless

ifeq ($(strip $(WIRELESS_ENABLE)), yes)
    OPT_DEFS += -DWIRELESS_ENABLE -DNO_USB_STARTUP_CHECK

    # quantum/via.c calls raw_hid_send() directly to forward HID reports.
    # Redirect just that one translation unit to our wireless-aware
    # replaced_hid_send() so quantum/raw_hid.c's USB-only implementation is
    # left untouched (no core files modified, no symbol clash).
    $(INTERMEDIATE_OUTPUT)/quantum/via.o: FILE_SPECIFIC_CFLAGS += -Draw_hid_send=replaced_hid_send

    UART_DRIVER_REQUIRED ?= yes
    WIRELESS_LPWR_STOP_ENABLE ?= yes

    VPATH += $(WIRELESS_DIR)

    SRC += \
        $(WIRELESS_DIR)/wireless.c \
        $(WIRELESS_DIR)/transport.c \
        $(WIRELESS_DIR)/lowpower.c \
        $(WIRELESS_DIR)/md_raw.c \
        $(WIRELESS_DIR)/smsg.c \
        $(WIRELESS_DIR)/module.c

    ifeq ($(strip $(WIRELESS_LPWR_STOP_ENABLE)), yes)
        OPT_DEFS += -DWIRELESS_LPWR_STOP_ENABLE
        SRC += $(WIRELESS_DIR)/lpwr_wb32.c
    endif
endif
