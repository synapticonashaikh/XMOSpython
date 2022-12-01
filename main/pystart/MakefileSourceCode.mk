
#defined/add the main code files!
SRC_C +=  $(MODULEL)modtimer.c
SRC_C +=  main.xc
SRC_C +=  PythonRun.c
SRC_C +=  $(BUILD_DIR)/_frozen_mpy.c
#add all the hardware interface file
SRC_C +=  $(HARDWAREL)xcTimer.xc
SRC_C +=  $(HARDWAREL)xcGPIO.xc
SRC_C +=  $(HARDWAREL)cTerminal.c
#add all the modular files
SRC_C +=  $(MODULEL)modmyport.c
SRC_C +=  $(MODULEL)modgpio.c
#defined/add the support interactive files!
SRC_C += $(ROOTL)py/readline.c  
SRC_C += $(ROOTL)py/pyexec.c 
SRC_C += $(ROOTL)py/stdout_helpers.c 

#add the library for reading the commands at interpretor
SRC_QSTR += $(ROOTL)py/readline.c 
SRC_QSTR += $(ROOTL)py/pyexec.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_QSTR += $(MODULEL)modmyport.c
SRC_QSTR += $(MODULEL)modtimer.c
SRC_QSTR += $(MODULEL)modgpio.c
endif