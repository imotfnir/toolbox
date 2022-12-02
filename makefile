export repo_dir := $(shell pwd)/
export include_dir = $(repo_dir)include/
export src_dir = $(repo_dir)src/
export library_dir = $(repo_dir)library/
export test_dir = $(repo_dir)test/
export tools_dir = $(repo_dir)tools/
export build_dir = $(repo_dir)build/
export out_objs_dir = $(build_dir)objs/

MAKE = make
RM = rm -f
CP = cp

INSTALL_DIR = /usr/local/bin/

vpath pcie_tools $(build_dir)

all: pcie_tools.bin

install: all
	$(CP) $(INSTALL_DIR)pcie_tools

uninstall:
	$(RM) $(INSTALL_DIR)pcie_tools

rebuild: clean all

clean:
	$(RM) -r $(build_dir)
	$(RM) pcie_tools.bin

pcie_tools: $(build_dir) $(out_objs_dir)
	$(MAKE) -C $@

pcie_tools.bin: pcie_tools
	$(CP) $(build_dir)pcie_tools $(repo_dir)$@

$(build_dir):
	mkdir -p $@

$(out_objs_dir):
	mkdir -p $@

.PHONY: all rebuild clean uninstall install
