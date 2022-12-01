# Environment Variable
DEBUG_LEVEL = 4
MAJOR = 0
MINOR = 0
PATCH = 1
SEM_VER = $(MAJOR).$(MINOR).$(PATCH)
TOOLS_NAME = pcie_tools
OUTPUT_BIN = $(TOOLS_NAME)

# Directory
ifndef REPO_DIR
	REPO_DIR := $(shell cd .. && pwd)
endif
ifndef INCLUDE_DIR
	INCLUDE_DIR = $(REPO_DIR)/include
endif
ifndef SRC_DIR
	SRC_DIR = $(REPO_DIR)/src
endif
ifndef TEST_DIR
	TEST_DIR = $(REPO_DIR)/test
endif
ifndef TOOLS_DIR
	TOOLS_DIR = $(REPO_DIR)/tools
endif
ifndef BUILD_DIR
	BUILD_DIR = $(REPO_DIR)/build
endif
ifndef OUT_OBJS_DIR
	OUT_OBJS_DIR = $(BUILD_DIR)
endif
PCIE_TOOLS_DIR = $(REPO_DIR)/$(TOOLS_NAME)

VPATH = $(SRC_DIR) $(BUILD_DIR) $(INCLUDE_DIR)
vpath %.c $(SRC_DIR)
vpath %.o $(OUT_OBJS_DIR)
vpath %.h $(INCLUDE_DIR)

# Tools and files
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar
RM = rm -f
SRCS = $(shell cd $(SRC_DIR) && ls *.c)
OBJS = $(SRCS:.c=.o)

# Flags
FLAGS = -g -O3 --save-temp -Wall
INC = $(INCLUDE_DIR)
MARCO = DEBUG=$(DEBUG_LEVEL) MAJOR=$(MAJOR) MINOR=$(MINOR) PATCH=$(PATCH) TOOLS_NAME=$(TOOLS_NAME)
INC_PARAM = $(foreach d, $(INC), -I$d)
MARCO_PARAM = $(foreach d, $(MARCO), -D$d)

# Build rule
all: dirs $(OUTPUT_BIN)

rebuild: clean all

clean:
	$(RM) -r $(BUILD_DIR)

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OUT_OBJS_DIR)

$(OUTPUT_BIN): $(OUT_OBJS_DIR)/$(OBJS) $(TOOLS_NAME).c
	$(CC) $(FLAGS) $(INC_PARAM) $(MARCO_PARAM) $^ -o $(BUILD_DIR)/$@

$(OUT_OBJS_DIR)/%.o: %.c
	$(CC) $(FLAGS) $(INC_PARAM) -c $< -o $@

debug:
	@echo $(PCIE_TOOLS_DIR)
	@echo $(REPO_DIR)
	@echo $(INCLUDE_DIR)
	@echo $(INC_PARAM)
	@echo $(OBJS)
	@echo $(OUT_OBJS_DIR)/$(OBJS)
	@echo $(CROSS_COMPILE)

.PHONY: all clean debug dirs rebuild
