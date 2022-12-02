
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

    #include "../../py/runtime.h"
    #include "header.h"


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
STATIC mp_obj_t gpio_PortRead(mp_obj_t a) 
{ 
    //return MP_OBJ_SMALL_INT_VALUE(FnPortWrite(MP_OBJ_SMALL_INT_VALUE(a)));
    return MP_OBJ_NEW_SMALL_INT( FnPortRead(MP_OBJ_SMALL_INT_VALUE(a)));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gpio_PortRead_obj, gpio_PortRead);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t gpio_PortWrite(mp_obj_t a, mp_obj_t b) 
{
   //return MP_OBJ_NEW_SMALL_INT(FnPortWrite(MP_OBJ_SMALL_INT_VALUE(a),MP_OBJ_SMALL_INT_VALUE(b)));
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
STATIC const mp_rom_map_elem_t gpio_module_globals_table[] = 
{
    /*Module head*/
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_gpio) },
    { MP_ROM_QSTR(MP_QSTR_PortRead),  MP_ROM_PTR(&gpio_PortRead_obj)  },
    { MP_ROM_QSTR(MP_QSTR_PortWrite), MP_ROM_PTR(&gpio_PortWrite_obj) },

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

    { MP_ROM_QSTR(MP_QSTR_MODE_INPUT),  MP_ROM_INT(PORT_MODE_INPUT)  },    
    { MP_ROM_QSTR(MP_QSTR_MODE_OUTPUT), MP_ROM_INT(PORT_MODE_OUTPUT) },    
  
};
STATIC MP_DEFINE_CONST_DICT(gpio_module_globals, gpio_module_globals_table);

const mp_obj_module_t gpio_module = 
{
    .base    = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&gpio_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_gpio, gpio_module);