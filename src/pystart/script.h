char scScript [] =
"from gpio import *\n"
"from delay import *\n"
"print('CODE STARTED')\n"
"while True:\n"
"	PortWrite(PORT4C,0x0F)\n"
"	print('GPIO STATE HIGH!')\n"
"	delaySec(1)\n"
"	PortWrite(PORT4C,0x00)\n"
"	print('GPIO STATE LOW!')\n"
"	delaySec(1)\n";