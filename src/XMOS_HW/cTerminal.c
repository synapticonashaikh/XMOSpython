/**************************************************************************************
 **************************************************************************************
 ______________________________________________________________________________________

  Company:
	Synapticon GmbH (https://www.synapticon.com/)
 ______________________________________________________________________________________

  File Name:
	hello.xc
 ______________________________________________________________________________________

  Summary:
    This file contains the source code for printing "Hello world" on the terminal.
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


/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
*/

   /*Standard Header files*/
    #include "header.h"      
    #include "unistd.h"
    #include "string.h"
    #include "mpconfig.h"

#ifdef USE_LOCAL_MAIN

#elif defined SOMANET_SOFTWARE_MAIN
      #include <filesystem/spiffs_xc_wrapper.h>
#endif

/* ----------------------------------------------------------------------------
 *                          MACROS
 * ----------------------------------------------------------------------------
*/
#ifdef  USE_LOCAL_MAIN
        #define _SERAIL_MODE_COMMAND    1     
        #define _SERAIL_MODE_DATA       2     
        #define _SERIAL_RX_SIZE         1000
        #define _CODE_BUFFER_SIZE       5000
#elif defined SOMANET_SOFTWARE_MAIN

        #define _ERROR_FOPEN   (int8_t)-2
        #define _ERROR_FREAD   (int8_t)-3
        #define _ERROR_FSIZE   (int8_t)-4
        #define _ERROR_FSEEK   (int8_t)-5
        #define _ERROR_FWRITE  (int8_t)-6

        #define _LOG_FILE (char *)"PythonLog.log"
        #define _LOG_MAX_SIZE  (uint16_t)5000
        #define _LOG_ROLL_OVER (uint16_t)3000
#endif

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
#ifdef  USE_LOCAL_MAIN
        char ReciverBuffer[_SERIAL_RX_SIZE], 
        CodeBuffer[_CODE_BUFFER_SIZE], SingleChar ;
        uint32_t ReceiveCount = RESET, CodeReceiveCount = RESET;
        uint8_t ucMode = _SERAIL_MODE_COMMAND ;
        char  cprint[100]; 
        uint32_t uiCodeSize = RESET;       
#elif defined SOMANET_SOFTWARE_MAIN


#endif

/* ----------------------------------------------------------------------------
 *                          FUNCTION DECLARATION 
 * ----------------------------------------------------------------------------
*/
#ifdef  USE_LOCAL_MAIN

#elif defined SOMANET_SOFTWARE_MAIN
    int FnWriteLogs(char *str, unsigned long int len);
