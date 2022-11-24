#enable/ disable debugg message 
ENABLE_DISABLE_DEBUGG_MESSAGE = 1

#enable disable micropython debug
#MPY_DEBUGG_FLAG = -DMPY_DEBUGG_ENABLE

#define the code version
#for the terminal interperter use DCODE_VERSION_0_0_1
#without terminal use DCODE_VERSION_0_1_0
DEFINE_CODE_VERSION	= -DCODE_VERSION_0_1_0

# MICROPY_FLOAT_IMPL_NONE MICROPY_FLOAT_IMPL_FLOAT MICROPY_FLOAT_IMPL_DOUBLE 
FLOAT_FLAG = -DMICROPY_FLOAT_IMPL=MICROPY_FLOAT_IMPL_FLOAT

CMP = xcc -target=XCORE-200-EXPLORER
#-Wno-xcore-fptrgroup
#include the all required path
INC += -I.
INC += -I../../
INC += -Ibuild
INC += -Ibuild/genhdr/

LDFLAGS = -Wno-unused-variable -Os -report $(INC) $(MPY_DEBUGG_FLAG) $(DEFINE_CODE_VERSION) $(FLOAT_FLAG)

SRC_C = \
	run.c \
	main.xc \
	uart_core.c \
	modmyport.c \
	build/_frozen_mpy.c \

SRC_C += ../../shared/libc/printf.c 
SRC_C += ../../shared/readline/readline.c  
SRC_C += ../../shared/runtime/pyexec.c 
SRC_C += ../../shared/runtime/stdout_helpers.c 

SRC_PY += ../../py/argcheck.c
SRC_PY += ../../py/asmarm.c
SRC_PY += ../../py/asmbase.c
SRC_PY += ../../py/asmthumb.c
SRC_PY += ../../py/asmx64.c
SRC_PY += ../../py/asmx86.c
SRC_PY += ../../py/asmxtensa.c
SRC_PY += ../../py/bc.c
SRC_PY += ../../py/binary.c
SRC_PY += ../../py/builtinevex.c
SRC_PY += ../../py/builtinhelp.c
SRC_PY += ../../py/builtinimport.c
SRC_PY += ../../py/compile.c
SRC_PY += ../../py/emitbc.c
SRC_PY += ../../py/emitcommon.c
SRC_PY += ../../py/emitglue.c
SRC_PY += ../../py/emitinlinethumb.c
SRC_PY += ../../py/emitinlinextensa.c
SRC_PY += ../../py/emitnarm.c
SRC_PY += ../../py/emitnthumb.c
SRC_PY += ../../py/emitnx64.c
SRC_PY += ../../py/emitnx86.c
SRC_PY += ../../py/emitnxtensa.c
SRC_PY += ../../py/emitnxtensawin.c
SRC_PY += ../../py/formatfloat.c
SRC_PY += ../../py/frozenmod.c
SRC_PY += ../../py/gc.c
SRC_PY += ../../py/lexer.c
SRC_PY += ../../py/malloc.c
SRC_PY += ../../py/map.c
SRC_PY += ../../py/modarray.c
SRC_PY += ../../py/modbuiltins.c
SRC_PY += ../../py/modcmath.c
SRC_PY += ../../py/modcollections.c
SRC_PY += ../../py/modgc.c
SRC_PY += ../../py/modio.c
SRC_PY += ../../py/modmath.c
SRC_PY += ../../py/modmicropython.c
SRC_PY += ../../py/modstruct.c
SRC_PY += ../../py/modsys.c
SRC_PY += ../../py/modthread.c
SRC_PY += ../../py/moduerrno.c
SRC_PY += ../../py/mpprint.c
SRC_PY += ../../py/mpstate.c
SRC_PY += ../../py/mpz.c
SRC_PY += ../../py/nativeglue.c
SRC_PY += ../../py/nlr.c
SRC_PY += ../../py/nlrpowerpc.c
SRC_PY += ../../py/nlrsetjmp.c
SRC_PY += ../../py/nlrthumb.c
SRC_PY += ../../py/nlrx64.c
SRC_PY += ../../py/nlrx86.c
SRC_PY += ../../py/nlrxtensa.c
SRC_PY += ../../py/obj.c
SRC_PY += ../../py/objarray.c
SRC_PY += ../../py/objattrtuple.c
SRC_PY += ../../py/objbool.c
SRC_PY += ../../py/objboundmeth.c
SRC_PY += ../../py/objcell.c
SRC_PY += ../../py/objclosure.c
SRC_PY += ../../py/objcomplex.c
SRC_PY += ../../py/objdeque.c
SRC_PY += ../../py/objdict.c
SRC_PY += ../../py/objenumerate.c
SRC_PY += ../../py/objexcept.c
SRC_PY += ../../py/objfilter.c
SRC_PY += ../../py/objfloat.c
SRC_PY += ../../py/objfun.c
SRC_PY += ../../py/objgenerator.c
SRC_PY += ../../py/objgetitemiter.c
SRC_PY += ../../py/objint.c
SRC_PY += ../../py/objint_longlong.c
SRC_PY += ../../py/objint_mpz.c
SRC_PY += ../../py/objlist.c
SRC_PY += ../../py/objmap.c
SRC_PY += ../../py/objmodule.c
SRC_PY += ../../py/objnamedtuple.c
SRC_PY += ../../py/objnone.c
SRC_PY += ../../py/objobject.c
SRC_PY += ../../py/objpolyiter.c
SRC_PY += ../../py/objproperty.c
SRC_PY += ../../py/objrange.c
SRC_PY += ../../py/objreversed.c
SRC_PY += ../../py/objset.c
SRC_PY += ../../py/objsingleton.c
SRC_PY += ../../py/objslice.c
SRC_PY += ../../py/objstr.c
SRC_PY += ../../py/objstringio.c
SRC_PY += ../../py/objstrunicode.c
SRC_PY += ../../py/objtuple.c
SRC_PY += ../../py/objtype.c
SRC_PY += ../../py/objzip.c
SRC_PY += ../../py/opmethods.c
SRC_PY += ../../py/pairheap.c
SRC_PY += ../../py/parse.c
SRC_PY += ../../py/parsenum.c
SRC_PY += ../../py/parsenumbase.c
SRC_PY += ../../py/persistentcode.c
SRC_PY += ../../py/profile.c
SRC_PY += ../../py/pystack.c
SRC_PY += ../../py/qstr.c
SRC_PY += ../../py/reader.c
SRC_PY += ../../py/repl.c
SRC_PY += ../../py/ringbuf.c
SRC_PY += ../../py/runtime.c
SRC_PY += ../../py/runtime_utils.c
SRC_PY += ../../py/scheduler.c
SRC_PY += ../../py/scope.c
SRC_PY += ../../py/sequence.c
SRC_PY += ../../py/showbc.c
SRC_PY += ../../py/smallint.c
SRC_PY += ../../py/stackctrl.c
SRC_PY += ../../py/stream.c
SRC_PY += ../../py/unicode.c
SRC_PY += ../../py/vm.c
SRC_PY += ../../py/vstr.c
SRC_PY += ../../py/warning.c


all: output.xe
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
	$(info Debugg: Final build info)
	$(info Debugg: LDFLAGS is $(LDFLAGS))
	$(info Debugg: CMP is $(CMP))
	$(info Debugg: CMD is $(CMP) $(LDFLAGS))
endif   

output.xe:
	$(CMP) $(LDFLAGS) $(SRC_C) $(SRC_PY) $(SRC_FLOAT) -o $@

clean:
	rm -rf output.xe
