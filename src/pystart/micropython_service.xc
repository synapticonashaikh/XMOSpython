/**************************************************************************************
 **************************************************************************************
 ______________________________________________________________________________________

  Company:
	Synapticon GmbH (https://www.synapticon.com/)
 ______________________________________________________________________________________

  File Name:
	Datatype.xc
 ______________________________________________________________________________________

  Summary:
    This file contains the source code for testing all the data types and 
    their memory allocated size assigned by the xc compiler.
 ______________________________________________________________________________________

  Description:
	This file contains the source code for a self-practice task by Synapticon GmbH. 
    It implements the logic of the application's requirements, and it may call API 
    routines from a different section of the code, such as drivers, system services, 
    and middleware (if applicable). However, at present, this code is not calling 
    any of the system-specified APIs (such as the "USARTInitialize" and "TimerTasks"
    functions) of any of the modules in the system. To make the code development 
    environment-friendly, the majority of the code shall be using self-created drivers.

 **************************************************************************************
 **************************************************************************************/

 /**************************************************************************************
   No-Copyright (c):
	 No copyrights are being imposed on these software files. Information shall have
	 to be freely available for the rapid development of science to benefit humanity.
	 When the information is free, this is not a barrier to their progress. Therefore,
	 I, Aatif Shaikh, license you the right to use, modify, copy and distribute this
	 software however you desire.

	 Note*
	 Software and documentation are provided "as is" without warranty of any kind,
	 either express or implied, including without limitation, any warranty of
	 merchantability, title, non-infringement and fitness for a particular purpose.
	 In no event shall, I (Aatif Shaikh) liable or obligated under contract,
	 negligence, strict liability, contribution, breach of warranty, or other legal
	 equitable theory any direct or indirect damages or expenses including but not
	 limited to any incidental, special, indirect, punitive or consequential damages,
	 lost profits or lost data, cost of procurement of substitute goods, technology,
	 services, or any claims by third parties (including but not limited to any
	 defence thereof), or other similar costs.

  ************************************************************************************/

  /************************************************************************************
  ______                                            __      __                                     
 /      \                                          |  \    |  \                                    
|  $$$$$$\ __    __  _______    ______    ______  _| $$_    \$$  _______   ______   _______        
| $$___\$$|  \  |  \|       \  |      \  /      \|   $$ \  |  \ /       \ /      \ |       \       
 \$$    \ | $$  | $$| $$$$$$$\  \$$$$$$\|  $$$$$$\\$$$$$$  | $$|  $$$$$$$|  $$$$$$\| $$$$$$$\      
 _\$$$$$$\| $$  | $$| $$  | $$ /      $$| $$  | $$ | $$ __ | $$| $$      | $$  | $$| $$  | $$      
|  \__| $$| $$__/ $$| $$  | $$|  $$$$$$$| $$__/ $$ | $$|  \| $$| $$_____ | $$__/ $$| $$  | $$      
 \$$    $$ \$$    $$| $$  | $$ \$$    $$| $$    $$  \$$  $$| $$ \$$     \ \$$    $$| $$  | $$      
  \$$$$$$  _\$$$$$$$ \$$   \$$  \$$$$$$$| $$$$$$$    \$$$$  \$$  \$$$$$$$  \$$$$$$  \$$   \$$      
          |  \__| $$                    | $$                                                       
           \$$    $$                    | $$                                                       
            \$$$$$$                      \$$                                                       
                          ______                 __        __    __                                
                         /      \               |  \      |  \  |  \                               
                        |  $$$$$$\ ______ ____  | $$____  | $$  | $$                               
                        | $$ __\$$|      \    \ | $$    \ | $$__| $$                               
                        | $$|    \| $$$$$$\$$$$\| $$$$$$$\| $$    $$                               
                        | $$ \$$$$| $$ | $$ | $$| $$  | $$| $$$$$$$$                               
                        | $$__| $$| $$ | $$ | $$| $$__/ $$| $$  | $$                               
                         \$$    $$| $$ | $$ | $$| $$    $$| $$  | $$                               
                          \$$$$$$  \$$  \$$  \$$ \$$$$$$$  \$$   \$$                               
                                                                                                   
                                                                                                                                                                                                   
		        In order to be irreplaceable, one must always be different
  *************************************************************************************/