#endif

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
// Send string of given length
/***********************************************************************
 * Function Name : main 
 * Arguments	   : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) 
{ 
unsigned char d;   
#ifdef USE_LOCAL_MAIN
    if(len != RESET )
    d = write(STDOUT_FILENO, str, len); fflush(stdout);
#elif defined SOMANET_SOFTWARE_MAIN
    if(len != RESET )
       d =FnWriteLogs((char *)str, len);
#endif
}

// Receive single character
/***********************************************************************
 * Function Name : main 
 * Arguments	   : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
int mp_hal_stdin_rx_chr(void) 
{      
  unsigned char c = 0, d;
  d = read(STDIN_FILENO, &c, 1);   
  return c;
}

/***********************************************************************
 * Function Name : main 
 * Arguments	   : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
#ifdef SOMANET_SOFTWARE_MAIN
int FnWriteLogs(char *str, unsigned long int len)
{

    char TempFile[(uint16_t)3002]; int fileW =  RESET;
    int fileD = iSPIFFS_open(_LOG_FILE, SPIFFS_O_CREAT | SPIFFS_O_RDWR | SPIFFS_O_APPEND ); 
     if( fileD<RESET) return _ERROR_FOPEN;
     int fileS = iSPIFFS_get_size(fileD);
     if( fileS<RESET) return _ERROR_FSIZE;
      
  
    //if( fileS >= _LOG_MAX_SIZE || (fileS + len) >= _LOG_MAX_SIZE )
      {
        //  int fileL=  iSPIFFS_seek(fileD,_LOG_ROLL_OVER,SPIFFS_SEEK_SET);
        //  if( fileL<RESET) return _ERROR_FSEEK;
        //  memset(TempFile,RESET,sizeof(TempFile));       
        //  int fileR = iSPIFFS_read(fileD,TempFile, fileS - _LOG_ROLL_OVER);
        //  if( fileR<RESET) return _ERROR_FREAD;
        //  iSPIFFS_close(fileD);
        //  fileD = iSPIFFS_open (_LOG_FILE, SPIFFS_O_RDWR | SPIFFS_O_TRUNC );
        //  if(fileD<RESET) return _ERROR_FOPEN; 
        //  fileW = iSPIFFS_write(fileD,TempFile,fileS-_LOG_ROLL_OVER);
        //  if(fileW<RESET) return _ERROR_FWRITE;
      }
       fileW = iSPIFFS_write(fileD,(char *)str,len);
       if(fileW<RESET) return _ERROR_FWRITE;
      iSPIFFS_close(fileD);
 return RESET;  
}

#endif

/***********************************************************************
 * Function Name : main 
 * Arguments	   : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
#ifdef USE_LOCAL_MAIN
int FnReceiveCharacter(void)
{      
    unsigned char c = RESET, d;
    d = read(STDIN_FILENO, &c, 1);
    fflush(stdin);
    return c;
}  

/***********************************************************************
 * Function Name : main 
 * Arguments	   : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
void FnTransmitCharacter(const char *str) 
{ 
    unsigned char d;   
    uint32_t len = strlen(str);
    if(len!= RESET )
      d = write(STDOUT_FILENO, str, len);
    fflush(stdout); 
}

/***********************************************************************
 * Function Name : main 
 * Arguments	   : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
void FnReceiveProcess(char *Data)
{ 

         if ( strstr(Data, "# check $") != RESET)
            { FnTransmitCharacter("Device is active!\n\r");         }
    else if ( strstr(Data, "# status $") != RESET )     
            {  FnTransmitCharacter("Status: Code is standby!\n\r"); }
    else if ( strstr(Data, "# codesize") != RESET )     
            {   
              if (strchr(Data, '$') != RESET )
                 {
                    char * ucChar   = strstr (Data,"codesize");
                    char * uc1Space = strchr (ucChar,' ');  uc1Space ++;   
                    char * uc2Space = strrchr(ucChar,' '); *uc2Space = RESET;
                    uiCodeSize = strtol(uc1Space,NULL,(uint8_t)10);
                    sprintf(cprint,"Status: code size = %lu\n\r",uiCodeSize);
                    FnTransmitCharacter(cprint);  
                 }
               else goto down1;  
            }
    else if ( strstr(Data, "# modechange $") != RESET )     
            {
              if( uiCodeSize !=  RESET )
                { ucMode      = _SERAIL_MODE_DATA;
                  FnTransmitCharacter("Status: Mode Changed\n\rSend Code: "); }            
              else goto down1;  
            }
    else   {  down1: 
              sprintf(cprint,"unknow data = %s",Data);
              FnTransmitCharacter(cprint);  }       
}


/***********************************************************************
 * Function Name : main 
 * Arguments	   : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
char * FnCommandReceive(void)
{
        FnTransmitCharacter("Enter data: ");
        while (SET)
        {
            if (ucMode == _SERAIL_MODE_COMMAND)
            {
                     //hwtimer_delay(t,100000);
                     SingleChar  = FnReceiveCharacter( );
                if ( SingleChar != '\n' &&  SingleChar != RESET )
                   { ReciverBuffer [ReceiveCount] = SingleChar ; ReceiveCount++; }
                else
                if ( SingleChar == '\n' )
                   {
                      ReciverBuffer [ ReceiveCount ] = SingleChar ;
                      ReciverBuffer [ ReceiveCount + SET] = RESET ;                     
                      FnReceiveProcess(ReciverBuffer);
                      memset(ReciverBuffer,RESET,sizeof(ReciverBuffer));
                      ReceiveCount =  RESET ;
                      if (ucMode == _SERAIL_MODE_COMMAND)
                          FnTransmitCharacter("Enter data: ");               
                   }
                  //else FnTransmitCharacter("No data is received!\n\r");    
            }
            else
            {
                  CodeBuffer[CodeReceiveCount++] = FnReceiveCharacter( );
              if( CodeReceiveCount == uiCodeSize )
                { 
                  for (uint32_t ucLoop = RESET; ucLoop < uiCodeSize - SET ; ucLoop++ )
                      {sprintf(cprint,"%c",CodeBuffer[ucLoop]); FnTransmitCharacter(cprint); }                                          
                  FnTransmitCharacter("Finsihed!\n\r");                                     
                  CodeReceiveCount = 
                  uiCodeSize = RESET ; 
                  ucMode = _SERAIL_MODE_COMMAND ;
                  return  CodeBuffer;               
                }
            }

        }
}
#endif
