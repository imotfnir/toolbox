# Environment Variable
export MAKE = make
export RM = rm -f
export CP = cp
export MKDIR = mkdir -p
export CC = $(CROSS_COMPILE)gcc
export LD = $(CROSS_COMPILE)ld
export AR = $(CROSS_COMPILE)ar
export SHELL = /bin/sh
DEBUG_LEVEL = 7
IS_TRACE = true
MAJOR = 0
MINOR = 0
PATCH = 1
SEM_VER = $(MAJOR).$(MINOR).$(PATCH)
PCIE_TOOLS = pcie_tools
IO_TOOLS = io_tools

# Directory
export repo_dir := $(shell pwd)/
export include_dir = $(repo_dir)include/
export src_dir = $(repo_dir)src/
export library_dir = $(repo_dir)library/
export test_dir = $(repo_dir)test/
export tools_dir = $(repo_dir)tools/
export build_dir = $(repo_dir)build/
export objs_dir = $(build_dir)objs/
export INSTALL_DIR = /usr/local/bin/

# Vpath
vpath pcie_tools $(build_dir)
vpath io_tools $(build_dir)
vpath %.o $(objs_dir)
vpath %.c $(src_dir) $(library_dir)
vpath %.h $(include_dir)
VPATH = $(objs_dir)

# Flags
CFLAGS = -g -O3 -Wall #--save-temp
incs_dir = $(include_dir)
marco = DEBUG_LEVEL=$(DEBUG_LEVEL) MAJOR=$(MAJOR) MINOR=$(MINOR) PATCH=$(PATCH) IS_TRACE=$(IS_TRACE)
incs_param = $(foreach d, $(incs_dir), -I$d)
marco_param = $(foreach d, $(marco), -D$d)
OBJS = $(objs_dir)io_lib.o $(objs_dir)debug_lib.o


all: $(objs_dir) pcie_tools io_tools

install: all
	$(CP) $(INSTALL_DIR)pcie_tools

uninstall:
	$(RM) $(INSTALL_DIR)pcie_tools

rebuild: clean all

clean:
	$(RM) -r $(build_dir)
	$(RM) pcie_tools io_tools

pcie_tools: pcie_tools.c $(OBJS)
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) $^ -o $(build_dir)$@
	$(CP) $(build_dir)$@ $(repo_dir)$@

io_tools: io_tools.c $(OBJS)
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) $^ -o $(build_dir)$@
	$(CP) $(build_dir)$@ $(repo_dir)$@

$(objs_dir)io_lib.o: io_lib.c io_lib.h $(objs_dir)debug_lib.o
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) -c $< -o $@

$(objs_dir)debug_lib.o: debug_lib.c debug_lib.h
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) -c $< -o $@

$(objs_dir):
	$(MKDIR) $@

debug:
	@echo $(VPATH)




.PHONY: all rebuild clean uninstall install test debug
