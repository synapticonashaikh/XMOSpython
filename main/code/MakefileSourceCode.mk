

#defined/add the main code files!
SRC_C +=  main.xc
SRC_C +=  ctimer.xc
SRC_C +=  PythonRun.c
SRC_C +=  InputOutput.c
SRC_C +=  modmyport.c
SRC_C +=  modtimer.c
SRC_C +=  $(BUILD_DIR)/_frozen_mpy.c

#defined/add the support interactive files!
SRC_C += $(ROOTL)py/readline.c  
SRC_C += $(ROOTL)py/pyexec.c 
SRC_C += $(ROOTL)py/stdout_helpers.c 

#add the library for reading the commands at interpretor
SRC_QSTR += $(ROOTL)py/readline.c 
SRC_QSTR += $(ROOTL)py/pyexec.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_QSTR += modmyport.c
SRC_QSTR += modtimer.c
endif