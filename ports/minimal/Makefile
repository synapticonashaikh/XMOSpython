#include the python envirmental variables
include ../../py/mkenv.mk

#to build for either STM board or Linux env
CROSS = 0

#enable/ disable debugg message 
ENABLE_DISABLE_DEBUGG_MESSAGE = 1

#enable/ disable float functionality
ENABLE_DISABLE_FLOAT = 0

#enable/ disable self created module
ENABLE_DISABLE_OWN_MODULE = 0

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 1

#C standard library
_C_STD_LIB = -std=c99

#board linking file 
_BOARD_LINKING_FILE = stm32_flash.ld #stm32f405.ld

# include py core make definitions
include $(TOP)/py/py.mk

#check if the CROSS is enable
ifeq ($(CROSS), 1)
CROSS_COMPILE ?= arm-none-eabi-
endif

#print of the debugg is enable
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: Debugg message enable!)
endif

#include the all required path
INC += -I.
INC += -I$(TOP)
INC += -I$(BUILD)

#print of the debugg is enable
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: INC paths are $(INC))
endif


#if the CROSS = 1 build add the compilation and linking flag
ifeq ($(CROSS), 1)
#python code to build the firmware file for stm32
DFU = $(TOP)/tools/dfu.py
PYDFU = $(TOP)/tools/pydfu.py
#check and add the float related functionality
ifeq ($(ENABLE_DISABLE_FLOAT), 1)
#add the ARM core flags
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: Compliation Flag, float is enabled!)
$(info Debugg: Size of the output file will be increased!)
endif
#note* -mfloat-abi=hard is not working
# MICROPY_FLOAT_IMPL_FLOAT for float and MICROPY_FLOAT_IMPL_NONE to remove float functionality
#c standard library can be changed to -std=gnu99, -std=c11 
CFLAGS_CORTEX_M4 = -mthumb -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=soft -fsingle-precision-constant -Wdouble-promotion -Wfloat-conversion
CFLAGS += -DMICROPY_FLOAT_IMPL=MICROPY_FLOAT_IMPL_FLOAT
CFLAGS += $(INC) -Wall -Werror -nostdlib -Wpointer-arith $(_C_STD_LIB) $(CFLAGS_CORTEX_M4) $(COPT)
else
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Compliation Flag, float is disabled)
endif
CFLAGS_CORTEX_M4 = -mthumb -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=soft -fsingle-precision-constant -Wdouble-promotion -Wfloat-conversion
CFLAGS += $(INC) -Wall -Werror -nostdlib -Wpointer-arith $(_C_STD_LIB) $(CFLAGS_CORTEX_M4) $(COPT)
endif
LDFLAGS += -nostdlib -T $(_BOARD_LINKING_FILE) -Map=$@.map --cref --gc-sections
else
#compiler for linux enviroment 
LD = gcc
CFLAGS += $(INC) -Wall -Werror -Wdouble-promotion -Wfloat-conversion $(_C_STD_LIB) $(COPT)
LDFLAGS += -Wl,-Map=$@.map,--cref -Wl,--gc-sections
endif

CSUPEROPT = -Os # save some code space

# Tune for Debugging or Optimization
CFLAGS += -g  # always include debug info in the ELF
ifeq ($(DEBUG), 1)
CFLAGS += -O0
else
CFLAGS += -Os -DNDEBUG
CFLAGS += -fdata-sections -ffunction-sections
endif

# Flags for optional C++ source code
CXXFLAGS += $(filter-out $(_C_STD_LIB),$(CFLAGS))

ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: The compliation flags are $(CFLAGS)) 
$(info Debugg: Compiler is $(CC)) 
endif

