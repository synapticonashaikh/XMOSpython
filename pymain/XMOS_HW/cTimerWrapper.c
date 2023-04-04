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
 *                           Includes
 * ----------------------------------------------------------------------------
*/
    #include "header.h"	
    #include "interrupt.h"    
    #include <hwtimer.h>  
    #include <xs1.h>


    #include "py/runtime.h"
    #include "mpconfig.h"
    #include "header.h"
    #include "py/mphal.h"
    #include "py/mpirq.h"
    #include "py/obj.h"
    #include "header.h"


/* ----------------------------------------------------------------------------
 *                           Macros
 * ----------------------------------------------------------------------------
*/
    register_interrupt_handler(FnTimerInterruptHandler, 1, 200)    

/* ----------------------------------------------------------------------------
 *                           External Function
 * ----------------------------------------------------------------------------
*/  
    void FnTimerInterruptHandler(void);
    unsigned FnTimerInterruptGetTime(hwtimer_t Var);
/* ----------------------------------------------------------------------------
 *                           Global Variable
 * ----------------------------------------------------------------------------
*/ 
    uint32_t globalTimer = RESET;
    
/* ----------------------------------------------------------------------------
 *                           Function Definition
 * ----------------------------------------------------------------------------
*/
/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnTimerInterruptUpdate(hwtimer_t Var)
{
    unsigned time;
    DISABLE_INTERRUPTS( );
    asm volatile("setc res[%0], %1"::"r"(Var),"r"(XS1_SETC_COND_NONE));
    time = FnTimerInterruptGetTime(Var);
    time += ui1mSec * globalTimer;
    asm volatile("setd res[%0], %1"::"r"(Var),"r"(time));
    asm volatile("setc res[%0], %1"::"r"(Var),"r"(XS1_SETC_COND_AFTER));
}    
/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnTimerInterruptStop(hwtimer_t Var)
{
    DISABLE_INTERRUPTS( );
    asm volatile("setc res[%0], %1"::"r"(Var),"r"(XS1_SETC_COND_NONE));
}
/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnTimerInterruptStart(hwtimer_t Var, uint32_t TimeInMsec)
{
    globalTimer = TimeInMsec ;
    set_interrupt_handler(FnTimerInterruptHandler, 1, Var, 0);
}
/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnTimerInterruptInit(hwtimer_t Var)
{
    FnTimerInterruptUpdate(Var);
}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnTimerIsrHandler (void)
{
    machine_pin_irq_obj_t *irq1 = 
    MP_STATE_PORT(machine_pin_irq_objects[1]);
    mp_irq_handler(&irq1->base);
}