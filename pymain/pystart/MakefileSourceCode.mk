
#defined/add the main code files!
SRC_C +=  localmain.xc
SRC_C +=  PythonRun.c
SRC_C +=  $(BUILD_DIR)/_frozen_mpy.c

#defined/add the support interactive files!
SRC_C += $(PYLIBL)/readline.c  
SRC_C += $(PYLIBL)/pyexec.c 
SRC_C += $(PYLIBL)/stdout_helpers.c 

#add all the hardware interface file
SRC_C +=  $(HARDWAREL)cTerminal.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_C +=  $(HARDWAREL)xcGPIO.xc
SRC_C +=  $(HARDWAREL)xcTimer.xc
SRC_C +=  $(HARDWAREL)cTimerWrapper.c
SRC_C +=  $(HARDWAREL)xcTimerinterrupt.xc

#add all the modular files
SRC_C +=  $(MODULEL)modmyport.c
SRC_C +=  $(MODULEL)modgpio.c
SRC_C +=  $(MODULEL)modtimer.c
endif

#add the library for reading the commands at interpretor
SRC_QSTR += $(PYLIBL)/readline.c 
SRC_QSTR += $(PYLIBL)/pyexec.c
ifeq ($(ENABLE_DISABLE_OWN_MODULE), 1)
SRC_QSTR += $(MODULEL)modmyport.c
SRC_QSTR += $(MODULEL)modtimer.c
SRC_QSTR += $(MODULEL)modgpio.c
SRC_QSTR += $(ROOTL)py/mpirq.c
endif
