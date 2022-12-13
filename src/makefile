# Environment Variable
DEBUG_LEVEL = 7
IS_TRACE = true
MAJOR = 0
MINOR = 0
PATCH = 1
SEM_VER = $(MAJOR).$(MINOR).$(PATCH)
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar
RM = rm -f
SHELL = /bin/sh
PCIE_TOOLS = pcie_tools

# Directory
ifndef repo_dir
	repo_dir := $(shell cd .. && pwd)/
endif
ifndef include_dir
	include_dir = $(repo_dir)include/
endif
ifndef src_dir
	src_dir = $(repo_dir)src/
endif
ifndef library_dir
	library_dir = $(repo_dir)library/
endif
ifndef test_dir
	test_dir = $(repo_dir)test/
endif
ifndef tools_dir
	tools_dir = $(repo_dir)tools/
endif
ifndef build_dir
	build_dir = $(repo_dir)build/
endif
ifndef out_objs_dir
	out_objs_dir = $(build_dir)objs/
endif
pcie_tools_dir = $(repo_dir)$(PCIE_TOOLS)/

VPATH = $(src_dir) $(build_dir) $(include_dir)
vpath %.c $(library_dir)
vpath %.c $(src_dir)
vpath %.o $(out_objs_dir)
vpath %.h $(include_dir)

# Files

srcs_file = $(wildcard $(src_dir)*.c)
libs_file = $(wildcard $(library_dir)*.c)
objs_file += $(addprefix $(out_objs_dir),$(notdir $(subst .c,.o,$(libs_file))))
incs_file = $(wildcard $(incs_dir)*.h)
# Flags
CFLAGS = -g -O3 --save-temp -Wall
incs_dir = $(include_dir)
marco = DEBUG_LEVEL=$(DEBUG_LEVEL) MAJOR=$(MAJOR) MINOR=$(MINOR) PATCH=$(PATCH) IS_TRACE=$(IS_TRACE)
incs_param = $(foreach d, $(incs_dir), -I$d)
marco_param = $(foreach d, $(marco), -D$d)

# Build rule
all: $(build_dir) $(out_objs_dir) pcie_tools io_tools

rebuild: clean all

clean:
	$(RM) -r $(build_dir)

$(build_dir):
	mkdir -p $@

$(out_objs_dir):
	mkdir -p $@

pcie_tools: $(objs_file) pcie_tools.c
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) $^ -o $(build_dir)$@

io_tools: $(objs_file) io_tools.c
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) $^ -o $(build_dir)$@

$(out_objs_dir)io_lib.o: io_lib.c debug_lib.o debug_lib.h
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) -c $< -o $@

$(out_objs_dir)debug_lib.o: debug_lib.c debug_lib.h
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) -c $< -o $@

debug:
	@echo repo_dir = $(repo_dir)
	@echo srcs_file = $(srcs_file)
	@echo libs_file = $(libs_file)
	@echo objs_file = $(objs_file)

.PHONY: all clean debug rebuild
