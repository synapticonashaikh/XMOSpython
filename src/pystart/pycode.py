from gpio import *
from delay import *

print('CODE STARTED')
while True:
	PortWrite(PORT4C,0x0F)
	delaySec(1)
	PortWrite(PORT4C,0x00)
	delaySec(1)
	