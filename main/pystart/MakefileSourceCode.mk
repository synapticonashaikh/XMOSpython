
#defined/add the main code files!
ifeq ($(USE_FILE_EXTENSION_C_ONLY), 1) 
SRC_C +=  mainc.c
else
SRC_C +=  main.xc
endif
SRC_C +=  PythonRun.c
SRC_C +=  $(BUILD_DIR)/_frozen_mpy.c
#defined/add the support interactive files!
SRC_C += $(ROOTL)py/readline.c  
SRC_C += $(ROOTL)py/pyexec.c 
SRC_C += $(ROOTL)py/stdout_helpers.c 


#add all the hardware interface file
SRC_C +=  $(HARDWAREL)cTerminal.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_C +=  $(HARDWAREL)xcTimer.xc
SRC_C +=  $(HARDWAREL)xcGPIO.xc
#add all the modular files
SRC_C +=  $(MODULEL)modmyport.c
SRC_C +=  $(MODULEL)modgpio.c
SRC_C +=  $(MODULEL)modtimer.c
endif

#add the library for reading the commands at interpretor
SRC_QSTR += $(ROOTL)py/readline.c 
SRC_QSTR += $(ROOTL)py/pyexec.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_QSTR += $(MODULEL)modmyport.c
SRC_QSTR += $(MODULEL)modtimer.c
SRC_QSTR += $(MODULEL)modgpio.c
endif