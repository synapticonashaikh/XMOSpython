#include "py/runtime.h"
#include <stdio.h>
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "STdriver.h"
#include <stdarg.h>
#include <stddef.h>

//#######################################################################################
STATIC mp_obj_t myport_info(void) 
{

    mp_printf(&mp_plat_print, "info about my import=100\n");
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(myport_info_obj, myport_info);


STATIC const mp_rom_map_elem_t myport_module_globals_table[] = 
{
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_myport) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&myport_info_obj) },

};
STATIC MP_DEFINE_CONST_DICT(myport_module_globals, myport_module_globals_table);

const mp_obj_module_t myport_module = 
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&myport_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_myport, myport_module);

//#######################################################################################

STATIC mp_obj_t board_clockinfo(void) 
{
    char buffer [150]= {'\0'}; 
   // int a = 1;
    sprintf(buffer,"this is just for test\n\r");    /*this is working*/    
    //sprintf(buffer,"this is just for test=%d\n\r",a); /*this is not working*/
    mp_printf(&mp_plat_print, buffer);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(board_clockinfo_obj, board_clockinfo);

STATIC mp_obj_t board_healthinfo(void) 
{
   return MP_OBJ_NEW_SMALL_INT(100);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(board_healthinfo_obj, board_healthinfo);


STATIC mp_obj_t board_add(mp_obj_t a, mp_obj_t b) 
{
   mp_printf(&mp_plat_print, "Addition of %d and %d is %d\n\r",
   MP_OBJ_SMALL_INT_VALUE(a), MP_OBJ_SMALL_INT_VALUE(b), 
   MP_OBJ_SMALL_INT_VALUE(a)+ MP_OBJ_SMALL_INT_VALUE(b)); 

   return MP_OBJ_NEW_SMALL_INT(MP_OBJ_SMALL_INT_VALUE(a)+ MP_OBJ_SMALL_INT_VALUE(b));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_add_obj, board_add);

#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
STATIC mp_obj_t board_mul(mp_obj_t a, mp_obj_t b) 
{
    
   mp_printf(&mp_plat_print, "Multiplication of %.2f and %.2f is %.2f\n\r",
   (double)(mp_obj_float_get(a)),(double)(mp_obj_float_get(b)), (double)(mp_obj_float_get(a) * mp_obj_float_get(b) ) ); 

   return mp_obj_new_float((mp_float_t)(mp_obj_float_get(a) * mp_obj_float_get(b) ));

}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_mul_obj, board_mul);
#endif

#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
STATIC mp_obj_t board_mul10(mp_obj_t a) 
{
   mp_float_t f,r;
   bool value; 
   value = mp_obj_get_float_maybe(a,&f);
   r = f * 10 ;
   mp_printf(&mp_plat_print, "[%d]Multiplication of %.2f and 10.00 is %.2f\n\r",
   value, (double)f,(double)r ); 
   return mp_obj_new_float(r);

}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(board_mul10_obj, board_mul10);
#endif

STATIC mp_obj_t board_strcat(mp_obj_t a, mp_obj_t b) 
{

   strcat((char *)mp_obj_str_get_str(a),mp_obj_str_get_str(b));
   mp_printf(&mp_plat_print, "strcat is %s\n\r",
   mp_obj_str_get_str(a)); 
   return mp_obj_new_str(mp_obj_str_get_str(a),strlen(mp_obj_str_get_str(a)));

}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_strcat_obj, board_strcat);



STATIC const mp_rom_map_elem_t board_module_globals_table[] = 
{
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_board) },
    { MP_ROM_QSTR(MP_QSTR_clockinfo), MP_ROM_PTR(&board_clockinfo_obj) },
    { MP_ROM_QSTR(MP_QSTR_healthinfo), MP_ROM_PTR(&board_healthinfo_obj) },
    { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&board_add_obj) },
 #if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT   
    { MP_ROM_QSTR(MP_QSTR_mul), MP_ROM_PTR(&board_mul_obj) },    
    { MP_ROM_QSTR(MP_QSTR_mul10),  MP_ROM_PTR(&board_mul10_obj) },
#endif    
    { MP_ROM_QSTR(MP_QSTR_strcat), MP_ROM_PTR(&board_strcat_obj)},

};
STATIC MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);

const mp_obj_module_t board_module = 
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&board_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_board, board_module);