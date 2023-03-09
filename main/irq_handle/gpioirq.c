

#include <xcore/hwtimer.h>
#include <xcore/triggerable.h>
#include <xcore/port.h>
#include <xcore/interrupt.h>
#include <xcore/interrupt_wrappers.h>
#include "header.h"

port_t button1 = XS1_PORT_1P;
static uint8_t RisingFallingEdge; //current code generates on rising edge!
static uint8_t uifeedback,uiStatus;


/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
DEFINE_INTERRUPT_PERMITTED(interrupt_handlers, void, interruptable_task, void)
{
  interrupt_unmask_all( ); 
  FnCompleteCode( );
}

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
DEFINE_INTERRUPT_CALLBACK (interrupt_handlers, interrupt_task, button)
{
  //manipulation to get the interrupt on rising edge only
  port_set_trigger_in_not_equal(button1, RisingFallingEdge);
  RisingFallingEdge = !RisingFallingEdge;
  uifeedback = port_peek(button1); 
  if      (( uifeedback == 1 ) && (uiStatus == 0))
          { /*CallbackFunction( );*/ uiStatus = 1;}
  else if ((uifeedback == 0 ) && (uiStatus == 1)) 
          { uiStatus = 0;   }
}

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void GPIOINTRWrapper(void)
{ INTERRUPT_PERMITTED(interruptable_task)( ); }
/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void GPIOInterrupt(void)
{
  
  port_enable(button1);
  triggerable_setup_interrupt_callback(button1, &button1, INTERRUPT_CALLBACK(interrupt_task));
  port_set_trigger_in_not_equal(button1, 1);
  port_clear_trigger_in(button1);
  triggerable_enable_trigger(button1);

}