/* ----------------------------------------------------------------------------
 *                           MACROS
 * ----------------------------------------------------------------------------
*/
    //  unsafe
    //  {
    //    char * unsafe command = 
    //     "from gpio import *\n"
    //     "def GPOICallback(self):\n"
    //     "    print('callback function!')\n"
    //     "pirq(handler=GPOICallback)\n"
    //     "count = 0\n"
    //     "while True:\n"
    //     "      pass\n";
    //  }

  //while(!sdo_is_initialized()) { }
  
    // unsafe
    // {
    //   char * unsafe command = 
    //   "from OBJDITC import *\n"
    //   "from delay import *\n"

    //   "def FnConfigureDevice( ):\n"
    //   "    WriteControlWord(0x80)\n"
    //   "    SetTargetTorque(0x00)\n"
    //   "    delaymSec(30)\n"
    //   "    WriteModesofOperation(0x0A)\n"
    //   "    delaymSec(300)\n"
    //   "    WriteControlWord(0x06)\n"
    //   "    delaymSec(50)\n"
    //   "    WriteControlWord(0x07)\n"
    //   "    delaymSec(30)\n"
    //   "    WriteControlWord(0x0F)\n"
    //   "    delaymSec(30)\n"

    //   "def FnCallbackFunction(self):\n"
    //   "    if ReadErrorStatus( ) != 0:\n"
    //   "       FnConfigureDevice( )\n"

    //   "delaySec(10)\n"
    //   "I2TEnDs(0)\n"      
    //   "FnConfigureDevice( )\n"
    //   "tirq(handler=FnCallbackFunction,duration=500)\n"
      
    //   "while True:\n"
    //   "   SetTargetTorque(-32)\n"  
    //   "   delaySec(2)\n"
    //   "   SetTargetTorque(0)\n"  
    //   "   delaySec(1)\n"
    //   "   SetTargetTorque(+32)\n"  
    //   "   delaySec(2)\n"    
    //   "   SetTargetTorque(0)\n"  
    //   "   delaySec(1)\n"; 

    //  // printf("Script is running!\n");
    //   while(SET)      
    //   FnRunTheCommand(command,RESET,SET);
    //   }

/* ----------------------------------------------------------------------------
 *                           INCLUDE
 * ----------------------------------------------------------------------------
*/
  	/*Standard Header files*/
	  #include "micropython_service.h"

/* ----------------------------------------------------------------------------
 *                           EXTERNAL FUNCTION
 * ----------------------------------------------------------------------------
*/

      extern "C"{ char *     FnRunTheCommand(char *commad, uint32_t CodeLen, uint8_t type); }
      extern "C"{ extern int FnMPInterpreterConsole(void); }
      extern "C"{ char *     FnCommandReceive(void); }
      extern "C"{ int        FnWriteLogs(char *str, unsigned long int len);}


/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnMicroPythonService(server interface MicroPythonInterface i_mpy,
                          client interface FileSystemInterface  i_filesystem,
                          client interface StorageInterface     i_storage)
{
    int ProcessStatus = RESET;

    /*wait for the file system to be ready*/
    select { case i_filesystem.service_ready(void):break; }
    /*wait for the SDO para to be ready*/    
    while(!sdo_is_initialized()) { }

    /*wait for the file system to be ready*/
    if (!isnull(i_storage)){ select { case i_storage.service_ready(void): break; } }

   /*Enable the microypthon Service*/
   i_mpy.service_ready( );


   ProcessStatus = SET;

   uint8_t log_buf[] = {"MicroPython: Code Started!\n"};

    while (SET) {
      select {
          case i_mpy.SvStartTheScript(void):
              ProcessStatus = SET;
          break;

          default:
          if( ProcessStatus  ==   SET )
            {  ProcessStatus  = RESET ;
              unsafe 
              {
                  if (!is_storage_interface_disabled_now()) { 
                  i_storage.write_log(LOGTYPE_INFO, log_buf, strlen(log_buf));
                  }

                  char FileName []= "UserScript.mpy", RXcommand[1000];
                  memset(RXcommand,'\0',  sizeof(RXcommand));            
                  int fileD = i_filesystem.open_file (FileName ,strlen(FileName) ,SPIFFS_O_RDONLY);
                  int FileS = i_filesystem.get_file_size(fileD);
                  int fileR = i_filesystem.read(fileD,RXcommand,FileS);
                  int fileC = i_filesystem.close_file(fileD);
                  FnRunTheCommand(RXcommand,FileS,RESET); 
              }
            } break; 
      }
    }
}
