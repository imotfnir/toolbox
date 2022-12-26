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
export repo_dir := $(PWD)
export include_dir = $(repo_dir)/include
export src_dir = $(repo_dir)/src
export library_dir = $(repo_dir)/library
export test_dir = $(repo_dir)/test
export tools_dir = $(repo_dir)/tools
export build_dir = $(repo_dir)/build
export install_dir = /usr/local/bin

# Vpath
vpath %.c $(src_dir) $(library_dir)
vpath %.h $(include_dir)
VPATH = $(build_dir)

# Flags
CFLAGS = -g -O3 -Wall #--save-temp
INCS = $(include_dir)
MARCO = DEBUG_LEVEL=$(DEBUG_LEVEL) MAJOR=$(MAJOR) MINOR=$(MINOR) PATCH=$(PATCH) IS_TRACE=$(IS_TRACE)
INCFLAG = $(foreach d, $(INCS)/, -I$d)
MARCOFLAG = $(foreach d, $(MARCO), -D$d)

# Files
LIB_FILES = $(wildcard $(library_dir)/*.c)
LIBS = $(notdir $(LIB_FILES))
OBJS = $(LIBS:.c=.o)
DEPS = $(LIBS:.c=.d)
OBJ_FILES = $(addprefix $(build_dir)/, $(OBJS))
DEP_FILES = $(addprefix $(build_dir)/, $(DEPS))

all: $(build_dir) pcie_tools io_tools

install: all
	$(CP) $(install_dir)/pcie_tools

uninstall:
	$(RM) $(install_dir)/pcie_tools

rebuild: clean all

clean:
	$(RM) -r $(build_dir)/
	$(RM) pcie_tools io_tools

pcie_tools: pcie_tools.c $(OBJ_FILES)
io_tools: io_tools.c $(OBJ_FILES)
pcie_tools io_tools:
	$(CC) $(CFLAGS) $(INCFLAG) $(MARCOFLAG) $(filter-out %.h, $^) -o $(build_dir)/$@
	$(CP) $(build_dir)/$@ $(repo_dir)/$@

$(build_dir)/io_lib.o: io_lib.c io_lib.h $(build_dir)/debug_lib.o
$(build_dir)/debug_lib.o: debug_lib.c debug_lib.h
$(build_dir)/debug_lib.o $(build_dir)/io_lib.o:
	$(CC) $(CFLAGS) $(INCFLAG) $(MARCOFLAG) -c $< -o $@

$(build_dir):
	$(MKDIR) $@

debug:
	@echo LIB_FILES = $(LIB_FILES)
	@echo OBJ_FILES = $(OBJ_FILES)
	@echo DEP_FILES = $(DEP_FILES)
	@echo LIBS = $(LIBS)
	@echo OBJS = $(OBJS)
	@echo DEPS = $(DEPS)

.PHONY: all rebuild clean uninstall install test debug
