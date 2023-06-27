from OBJDITC import WriteControlWord
from OBJDITC import SetTargetTorque
from OBJDITC import WriteModesofOperation
from OBJDITC import SetTargetTorque
from delay   import delaymSec
from delay   import delaySec

delaySec(5)    #delay, so we can switch the state machine from INIT to op 
WriteControlWord(0x80)  #clear all error
SetTargetTorque(0x00)   #reset the target torque
WriteModesofOperation(0x0A) #cyclic toque mode 
WriteControlWord(0x06)  #shutdown all operation
delaymSec(10)
WriteControlWord(0x07)  #switch on
delaymSec(10)
WriteControlWord(0x0F)  #switch on + enable operation
delaymSec(10)
SetTargetTorque(+30)  #set the target torque to -30


while True:
   delaySec(5)
   SetTargetTorque(0)	#set the target torque to 0 / turn off
   delaySec(1)   
   SetTargetTorque(-30) #set the target torque to -30
   delaySec(5)
   SetTargetTorque(0)  #set the target torque to 0 / turn off
   delaySec(1)      
   SetTargetTorque(+30) #set the target torque to +30