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
 #if ENABLE_DISABLE_GPIO_IRQ == 1

/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
*/
    #include "header.h"
    #include "interrupt.h" 
    #include "py/runtime.h"
    #include "py/mphal.h"
    #include "py/mpirq.h"
    #include "py/obj.h"


/* ----------------------------------------------------------------------------
 *                           External Function
 * ----------------------------------------------------------------------------
*/ 
/* ----------------------------------------------------------------------------
 *                           GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/

  static uint8_t RisingFallingEdge = RESET;
  static uint8_t uiStatus  = RESET;
  uint8_t    ucGpioIRQFlag = RESET;
  uint32_t   uiReadPort    = RESET;
  static int uifeedback    = RESET;

  uint8_t    ucDummyPin    = RESET;

/* ----------------------------------------------------------------------------
 *                           Fnction Definitions
 * ----------------------------------------------------------------------------
*/
/***********************************************************************
 * Function Name: Function1 
 * Arguments	  : void
 * Return Type	: void
 * Details	    : A callback function
 * *********************************************************************/
#if defined(SOMANET_SOFTWARE_MAIN) || defined(USE_LOCAL_MAIN)
    #pragma stackfunction 1000
#endif    
void FnGPIOCallbackFunction(void)
{
    machine_pin_irq_obj_t *irq1 = 
    MP_STATE_PORT (machine_pin_irq_objects[0]);
    mp_irq_handler(&irq1->base);
}

/***********************************************************************
 * Function Name: DEFINE_INTERRUPT_CALLBACK 
 * Arguments	  : 
 * Return Type	: 
 * Details	    : 
 * *********************************************************************/
void FnGPIOIntrCheck(void)
{
    if ( uiReadPort != RESET )
    {
     // uifeedback = FnPortRead(uiReadPort); //read the current status
        uifeedback = RESET;
      if (( uifeedback == SET ) 
      &&  ( uiStatus == RESET ))
          { uiStatus  =   SET;
          if (RisingFallingEdge == IRQ_RISING)
             {FnGPIOCallbackFunction( );  
              printf("IRQ 1!\n");}
          }
      else 
      if (( uifeedback == RESET ) 
      &&  ( uiStatus   ==   SET )) 
          { uiStatus    = RESET; 
            if (RisingFallingEdge == IRQ_FALLING)
               {FnGPIOCallbackFunction( );
                printf("IRQ 2!\n"); }
          }
         // printf("%d",uifeedback);         
    }
}

/***********************************************************************
 * Function Name: GPIOInterrupt 
 * Arguments	  : void
 * Return Type	: void
 * Details	    : 
 * *********************************************************************/
void GPIOInterrupt(uint32_t uiPort, uint8_t ucMode)
{

  ucGpioIRQFlag     = SET;
  RisingFallingEdge = ucMode;
  uiReadPort        = uiPort;
  //uiStatus = FnPortRead(uiReadPort);
   uiStatus = RESET;//FnReadDummy( );

}

#endif
