WIRELESS_ENABLE ?= yes
ifeq ($(strip $(WIRELESS_ENABLE)), yes)
SRC += wls/wls.c
endif
