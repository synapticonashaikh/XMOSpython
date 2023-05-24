from gpio import *
from delay import *

print('CODE STARTED')
while True:
	PortWrite(PORT4C,0x0F)
	print('GPIO STATE HIGH!')
	delaySec(1)
	PortWrite(PORT4C,0x00)
	print('GPIO STATE LOW!')
	delaySec(1)
	