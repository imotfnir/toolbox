####################################################################
# Tools
####################################################################
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar
RANLIB = $(CROSS_COMPILE)ranlib
STRIP = $(CROSS_COMPILE)strip

CFLAGS += -g -O2

####################################################################
# ALL
####################################################################
TOOL_NAME="hmrfpo_enable"
TOOL_OBJS = PCIIORW.o HeciCore.o lpc_hal.o hmrfpo_enable.o

.c.o:
	$(CC) $(CFLAGS) -c $<

all: hmrfpo_enable

hmrfpo_enable: $(TOOL_OBJS)
	$(CC) $(CFLAGS) -o $(TOOL_NAME) $(TOOL_OBJS)

clean:
	rm -fr *.o
	rm -fr ${TOOL_NAME}

install: all
	install ${TOOL_NAME} ${OUTPUT_SBIN_DIR}

.PHONY: clean
