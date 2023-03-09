
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
	//#define PORT_MODE_INPUT   1
	//#define PORT_MODE_OUTPUT  2

    #define IRQ_FALLING (1)
    #define IRQ_RISING (2)

/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
*/

    #include "py/runtime.h"
    #include "mpconfig.h"
    #include "header.h"
    #include "py/mphal.h"
    #include "py/mpirq.h"
    #include "py/obj.h"
    #include "header.h"


/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
    //ypedef GPIO_TypeDef pin_gpio_t;
/* ----------------------------------------------------------------------------
 *                           important command
 * ----------------------------------------------------------------------------
*/
typedef struct _machine_pin_obj_t {
    mp_obj_base_t base;
    uint8_t pin_id;
    char *name;
    uint8_t eic;
    uint8_t adc0;
    uint8_t adc1;
    uint8_t sercom1;
    uint8_t sercom2;
    uint8_t tc;
    uint8_t tcc1;
    uint8_t tcc2;
} machine_pin_obj_t;

typedef struct _machine_pin_irq_obj_t {
    mp_irq_obj_t base;
    uint32_t flags;
    uint32_t trigger;
    uint8_t pin_id;
} machine_pin_irq_obj_t;


typedef struct {
    mp_obj_base_t base;
    qstr name;
    uint8_t idx;
    uint8_t fn;
    uint8_t unit;
    uint8_t type;
    void *reg; // The peripheral associated with this AF
} pin_af_obj_t;

typedef struct {
    mp_obj_base_t base;
    qstr name;
    uint32_t port   : 4;
    uint32_t pin    : 5;    // Some ARM processors use 32 bits/PORT
    uint32_t num_af : 4;
    uint32_t adc_channel : 5; // Some ARM processors use 32 bits/PORT
    uint32_t adc_num  : 3;  // 1 bit per ADC
    uint32_t pin_mask;
    /*pin_gpio_t*/ machine_pin_obj_t *gpio;
    const pin_af_obj_t *af;
    uint8_t pin_id;
} pin_obj_t; 



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
STATIC mp_obj_t gpio_PortRead(mp_obj_t a) 
{ 
    return MP_OBJ_NEW_SMALL_INT( FnPortRead(MP_OBJ_SMALL_INT_VALUE(a)));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gpio_PortRead_obj, gpio_PortRead);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t gpio_PortWrite(mp_obj_t a, mp_obj_t b) 
{
   FnPortWrite(MP_OBJ_SMALL_INT_VALUE(a),MP_OBJ_SMALL_INT_VALUE(b));
   return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(gpio_PortWrite_obj, gpio_PortWrite);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t gpio_Toggle(void) 
{
  FnToggle();
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gpio_Toggle_obj, gpio_Toggle);


/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t gpio_PrintGM(void) 
{
  mp_printf(&mp_plat_print,"****GPIO MODULES****\n");
  mp_printf(&mp_plat_print,"1) PrintGM\n");    
  mp_printf(&mp_plat_print,"2) PortRead\n");  
  mp_printf(&mp_plat_print,"3) PortWrite\n");  
  mp_printf(&mp_plat_print,"****GPIO DEFINITION****\n");
  mp_printf(&mp_plat_print,"1) PORT1A\n2) PORT1B\n3) PORT1C\n4) PORT1D\n5) PORT1E\n6) PORT1F\n7) PORT1G\n8) PORT1H\n");
  mp_printf(&mp_plat_print,"9) PORT1I\n10) PORT1J\n11) PORT1K\n12) PORT1L\n13) PORT1M\n14) PORT1N\n15) PORT1O\n16) PORT1P\n");  
  mp_printf(&mp_plat_print,"17) PORT4A\n18) PORT4B\n19) PORT4C\n20) PORT4D\n21) PORT4E\n22) PORT4F\n23) PORT8A\n24) PORT8B\n");
  mp_printf(&mp_plat_print,"25) PORT8C\n26) PORT8D\n27) PORT16A\n28) PORT16B\n29) PORT32A\n");  

  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gpio_PrintGM_obj, gpio_PrintGM);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
#pragma stackfunction 1000
STATIC mp_obj_t gpiopin_irq(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) 
{

    enum { ARG_handler, ARG_trigger, ARG_hard };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_handler, MP_ARG_OBJ,  {.u_rom_obj = MP_ROM_NONE} },
        { MP_QSTR_trigger, MP_ARG_INT,  {.u_int = 3} },
        { MP_QSTR_hard   , MP_ARG_BOOL, {.u_bool = false} },
    };
    
    pin_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args , pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

     // Get the IRQ object.
     uint8_t eic_id = 1;//get_pin_obj_ptr(self->pin_id)->eic;
     machine_pin_irq_obj_t *irq = MP_STATE_PORT(machine_pin_irq_objects[eic_id]);
     if (irq != NULL && irq->pin_id != self->pin_id) 
     {
        mp_raise_ValueError(MP_ERROR_TEXT("IRQ already used"));
     }

    if (irq == NULL) 
    {
        irq = m_new_obj(machine_pin_irq_obj_t);
        irq->base.base.type = &mp_irq_type;
        irq->base.parent  = MP_OBJ_FROM_PTR(self);
        irq->base.handler = mp_const_none;
        irq->base.ishard  = false;
        irq->pin_id       = 0xff;
        MP_STATE_PORT(machine_pin_irq_objects[eic_id]) = irq;
    }


    if (n_args > 1 || kw_args->used != 0) 
     {  
        // Update IRQ data.
        irq->base.handler = args[ARG_handler].u_obj;
        irq->base.ishard  = args[ARG_hard].u_bool  ;
        if (args[ARG_handler].u_obj != mp_const_none) 
            {   }
     }


        machine_pin_irq_obj_t *irq1 = 
        MP_STATE_PORT(machine_pin_irq_objects[eic_id]);
    if (irq1 != NULL) 
        {
            irq1->flags = irq1->trigger;
            mp_irq_handler(&irq1->base);
        }

    return mp_const_none;

}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(pin_irq_obj, 0, gpiopin_irq);

