#define root locations
ROOTL = ../../

#to build for either STM board or Linux env
CROSS = 1

#include the python envirmental variables
#include $(ROOTL)py/mkenv.mk
include ../../py/mkenv.mk

#enable/ disable debugg message 
ENABLE_DISABLE_DEBUGG_MESSAGE = 0

ENABLE_DISABLE_OWN_MODULE = 1

#define the code version
#for the terminal interperter use DCODE_WITH_PYTHON_INTRACTIVE_TERMINAL
#without terminal use DCODE_WITHOUT_PYTHON_INTRACTIVE_TERMINAL
DEFINE_CODE_VERSION=-DCODE_WITHOUT_PYTHON_INTRACTIVE_TERMINAL

# MICROPY_FLOAT_IMPL_NONE MICROPY_FLOAT_IMPL_FLOAT MICROPY_FLOAT_IMPL_DOUBLE 
FLOAT_FLAG=-DMICROPY_FLOAT_IMPL=MICROPY_FLOAT_IMPL_FLOAT

#output and supoort folder 
BUILD_DIR = build


CMP = xcc -target=XCORE-200-EXPLORER
#-Wno-xcore-fptrgroup
#include the all required path
INC += -I.
INC += -I../..
INC += -I$(BUILD_DIR)
INC += -I$(BUILD_DIR)/genhdr/

#flags with respect to XMOS core
LDFLAGS = -Wno-unused-variable -Wno-xcore-fptrgroup -Os -report $(INC) $(DEFINE_CODE_VERSION) $(FLOAT_FLAG)

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 1

# include py core make definitions
include $(TOP)/py/py.mk


#defined/add the main code files!
SRC_C = \
	main.xc \
	ctimer.xc \
	run.c \
	uart_core.c \
	modmyport.c \
	modtimer.c \
	$(BUILD_DIR)/_frozen_mpy.c \

#defined/add the support interactive files!
SRC_C += $(ROOTL)py/readline.c  
SRC_C += $(ROOTL)py/pyexec.c 
SRC_C += $(ROOTL)py/stdout_helpers.c 

