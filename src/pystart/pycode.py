from gpio import *
from delay import *

print('CODE STARTED')
while True:
	PortWrite(PORT4C,0x0F)
	delaymSec(10)
	PortWrite(PORT4C,0x00)
	delaymSec(10)
	