from delay import *
from gpio import *
Loop1 = 0
Loop2 = 0        
def CallBack1(self):
    global Loop1
    Loop1 = Loop1 + 1
    print('Count1 = ' + str(Loop1))
def CallBack2(self):
    global Loop2
    Loop2 = Loop2 + 1
    print('Count2 = ' + str(Loop2))
delaySec(2)
tirq(handler=CallBack2,duration=2000,instance=1)
tirq(handler=CallBack1,duration=500,instance=0)
while True:
      pass