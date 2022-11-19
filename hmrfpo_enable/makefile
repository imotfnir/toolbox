####################################################################
# Variable
####################################################################
MAJOR := 1
MINOR := 6
PATCH := 1
SEM_VER := v$(MAJOR).$(MINOR).$(PATCH)
VERSION := \"$(SEM_VER)\"
TOOL_NAME = hmrfpo_enable_$(SEM_VER)
TOOL_OBJS = PCIIORW.o HeciCore.o lpc_hal.o hmrfpo_enable.o
####################################################################
# Tools and Flags
####################################################################
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
AR := $(CROSS_COMPILE)ar
RANLIB := $(CROSS_COMPILE)ranlib
STRIP := $(CROSS_COMPILE)strip

CFLAGS += -g -O2 --save-temps
CFLAGS += -DVERSION=$(VERSION)

####################################################################
# Build
####################################################################
.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(TOOL_NAME)

rebuild: clean all

${TOOL_NAME}: $(TOOL_OBJS)
	$(CC) $(CFLAGS) -o $(TOOL_NAME) $(TOOL_OBJS)

clean:
	rm -fr *.o *.i *.s
	rm -fr ${TOOL_NAME}

install: all
	install ${TOOL_NAME} ${OUTPUT_SBIN_DIR}

.PHONY: clean