// Common EIC handler for all events.
void EIC_Handler(void) 
 {
//     uint32_t mask = 1;
//     uint32_t isr = EIC->INTFLAG.reg;
//     for (int eic_id = 0; eic_id < 16; eic_id++, mask <<= 1) {
//         // Did the ISR fire?
//         if (isr & mask) {
//             EIC_occured = true;
//             EIC->INTFLAG.reg |= mask; // clear the ISR flag
//             machine_pin_irq_obj_t *irq = MP_STATE_PORT(machine_pin_irq_objects[eic_id]);
//             if (irq != NULL) {
//                 irq->flags = irq->trigger;
//                 mp_irq_handler(&irq->base);
//                 break;
//             }
//         }
//     }
}


/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC const mp_rom_map_elem_t gpio_module_globals_table[] = 
{
    /*Module head*/
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_gpio) },
    { MP_ROM_QSTR(MP_QSTR_PortRead),  MP_ROM_PTR(&gpio_PortRead_obj)  },
    { MP_ROM_QSTR(MP_QSTR_PortWrite), MP_ROM_PTR(&gpio_PortWrite_obj) },
    { MP_ROM_QSTR(MP_QSTR_PrintGM),   MP_ROM_PTR(&gpio_PrintGM_obj) },    
    { MP_ROM_QSTR(MP_QSTR_Toggle),    MP_ROM_PTR(&gpio_Toggle_obj) },        
    { MP_ROM_QSTR(MP_QSTR_pirq),       MP_ROM_PTR(&pin_irq_obj) },    
    { MP_ROM_QSTR(MP_QSTR_IRQ_RISING),  MP_ROM_INT(IRQ_FALLING) },
    { MP_ROM_QSTR(MP_QSTR_IRQ_FALLING), MP_ROM_INT(IRQ_RISING) },

    /*ports pin definition*/
    { MP_ROM_QSTR(MP_QSTR_PORT1A), MP_ROM_INT(PORT1A) },
    { MP_ROM_QSTR(MP_QSTR_PORT1B), MP_ROM_INT(PORT1B) },
    { MP_ROM_QSTR(MP_QSTR_PORT1C), MP_ROM_INT(PORT1C) },
    { MP_ROM_QSTR(MP_QSTR_PORT1D), MP_ROM_INT(PORT1D) },
    { MP_ROM_QSTR(MP_QSTR_PORT1E), MP_ROM_INT(PORT1E) },
    { MP_ROM_QSTR(MP_QSTR_PORT1F), MP_ROM_INT(PORT1F) },
    { MP_ROM_QSTR(MP_QSTR_PORT1G), MP_ROM_INT(PORT1G) },
    { MP_ROM_QSTR(MP_QSTR_PORT1H), MP_ROM_INT(PORT1H) },
    { MP_ROM_QSTR(MP_QSTR_PORT1I), MP_ROM_INT(PORT1I) },
    { MP_ROM_QSTR(MP_QSTR_PORT1J), MP_ROM_INT(PORT1J) },
    { MP_ROM_QSTR(MP_QSTR_PORT1K), MP_ROM_INT(PORT1K) },
    { MP_ROM_QSTR(MP_QSTR_PORT1L), MP_ROM_INT(PORT1L) },
    { MP_ROM_QSTR(MP_QSTR_PORT1M), MP_ROM_INT(PORT1M) },
    { MP_ROM_QSTR(MP_QSTR_PORT1N), MP_ROM_INT(PORT1N) },
    { MP_ROM_QSTR(MP_QSTR_PORT1O), MP_ROM_INT(PORT1O) },
    { MP_ROM_QSTR(MP_QSTR_PORT1P), MP_ROM_INT(PORT1P) },

    { MP_ROM_QSTR(MP_QSTR_PORT4A), MP_ROM_INT(PORT4A) },
    { MP_ROM_QSTR(MP_QSTR_PORT4B), MP_ROM_INT(PORT4B) },
    { MP_ROM_QSTR(MP_QSTR_PORT4C), MP_ROM_INT(PORT4C) },
    { MP_ROM_QSTR(MP_QSTR_PORT4D), MP_ROM_INT(PORT4D) },
    { MP_ROM_QSTR(MP_QSTR_PORT4E), MP_ROM_INT(PORT4E) },
    { MP_ROM_QSTR(MP_QSTR_PORT4F), MP_ROM_INT(PORT4F) },

    { MP_ROM_QSTR(MP_QSTR_PORT8A), MP_ROM_INT(PORT8A) },
    { MP_ROM_QSTR(MP_QSTR_PORT8B), MP_ROM_INT(PORT8B) },
    { MP_ROM_QSTR(MP_QSTR_PORT8C), MP_ROM_INT(PORT8C) },
    { MP_ROM_QSTR(MP_QSTR_PORT8D), MP_ROM_INT(PORT8D) },    

    { MP_ROM_QSTR(MP_QSTR_PORT16A), MP_ROM_INT(PORT16A) },
    { MP_ROM_QSTR(MP_QSTR_PORT16B), MP_ROM_INT(PORT16B) },

    { MP_ROM_QSTR(MP_QSTR_PORT32A), MP_ROM_INT(PORT32A) },    

  //{ MP_ROM_QSTR(MP_QSTR_MODE_INPUT),  MP_ROM_INT(PORT_MODE_INPUT) },    
  //{ MP_ROM_QSTR(MP_QSTR_MODE_OUTPUT), MP_ROM_INT(PORT_MODE_OUTPUT)},    
  
};
STATIC MP_DEFINE_CONST_DICT(gpio_module_globals, gpio_module_globals_table);

const mp_obj_module_t gpio_module = 
{
    .base    = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&gpio_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_gpio, gpio_module);


MP_REGISTER_ROOT_POINTER(void *machine_pin_irq_objects[16]);