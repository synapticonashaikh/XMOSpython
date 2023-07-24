/**************************************************************************************
 **************************************************************************************
 ______________________________________________________________________________________

  Company:
	Synapticon GmbH (https://www.synapticon.com/)
 ______________________________________________________________________________________

  File Name:
	parallel.xc
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
 *                           Macros
 * ----------------------------------------------------------------------------
*/
/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
*/
	/*Standard Header files*/
	#include "header.h"	
    #include <hwtimer.h> 

/* ----------------------------------------------------------------------------
 *                           External Function
 * ----------------------------------------------------------------------------
*/  

    extern void FnTimerInterruptStart(hwtimer_t Var, uint32_t TimeInMsec); 
    extern void FnTimerInterruptInit (hwtimer_t Var);    
    extern void FnTimerInterruptStop (hwtimer_t Var);    
    extern void FnTimerIsrHandler    (uint8_t ucIRQInstance);

/* ----------------------------------------------------------------------------
 *                           Global Variable
 * ----------------------------------------------------------------------------
*/ 
    hwtimer_t varTimerInterrupt ;
    uint8_t   ucTimerIRQFlag[(uint8_t)2] ;
    uint32_t  ucTimerIRQTime[(uint8_t)2] ;

/* ----------------------------------------------------------------------------
 *                           Function Definition
 * ----------------------------------------------------------------------------
*/ 
/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnTimerInterruptHandler(void)
{

  static uint32_t uiTimerCount[(uint8_t)2] ;

  for (uint8_t ucLoop=RESET; ucLoop < (uint8_t)2; ucLoop++)
      {
        if( ucTimerIRQFlag[ucLoop] == SET)
        {
               uiTimerCount[ucLoop] ++;
          if ( uiTimerCount[ucLoop] == ucTimerIRQTime[ucLoop])
             { uiTimerCount[ucLoop]  = RESET;
               FnTimerIsrHandler(ucLoop);  }
        }
        else 
        uiTimerCount[ucLoop] = RESET;
      }


    #if ENABLE_DISABLE_GPIO_IRQ == 1
      if( ucGpioIRQFlag == SET )
        { FnGPIOIntrCheck();   }
    #endif

    FnTimerInterruptInit(varTimerInterrupt);
}                             
/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	: main function, start of the code
 * *********************************************************************/
unsigned FnTimerInterruptGetTime(hwtimer_t Var)
{ unsigned time; Var :> time; return time; }                                                           

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	: main function, start of the code
 * *********************************************************************/
int FnStartTheTimerIrq(uint32_t uiTime,uint8_t uiInstance)
{
    /*start should come before init (to update the time)*/
    ucTimerIRQFlag[uiInstance] = SET;
    ucTimerIRQTime[uiInstance] = uiTime;
    return RESET;
}

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnEnableTheTimerIRQ(void)
{
  FnTimerInterruptInit (varTimerInterrupt);     
  FnTimerInterruptStart(varTimerInterrupt , 1);//1 ms
}
