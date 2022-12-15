
# qstr definitions (must come before including py.mk)
QSTR_DEFS = ../headers/qstrdefsport.h

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 1

#add the python complied object to final object
OBJ += $(PY_CORE_O)

#flags required to compile python
CFLAGS += $(INC) -Wall -Werror -Wdouble-promotion -Wfloat-conversion  $(FLOAT_FLAG)
CXXFLAGS += $(CFLAGS) $(FLOAT_FLAG)

