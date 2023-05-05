char scScript [] ="from gpio import *\n"
"from delay import *\n"
"while True:\n"
"	PortWrite(PORT4C,0x0F)\n"
"	delaySec(1)\n"
"	PortWrite(PORT4C,0x00)\n"
"	delaySec(1)\n"
;