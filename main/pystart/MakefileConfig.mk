
#define root locations
ROOTL = ../../

#define the distribution location
MODULEL   = ../modules/
HARDWAREL = ../hardware/
HEADERSL  = ../headers/

#enable/ disable debugg message 
ENABLE_DISABLE_DEBUGG_MESSAGE = 0

#enable/ disable self created modules 
ENABLE_DISABLE_OWN_MODULE = 0

#enable/ disable float functionality
ENABLE_DISABLE_FLOAT_FUNCTIONALITY = 0

#enable/ disable float functionality
#PROCESSING_FLAG = -DREMOVE_PROCESSING_TIME

#define the code version
#for the terminal interperter use DCODE_WITH_PYTHON_INTRACTIVE_TERMINAL
#without terminal use DCODE_WITHOUT_PYTHON_INTRACTIVE_TERMINAL
DEFINE_CODE_VERSION=-DCODE_WITHOUT_PYTHON_INTRACTIVE_TERMINAL

# MICROPY_FLOAT_IMPL_NONE MICROPY_FLOAT_IMPL_FLOAT MICROPY_FLOAT_IMPL_DOUBLE 
ifeq ($(ENABLE_DISABLE_FLOAT_FUNCTIONALITY), 1)
FLOAT_FLAG=-DMICROPY_FLOAT_IMPL=MICROPY_FLOAT_IMPL_FLOAT
else
FLOAT_FLAG=-DMICROPY_FLOAT_IMPL=MICROPY_FLOAT_IMPL_NONE
endif

#supoort folder (generated header folder)
BUILD_DIR = build

XCTarget = ../targets/C2X.xn

#define the compiler
CMP = xcc -target= $(XCTarget)
#xflash --verbose --target XCORE-200-EXPLORER --boot-partition-size 0x90000  output.xe

#include the all required path
INC += -I.
INC += -I$(ROOTL)
INC += -I$(HEADERSL)
INC += -I$(BUILD_DIR)
INC += -I$(BUILD_DIR)/genhdr/

#flags with respect to XMOS core
LDFLAGS = -Wno-unused-variable -Wno-xcore-fptrgroup -Os -report $(INC) $(DEFINE_CODE_VERSION) $(FLOAT_FLAG) $(PROCESSING_FLAG)
