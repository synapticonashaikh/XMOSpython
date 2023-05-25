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

    #define _SERAIL_MODE_COMMAND    1     
    #define _SERAIL_MODE_DATA       2     

    #define _SERIAL_RX_SIZE         1000
    #define _CODE_BUFFER_SIZE       5000


/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
        char ReciverBuffer[_SERIAL_RX_SIZE], 
        CodeBuffer[_CODE_BUFFER_SIZE],
        SingleChar ;
        uint32_t ReceiveCount = RESET, CodeReceiveCount = RESET;
        uint8_t ucMode = _SERAIL_MODE_COMMAND ;
        char  cprint[100]; 
        uint32_t uiCodeSize = RESET;

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/

// Receive single character
int mp_hal_stdin_rx_chr(void) 
{      
  unsigned char c = 0, d;
  d = read(STDIN_FILENO, &c, 1);   
  return c;
}  

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) 
{ 
    unsigned char d;   
    if(len!= RESET )
    d = write(STDOUT_FILENO, str, len);
    fflush(stdout);
}

/***********************************************************************
 * Function Name : main 
 * Arguments	 : void
 * Return Type	 : int
 * Details	     : main function, start of the code
 * *********************************************************************/
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
                    sprintf(cprint,"Status: code size = %d\n\r",uiCodeSize);
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

