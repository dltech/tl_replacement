PROJECT = tl494_replacement
BUILD_DIR = bin

SHARED_DIR = ../lib
CFILES = main.c
CFILES += board.c
CFILES += display.c
CFILES += measure.c
CFILES += tl.c
CFILES += charger.c
CFILES += menu.c
CFILES += time.c
CFILES += buttons.c
CFILES += settings.c


# TODO - you will need to edit these two lines!
DEVICE=stm32f030F4P6
OOCD_FILE = board/stm32f0discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
