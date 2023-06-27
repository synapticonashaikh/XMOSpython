from OBJDITC import WriteControlWord
from OBJDITC import SetTargetTorque
from OBJDITC import WriteModesofOperation
from OBJDITC import SetTargetTorque
from delay   import delaymSec
from delay   import delaySec
from delay   import tirq
from gpio    import PortRead
from gpio    import PORT1M

MinimumTargetTorque = 20
CurrentTargetTorque = MinimumTargetTorque
MaximumTargetTorque = 80
CurrentProcessState = 0

def FnConfigureDevice( ):
    global CurrentProcessState
    delaySec(5)
    WriteControlWord(0x00)       # reset everything
    delaymSec(10)    
    WriteControlWord(0x80)        #clear all error
    SetTargetTorque(0x00)         #reset the target torque
    WriteModesofOperation(0x0A)   #cyclic toque mode  
    WriteControlWord(0x06)        #shutdown all operation
    delaymSec(10)
    WriteControlWord(0x07)        #switch on
    delaymSec(10)
    WriteControlWord(0x0F)        #switch on + enable operation
    delaymSec(10)
    CurrentProcessState =  1

def FnCallbackFunction(self): 
    global CurrentProcessState, MinimumTargetTorque, CurrentTargetTorque, MaximumTargetTorque
    if   PortRead(PORT1M) == 1 and CurrentProcessState == 1: #read the gpio 
         SetTargetTorque(CurrentTargetTorque) #set the target torque    
         if   CurrentTargetTorque < MaximumTargetTorque:
              CurrentTargetTorque = CurrentTargetTorque + 5
    elif PortRead(PORT1M) == 0 and CurrentProcessState == 1:
         SetTargetTorque(CurrentTargetTorque) #set the target torque
         if   CurrentTargetTorque > MinimumTargetTorque:
              CurrentTargetTorque = CurrentTargetTorque - 5

FnConfigureDevice()
tirq(handler=FnCallbackFunction,duration=100) #100ms

while True:
      pass