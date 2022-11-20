####################################################################
# Variable
####################################################################
DEBUG_LEVEL := 2
MAJOR := 1
MINOR := 6
PATCH := 4
SEM_VER := v$(MAJOR).$(MINOR).$(PATCH)
VERSION := \"$(SEM_VER)\"
TOOL_NAME = hmrfpo_enable
OUTPUT_BIN = $(TOOL_NAME)_$(SEM_VER).bin
TOOL_OBJS = PciRwLibrary.o HeciCore.o lpc_hal.o debug_lib.o $(TOOL_NAME).o
####################################################################
# Tools and Flags
####################################################################
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
AR := $(CROSS_COMPILE)ar
RANLIB := $(CROSS_COMPILE)ranlib
STRIP := $(CROSS_COMPILE)strip

CFLAGS += -g -O2 --save-temps
CFLAGS += -DDEBUG_LEVEL=$(DEBUG_LEVEL)
CFLAGS += -DVERSION=$(VERSION)

####################################################################
# Build
####################################################################
.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(OUTPUT_BIN)

rebuild: clean all

$(OUTPUT_BIN): $(TOOL_OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT_BIN) $(TOOL_OBJS)

clean:
	rm -fr *.o *.i *.s
	rm -fr $(TOOL_NAME)_v*

.PHONY: clean