ifeq ($(ENABLE_DISABLE_FLOAT), 1)
LIBS += "$(shell $(CC) $(CFLAGS) -print-libgcc-file-name)"
#adding the python library
SRC_LIB += $(addprefix lib/,\
        libm/math.c \
        libm/fmodf.c \
        libm/nearbyintf.c \
        libm/ef_sqrt.c \
        libm/kf_rem_pio2.c \
        libm/kf_sin.c \
        libm/kf_cos.c \
        libm/kf_tan.c \
        libm/ef_rem_pio2.c \
        libm/sf_sin.c \
        libm/sf_cos.c \
        libm/sf_tan.c \
        libm/sf_frexp.c \
        libm/sf_modf.c \
        libm/sf_ldexp.c \
        libm/asinfacosf.c \
        libm/acoshf.c \
        libm/asinhf.c \
        libm/atanf.c \
        libm/atan2f.c \
        libm/atanhf.c \
        libm/log1pf.c \
        libm/sf_erf.c \
        libm/erf_lgamma.c \
        libm/wf_lgamma.c \
        libm/wf_tgamma.c \
        libm/roundf.c \
	)
LIBM_O = $(addprefix $(BUILD)/, $(SRC_LIB:.c=.o))
else
LIBS = 
endif
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: float library path is $(LIBS)) 
endif

SRC_C = \
	main.c \
	uart_core.c \
	STdriver.c \
	shared/libc/printf.c \
	shared/readline/readline.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \
	$(BUILD)/_frozen_mpy.c \

ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_C += modmyport.c 
endif        

ifeq ($(CROSS), 1)
SRC_C += shared/libc/string0.c
endif

#add the library for reading the commands at interpretor
SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_QSTR += modmyport.c
endif

OBJ += $(PY_CORE_O)
ifeq ($(ENABLE_DISABLE_FLOAT), 1)
OBJ += $(LIBM_O)
endif
OBJ += $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_CXX:.cpp=.o))

ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: Final build info)
$(info Debugg: PYTHON is $(PYTHON))
$(info Debugg: Q is $(Q))
$(info Debugg: LD is $(LD))
$(info Debugg: LDFLAGS is $(LDFLAGS))
$(info Debugg: LIBS is $(LIBS))
$(info Debugg: SIZE is $(SIZE))
$(info Debugg: CC is $(CC))
$(info Debugg: GEN is $(GEN))
$(info Debugg: CMD is $(Q)$(LD) $(LDFLAGS) -o $(LIBS))
$(info Debugg: OBJCOPY is $(OBJCOPY))
$(info Debugg: BIN is $(Q)$(OBJCOPY) -O binary -j .isr_vector -j .text -j .data -o $(BUILD)/firmware.bin)
#$(info Debugg: OBJ is $(OBJ))
endif   


ifeq ($(CROSS), 1)
all: $(BUILD)/firmware.dfu
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: Building all $(BUILD)/firmware.dfu )
endif
else
all: $(BUILD)/firmware.elf
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
$(info Debugg: Building all $(BUILD)/firmware.elf )
endif
endif

$(BUILD)/_frozen_mpy.c: $(TOP)/tests/frozen/frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@    

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

$(BUILD)/firmware.bin: $(BUILD)/firmware.elf
	$(Q)$(OBJCOPY) -O binary -j .isr_vector -j .text -j .data $^ $(BUILD)/firmware.bin

$(BUILD)/firmware.dfu: $(BUILD)/firmware.bin
	$(ECHO) "Create $@"
	$(Q)$(PYTHON) $(DFU) -b 0x08000000:$(BUILD)/firmware.bin $@

deploy: $(BUILD)/firmware.dfu
	$(ECHO) "Writing $< to the board"
	$(Q)$(PYTHON) $(PYDFU) -u $<

# Run emulation build on a POSIX system with suitable terminal settings
run:
	@saved_=`stty -g`; \
	  stty raw opost -echo; \
	  $(BUILD)/firmware.elf; \
	  echo "Exit status: $$?"; \
	  stty $$saved_

test: $(BUILD)/firmware.elf
	$(Q)/bin/echo -e "print('hello world!', list(x+1 for x in range(10)), end='eol\\\\n')\\r\\n\\x04" | $(BUILD)/firmware.elf | tail -n2 | grep "^hello world! \\[1, 2, 3, 4, 5, 6, 7, 8, 9, 10\\]eol"


include $(TOP)/py/mkrules.mk
