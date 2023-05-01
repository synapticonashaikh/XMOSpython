from OBJDITC import *
from delay import *

def FnConfigureDevice( ):
    WriteControlWord(0x80)
    SetTargetTorque(0x00)
    delaymSec(30)
    WriteModesofOperation(0x0A)
    delaymSec(300)
    WriteControlWord(0x06)
    delaymSec(50)
    WriteControlWord(0x07)
    delaymSec(30)
    WriteControlWord(0x0F)
    delaymSec(30)

def FnCallbackFunction(self):
    if ReadErrorStatus( ) != 0:
       FnConfigureDevice( )

delaySec(10)
I2TEnDs(0)
FnConfigureDevice( )
tirq(handler=FnCallbackFunction,duration=500)

while True:
   SetTargetTorque(-32)  
   delaySec(2)
   SetTargetTorque(0)  
   delaySec(1)
   SetTargetTorque(+32)  
   delaySec(2)    
   SetTargetTorque(0)  
   delaySec(1)
