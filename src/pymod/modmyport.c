
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
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t myport_info(void) 
{
    mp_printf(&mp_plat_print, "Just a debugg message to print\n");
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(myport_info_obj, myport_info);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC const mp_rom_map_elem_t myport_module_globals_table[] = 
{
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_myport) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&myport_info_obj) },
};
STATIC MP_DEFINE_CONST_DICT(myport_module_globals, myport_module_globals_table);

const mp_obj_module_t myport_module = 
{
    .base    = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&myport_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_myport, myport_module);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t board_clockinfo(void) 
{
    int a = 1;
    char buffer [50]= {'\0'}; 
    sprintf(buffer,"this is just for test=%d\n\r",a);
    mp_printf(&mp_plat_print, buffer);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(board_clockinfo_obj, board_clockinfo);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t board_healthinfo(mp_obj_t a) 
{
  int abc = 200;
   return MP_OBJ_NEW_SMALL_INT(abc);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(board_healthinfo_obj, board_healthinfo);

/***********************************************************************
 * Function Name : main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t board_add(mp_obj_t a, mp_obj_t b) 
{
   return MP_OBJ_NEW_SMALL_INT(MP_OBJ_SMALL_INT_VALUE(a) + MP_OBJ_SMALL_INT_VALUE(b));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_add_obj, board_add);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
STATIC mp_obj_t board_mul(mp_obj_t a, mp_obj_t b) 
{    
   return mp_obj_new_float((mp_float_t)(mp_obj_float_get(a) * mp_obj_float_get(b) ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_mul_obj, board_mul);
#endif

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
STATIC mp_obj_t board_mul10(mp_obj_t a) 
{
   mp_float_t f;
   mp_obj_get_float_maybe(a,&f);
   return mp_obj_new_float(f * 10);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(board_mul10_obj, board_mul10);
#endif

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t board_strcat(mp_obj_t a, mp_obj_t b) 
{
  strcat((char *)mp_obj_str_get_str(a),mp_obj_str_get_str(b));
  return mp_obj_new_str(mp_obj_str_get_str(a),strlen(mp_obj_str_get_str(a)));

}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_strcat_obj, board_strcat);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC const mp_rom_map_elem_t board_module_globals_table[] = 
{
     { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_board) },
     { MP_ROM_QSTR(MP_QSTR_clockinfo),  MP_ROM_PTR(&board_clockinfo_obj) },
     { MP_ROM_QSTR(MP_QSTR_healthinfo), MP_ROM_PTR(&board_healthinfo_obj)},
     { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&board_add_obj) },
    #if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT   
        { MP_ROM_QSTR(MP_QSTR_mul),   MP_ROM_PTR(&board_mul_obj) },    
        { MP_ROM_QSTR(MP_QSTR_mul10), MP_ROM_PTR(&board_mul10_obj) },
    #endif    
     { MP_ROM_QSTR(MP_QSTR_strcat), MP_ROM_PTR(&board_strcat_obj)},

};
STATIC MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);

const mp_obj_module_t board_module = 
{
    .base    = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&board_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_board, board_module);
