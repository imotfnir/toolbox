export REPO_DIR := $(shell pwd)
export INCLUDE_DIR = $(REPO_DIR)/include
export SRC_DIR = $(REPO_DIR)/src
export TEST_DIR = $(REPO_DIR)/test
export TOOLS_DIR = $(REPO_DIR)/tools
export BUILD_DIR = $(REPO_DIR)/build
export OUT_OBJS_DIR = $(BUILD_DIR)

MAKE = make
RM = rm -f
CP = cp

all: dirs pcie_tools

rebuild: clean all

pcie_tools:
	$(MAKE) -C $@
	$(CP) $(BUILD_DIR)/pcie_tools pcie_tools.bin

dirs:
	mkdir -p $(BUILD_DIR)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) pcie_tools.bin

.PHONY: all rebuild pcie_tools clean dirs
