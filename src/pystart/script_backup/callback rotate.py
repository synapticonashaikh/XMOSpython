from OBJDITC import WriteControlWord, SetTargetTorque, WriteModesofOperation, SetTargetTorque
from delay   import delaymSec, delaySec, tirq

flag = 0
forward  = 1
backward = 2
Gdirection = forward

def FnInitTargetTorque():
    delaySec(5)
    WriteControlWord(0x80)
    SetTargetTorque(0x00)
    WriteModesofOperation(0x0A) 
    WriteControlWord(0x06)
    delaymSec(10)
    WriteControlWord(0x07)
    delaymSec(10)
    WriteControlWord(0x0F)
    delaymSec(10)
    SetTargetTorque(+30)
    print('Init completed')
    
def FnRotateMotor(direction):
    SetTargetTorque(0)
    delaySec(1)
    if direction == forward:
        SetTargetTorque(+25)
    elif direction == backward:
        SetTargetTorque(-25)

def CallBack1(self):
    global Gdirection
    global flag
    flag = 1
    if Gdirection == forward:
        Gdirection =  backward
    else:
        Gdirection == forward
    
FnInitTargetTorque()
tirq(handler=CallBack1,duration=5000,instance=0)
print('Code started:')

while True:
    if flag == 1:
        flag = 0
        FnRotateMotor(Gdirection)
        