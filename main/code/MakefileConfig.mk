
#define root locations
ROOTL = ../../

#enable/ disable debugg message 
ENABLE_DISABLE_DEBUGG_MESSAGE = 0

#enable/ disable self created modules 
ENABLE_DISABLE_OWN_MODULE = 1

#enable/ disable float functionality
ENABLE_DISABLE_FLOAT_FUNCTIONALITY = 1

#define the code version
#for the terminal interperter use DCODE_WITH_PYTHON_INTRACTIVE_TERMINAL
#without terminal use DCODE_WITHOUT_PYTHON_INTRACTIVE_TERMINAL
DEFINE_CODE_VERSION=-DCODE_WITHOUT_PYTHON_INTRACTIVE_TERMINAL

# MICROPY_FLOAT_IMPL_NONE MICROPY_FLOAT_IMPL_FLOAT MICROPY_FLOAT_IMPL_DOUBLE 
FLOAT_FLAG=-DMICROPY_FLOAT_IMPL=MICROPY_FLOAT_IMPL_FLOAT


#supoort folder (generated header folder)
BUILD_DIR = build

#define the compiler
CMP = xcc -target=XCORE-200-EXPLORER

#include the all required path
INC += -I.
INC += -I../..
INC += -I$(BUILD_DIR)
INC += -I$(BUILD_DIR)/genhdr/

#flags with respect to XMOS core
LDFLAGS = -Wno-unused-variable -Wno-xcore-fptrgroup -Os -report $(INC) $(DEFINE_CODE_VERSION) $(FLOAT_FLAG)
