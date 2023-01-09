MAJOR = 0
MINOR = 2
PATCH = 0
SEM_VER = $(MAJOR).$(MINOR).$(PATCH)
TOOLS = pcie_tools io_tools ioget ioset

ifeq "$(PATCH)" "0"
	DEBUG_LEVEL := 3
	IS_TRACE := false
else
	DEBUG_LEVEL := 7
	IS_TRACE := true
endif

MARCO =\
DEBUG_LEVEL=$(DEBUG_LEVEL)\
MAJOR=$(MAJOR)\
MINOR=$(MINOR)\
PATCH=$(PATCH)\
IS_TRACE=$(IS_TRACE)\
SEM_VER=$(SEM_VER)\
