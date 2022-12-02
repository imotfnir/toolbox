# Environment Variable
DEBUG_LEVEL = 4
MAJOR = 0
MINOR = 0
PATCH = 1
SEM_VER = $(MAJOR).$(MINOR).$(PATCH)
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar
RM = rm -f
SHELL = /bin/sh
TOOLS_NAME = pcie_tools

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
pcie_tools_dir = $(repo_dir)$(TOOLS_NAME)/

VPATH = $(src_dir) $(build_dir) $(include_dir)
vpath %.c $(library_dir)
vpath %.c $(src_dir)
vpath %.o $(out_objs_dir)
vpath %.h $(include_dir)

# Files
target = $(TOOLS_NAME)
srcs = $(wildcard $(src_dir)*.c)
libs = $(wildcard $(library_dir)*.c)
objs += $(addprefix $(out_objs_dir),$(notdir $(subst .c,.o,$(srcs))))
objs += $(addprefix $(out_objs_dir),$(notdir $(subst .c,.o,$(libs))))

# Flags
CFLAGS = -g -O3 --save-temp -Wall
incs = $(include_dir)
marco = DEBUG_LEVEL=$(DEBUG_LEVEL) MAJOR=$(MAJOR) MINOR=$(MINOR) PATCH=$(PATCH) TOOLS_NAME=$(TOOLS_NAME)
incs_param = $(foreach d, $(incs), -I$d)
marco_param = $(foreach d, $(marco), -D$d)

# Build rule
all: $(target) $(build_dir) $(out_objs_dir)

rebuild: clean all

clean:
	$(RM) -r $(build_dir)

$(build_dir):
	mkdir -p $@

$(out_objs_dir):
	mkdir -p $@

$(target): $(objs) $(TOOLS_NAME).c
	$(CC) $(CFLAGS) $(incs_param) $(marco_param) $^ -o $(build_dir)/$@

$(objs): %.c %.h
	$(CC) $(CFLAGS) $(incs_param) -c $< -o $@

debug:
	@echo repo_dir = $(repo_dir)
	@echo srcs = $(srcs)
	@echo libs = $(libs)
	@echo objs = $(objs)

.PHONY: all clean debug rebuild
