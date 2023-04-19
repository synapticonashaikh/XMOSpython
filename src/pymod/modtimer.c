
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

    #include "runtime.h"
    #include "interrupt.h" 

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/

/* ----------------------------------------------------------------------------
 *                           important command
 * ----------------------------------------------------------------------------
*/

/* ----------------------------------------------------------------------------
 *                           Fnction Definitions
 * ----------------------------------------------------------------------------
*/

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t delay_delayuSec(mp_obj_t a) 
{
  FndelayuSec(MP_OBJ_SMALL_INT_VALUE(a));
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(delay_delayuSec_obj, delay_delayuSec);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t delay_delaymSec(mp_obj_t a) 
{
  FndelaymSec(MP_OBJ_SMALL_INT_VALUE(a));
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(delay_delaymSec_obj, delay_delaymSec);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t delay_delaySec(mp_obj_t a) 
{
  FndelaySec(MP_OBJ_SMALL_INT_VALUE(a));
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(delay_delaySec_obj, delay_delaySec);


/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t delay_PrintTM(void) 
{
  mp_printf(&mp_plat_print,"****TIMER MODULES****\n");
  mp_printf(&mp_plat_print,"1) PrintTM\n"  );    
  mp_printf(&mp_plat_print,"2) delayuSec\n");  
  mp_printf(&mp_plat_print,"3) delaymSec\n");  
  mp_printf(&mp_plat_print,"4) delaySec\n" );    
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_PrintTM_obj, delay_PrintTM);


/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
#pragma stackfunction 1000
STATIC mp_obj_t delay_irq(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) 
{

    enum { ARG_handler, ARG_duration};
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_handler,  MP_ARG_OBJ,  {.u_rom_obj = MP_ROM_NONE }},
        { MP_QSTR_duration, MP_ARG_INT,  {.u_int     = 1000 }},
    };
    
    pin_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args , pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

     // Get the IRQ object.
     uint8_t eic_id = 1;
     machine_pin_irq_obj_t *irq = MP_STATE_PORT(machine_timer_irq_objects[eic_id]);

    if (n_args > 1 || kw_args->used != 0) 
     {  
      // Update IRQ data.
        irq = m_new_obj(machine_pin_irq_obj_t);
        irq->base.base.type = &mp_irq_type;
        irq->base.parent  = MP_OBJ_FROM_PTR(self);
        MP_STATE_PORT(machine_timer_irq_objects[eic_id]) = irq;
        irq->base.handler = args[ARG_handler].u_obj;
     }

     FnStartTheTimerIrq(args[ARG_duration].u_int);

    return mp_const_none;

}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(delay_irq_obj, 0, delay_irq);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC const mp_rom_map_elem_t delay_module_globals_table[] = 
{
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_delay) },
    { MP_ROM_QSTR(MP_QSTR_delayuSec), MP_ROM_PTR(&delay_delayuSec_obj) },
    { MP_ROM_QSTR(MP_QSTR_delaymSec), MP_ROM_PTR(&delay_delaymSec_obj) },
    { MP_ROM_QSTR(MP_QSTR_delaySec),  MP_ROM_PTR(&delay_delaySec_obj)  },
    { MP_ROM_QSTR(MP_QSTR_PrintTM),   MP_ROM_PTR(&delay_PrintTM_obj)   },
    { MP_ROM_QSTR(MP_QSTR_tirq),      MP_ROM_PTR(&delay_irq_obj) }, 
};
STATIC MP_DEFINE_CONST_DICT(delay_module_globals, delay_module_globals_table);

const mp_obj_module_t delay_module = 
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&delay_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_delay, delay_module);

MP_REGISTER_ROOT_POINTER(void *machine_timer_irq_objects[2]);