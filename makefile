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
TOOLS = pcie_tools io_tools

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
OBJ_FILES = $(LIBS:%.c=$(build_dir)/%.o)
DEP_FILES = $(LIBS:%.c=$(build_dir)/%.d) $(TOOLS:%=$(build_dir)/%.d)

# include other makefile

all: $(build_dir) $(TOOLS)

rebuild: clean all

install: all
	$(CP) $(install_dir)/pcie_tools

uninstall:
	$(RM) $(install_dir)/pcie_tools

clean:
	$(RM) -r $(build_dir)/
	$(RM) $(TOOLS)

$(TOOLS): %: $(build_dir)/%.o $(OBJ_FILES)
	$(CC) $^ -o $@

$(build_dir)/%.o:
	$(CC) $(CFLAGS) $(INCFLAG) $(MARCOFLAG) -c $< -o $@

$(build_dir)/%.d: %.c
	$(MKDIR) $(build_dir)
	$(CC) $(INCFLAG) -MM $< -MF $@ -MT '$(patsubst %.d,%.o,$@) $@'

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

-include $(DEP_FILES)