SRC_PY += $(ROOTL)py/argcheck.c
SRC_PY += $(ROOTL)py/asmarm.c
SRC_PY += $(ROOTL)py/asmbase.c
SRC_PY += $(ROOTL)py/asmthumb.c
SRC_PY += $(ROOTL)py/asmx64.c
SRC_PY += $(ROOTL)py/asmx86.c
SRC_PY += $(ROOTL)py/asmxtensa.c
SRC_PY += $(ROOTL)py/bc.c
SRC_PY += $(ROOTL)py/binary.c
SRC_PY += $(ROOTL)py/builtinevex.c
SRC_PY += $(ROOTL)py/builtinhelp.c
SRC_PY += $(ROOTL)py/builtinimport.c
SRC_PY += $(ROOTL)py/compile.c
SRC_PY += $(ROOTL)py/emitbc.c
SRC_PY += $(ROOTL)py/emitcommon.c
SRC_PY += $(ROOTL)py/emitglue.c
SRC_PY += $(ROOTL)py/emitinlinethumb.c
SRC_PY += $(ROOTL)py/emitinlinextensa.c
SRC_PY += $(ROOTL)py/emitnarm.c
SRC_PY += $(ROOTL)py/emitnthumb.c
SRC_PY += $(ROOTL)py/emitnx64.c
SRC_PY += $(ROOTL)py/emitnx86.c
SRC_PY += $(ROOTL)py/emitnxtensa.c
SRC_PY += $(ROOTL)py/emitnxtensawin.c
SRC_PY += $(ROOTL)py/formatfloat.c
SRC_PY += $(ROOTL)py/frozenmod.c
SRC_PY += $(ROOTL)py/gc.c
SRC_PY += $(ROOTL)py/lexer.c
SRC_PY += $(ROOTL)py/malloc.c
SRC_PY += $(ROOTL)py/map.c
SRC_PY += $(ROOTL)py/modarray.c
SRC_PY += $(ROOTL)py/modbuiltins.c
SRC_PY += $(ROOTL)py/modcmath.c
SRC_PY += $(ROOTL)py/modcollections.c
SRC_PY += $(ROOTL)py/modgc.c
SRC_PY += $(ROOTL)py/modio.c
SRC_PY += $(ROOTL)py/modmath.c
SRC_PY += $(ROOTL)py/modmicropython.c
SRC_PY += $(ROOTL)py/modstruct.c
SRC_PY += $(ROOTL)py/modsys.c
SRC_PY += $(ROOTL)py/modthread.c
SRC_PY += $(ROOTL)py/moduerrno.c
SRC_PY += $(ROOTL)py/mpprint.c
SRC_PY += $(ROOTL)py/mpstate.c
SRC_PY += $(ROOTL)py/mpz.c
SRC_PY += $(ROOTL)py/nativeglue.c
SRC_PY += $(ROOTL)py/nlr.c
SRC_PY += $(ROOTL)py/nlrpowerpc.c
SRC_PY += $(ROOTL)py/nlrsetjmp.c
SRC_PY += $(ROOTL)py/nlrthumb.c
SRC_PY += $(ROOTL)py/nlrx64.c
SRC_PY += $(ROOTL)py/nlrx86.c
SRC_PY += $(ROOTL)py/nlrxtensa.c
SRC_PY += $(ROOTL)py/obj.c
SRC_PY += $(ROOTL)py/objarray.c
SRC_PY += $(ROOTL)py/objattrtuple.c
SRC_PY += $(ROOTL)py/objbool.c
SRC_PY += $(ROOTL)py/objboundmeth.c
SRC_PY += $(ROOTL)py/objcell.c
SRC_PY += $(ROOTL)py/objclosure.c
SRC_PY += $(ROOTL)py/objcomplex.c
SRC_PY += $(ROOTL)py/objdeque.c
SRC_PY += $(ROOTL)py/objdict.c
SRC_PY += $(ROOTL)py/objenumerate.c
SRC_PY += $(ROOTL)py/objexcept.c
SRC_PY += $(ROOTL)py/objfilter.c
SRC_PY += $(ROOTL)py/objfloat.c
SRC_PY += $(ROOTL)py/objfun.c
SRC_PY += $(ROOTL)py/objgenerator.c
SRC_PY += $(ROOTL)py/objgetitemiter.c
SRC_PY += $(ROOTL)py/objint.c
SRC_PY += $(ROOTL)py/objint_longlong.c
SRC_PY += $(ROOTL)py/objint_mpz.c
SRC_PY += $(ROOTL)py/objlist.c
SRC_PY += $(ROOTL)py/objmap.c
SRC_PY += $(ROOTL)py/objmodule.c
SRC_PY += $(ROOTL)py/objnamedtuple.c
SRC_PY += $(ROOTL)py/objnone.c
SRC_PY += $(ROOTL)py/objobject.c
SRC_PY += $(ROOTL)py/objpolyiter.c
SRC_PY += $(ROOTL)py/objproperty.c
SRC_PY += $(ROOTL)py/objrange.c
SRC_PY += $(ROOTL)py/objreversed.c
SRC_PY += $(ROOTL)py/objset.c
SRC_PY += $(ROOTL)py/objsingleton.c
SRC_PY += $(ROOTL)py/objslice.c
SRC_PY += $(ROOTL)py/objstr.c
SRC_PY += $(ROOTL)py/objstringio.c
SRC_PY += $(ROOTL)py/objstrunicode.c
SRC_PY += $(ROOTL)py/objtuple.c
SRC_PY += $(ROOTL)py/objtype.c
SRC_PY += $(ROOTL)py/objzip.c
SRC_PY += $(ROOTL)py/opmethods.c
SRC_PY += $(ROOTL)py/pairheap.c
SRC_PY += $(ROOTL)py/parse.c
SRC_PY += $(ROOTL)py/parsenum.c
SRC_PY += $(ROOTL)py/parsenumbase.c
SRC_PY += $(ROOTL)py/persistentcode.c
SRC_PY += $(ROOTL)py/profile.c
SRC_PY += $(ROOTL)py/pystack.c
SRC_PY += $(ROOTL)py/qstr.c
SRC_PY += $(ROOTL)py/reader.c
SRC_PY += $(ROOTL)py/repl.c
SRC_PY += $(ROOTL)py/ringbuf.c
SRC_PY += $(ROOTL)py/runtime.c
SRC_PY += $(ROOTL)py/runtime_utils.c
SRC_PY += $(ROOTL)py/scheduler.c
SRC_PY += $(ROOTL)py/scope.c
SRC_PY += $(ROOTL)py/sequence.c
SRC_PY += $(ROOTL)py/showbc.c
SRC_PY += $(ROOTL)py/smallint.c
SRC_PY += $(ROOTL)py/stackctrl.c
SRC_PY += $(ROOTL)py/stream.c
SRC_PY += $(ROOTL)py/unicode.c
SRC_PY += $(ROOTL)py/vm.c
SRC_PY += $(ROOTL)py/vstr.c
SRC_PY += $(ROOTL)py/warning.c

CFLAGS += $(INC) -Wall -Werror -Wdouble-promotion -Wfloat-conversion  $(FLOAT_FLAG)
CXXFLAGS += $(CFLAGS) $(FLOAT_FLAG)

OBJ += $(PY_CORE_O)

#add the library for reading the commands at interpretor
SRC_QSTR += $(ROOTL)py/readline.c 
SRC_QSTR += $(ROOTL)py/pyexec.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_QSTR += modmyport.c
SRC_QSTR += modtimer.c
endif

all: $(OBJ) $(BUILD)/_frozen_mpy.c output.xe
#all: output.xe
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
	$(info Debugg: Final build info)
	$(info Debugg: LDFLAGS is $(LDFLAGS))
	$(info Debugg: CMP is $(CMP))
	$(info Debugg: CMD is $(CMP) $(LDFLAGS))
endif   

output.xe:
	$(CMP) $(LDFLAGS) $(SRC_C) $(SRC_PY) -o $@
	rm -rf ../py
	rm -rf build	

$(BUILD)/_frozen_mpy.c: frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h 
	$(Q)$(TOP)/py/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@ 

clean:
	rm -rf output.xe
	rm -rf build

include $(ROOTL)py/mkrules.mk
