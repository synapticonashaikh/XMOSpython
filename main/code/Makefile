#makefile which has all the configuration definition
include MakefileConfig.mk

#makefile which has all the python library
include MakefilePythonLib.mk

#makefile which has all the source code
include MakefileSourceCode.mk

#makefile which generate supported files
include MakefileTargetBuildDefinition.mk

#include the python envirmental variables
include $(ROOTL)/py/mkenv.mk

# include py core make definitions
include $(ROOTL)/py/py.mk

# include py core make definitions
include $(ROOTL)/py/mkrules.mk

#build the frozen code that required duuring the compilation
$(BUILD)/_frozen_mpy.c: frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h 
	$(Q)$(ROOTL)/py/mpy-tool.py -f -q    $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@ 

all:  dependency output.xe
ifeq ($(ENABLE_DISABLE_DEBUGG_MESSAGE), 1)
	$(info Debugg: Final build info)
	$(info Debugg: LDFLAGS is $(LDFLAGS))
	$(info Debugg: CMP is $(CMP))
	$(info Debugg: CMD is $(CMP) $(LDFLAGS))
endif   

dependency: $(OBJ) $(BUILD)/_frozen_mpy.c

output.xe:
	$(CMP) $(LDFLAGS) $(SRC_C) $(SRC_PY) -o $@
	rm -rf ../py
	rm -rf build	

clean:
	rm -rf output.xe
	rm -rf build
