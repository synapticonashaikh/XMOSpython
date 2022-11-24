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

    #define  PARSE_SINGLE_INPUT   0
    #define  PARSE_FILE_INPUT     1
    #define  PARSE_EVAL_INPUT     2

/* ----------------------------------------------------------------------------
 *                           INCLUDE
 * ----------------------------------------------------------------------------
*/

  	/*Standard Header files*/
	  #include "header.h"

/* ----------------------------------------------------------------------------
 *                          EXTERNAL FUNCTION
 * ----------------------------------------------------------------------------
*/

  #ifdef CODE_VERSION_0_0_1
      extern "C"{ extern int mp_main(void); }
  #endif

  #ifdef CODE_VERSION_0_1_0
      extern "C"{ char * FnRunTheCommand(char *commad, uint8_t type); }
  #endif

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/


/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
#ifdef CODE_VERSION_0_1_0
  void FnSender(chanend SendCommand, chanend ReceiveCommad)
  {
    unsafe
    {
      //char * unsafe command = "print('Hello')";
      //char * unsafe command = "import myport\nfor i in range(10):\n  myport.info()";      
      char * unsafe command = "import board\nval=board.mul10(20)\nprint(val)";      
      char * unsafe ret;

       SendCommand <: command;        
    
        select 
        {
            case ReceiveCommad :> ret:
            printf("ret value = %s\n",ret);
            break ;
            //default: break;
        }      
    }
  }

  void FnReceiver(chanend ReceiveCommad, chanend SendCommand)
  {

    unsafe 
    {  
      char * unsafe command;

      while (SET)
      {
        select 
        {
            case ReceiveCommad :> command:        
            printf ("RECEIVED CMD=\n\r%s\n\r",command);
            SendCommand <: FnRunTheCommand(command,PARSE_FILE_INPUT);
            break ;

            default: break; // to make the select non-blockable 
        }
      }
    } 
  }
#endif

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/

int main( )
{

#ifdef CODE_VERSION_0_1_0
      printf("Warning! Terminal interpreter is not available!\n\r");      
      chan ReceiveCommad, SendCommand; 
      par
      {  
        FnSender  (ReceiveCommad,SendCommand);
        FnReceiver(ReceiveCommad,SendCommand);    
      }

#endif

#ifdef CODE_VERSION_0_0_1
        //printf("Warning! Terminal interpreter is activated!\n\r");  
        par
        { 
         on tile[TILE0] : mp_main( );  
        }  
#endif  

  return 0;

}

