export repo_dir := $(shell pwd)/
export include_dir = $(repo_dir)include/
export src_dir = $(repo_dir)src/
export library_dir = $(repo_dir)library/
export test_dir = $(repo_dir)test/
export tools_dir = $(repo_dir)tools/
export build_dir = $(repo_dir)build/
export out_objs_dir = $(build_dir)objs/

export MAKE = make
export RM = rm -f
export CP = cp
export CC = $(CROSS_COMPILE)gcc
export LD = $(CROSS_COMPILE)ld
export AR = $(CROSS_COMPILE)ar
export SHELL = /bin/sh

export INSTALL_DIR = /usr/local/bin/

vpath pcie_tools $(build_dir)
vpath io_tools $(build_dir)

all: cp_execute

install: all
	$(CP) $(INSTALL_DIR)pcie_tools

uninstall:
	$(RM) $(INSTALL_DIR)pcie_tools

rebuild: clean all

clean:
	$(RM) -r $(build_dir)
	$(RM) pcie_tools io_tools

pcie_tools: $(build_dir) $(out_objs_dir)
	$(MAKE) -C $(src_dir) $@

io_tools: $(build_dir) $(out_objs_dir)
	$(MAKE) -C $(src_dir) $@

cp_execute: pcie_tools io_tools
	$(CP) $(build_dir)io_tools $(repo_dir)io_tools
	$(CP) $(build_dir)pcie_tools $(repo_dir)pcie_tools

$(build_dir):
	mkdir -p $@

$(out_objs_dir):
	mkdir -p $@

.PHONY: all rebuild clean uninstall install
