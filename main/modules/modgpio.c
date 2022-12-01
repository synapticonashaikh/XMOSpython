#include "../../py/runtime.h"
#include "header.h"



//#######################################################################################
STATIC mp_obj_t gpio_PortRead(mp_obj_t a) 
{ 
    //return MP_OBJ_SMALL_INT_VALUE(FnPortWrite(MP_OBJ_SMALL_INT_VALUE(a)));
    return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gpio_PortRead_obj, gpio_PortRead);

STATIC mp_obj_t gpio_PortWrite(mp_obj_t a, mp_obj_t b) 
{
   //return MP_OBJ_NEW_SMALL_INT(FnPortWrite(MP_OBJ_SMALL_INT_VALUE(a),MP_OBJ_SMALL_INT_VALUE(b)));
   FnPortWrite(MP_OBJ_SMALL_INT_VALUE(a),MP_OBJ_SMALL_INT_VALUE(b));
   return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(gpio_PortWrite_obj, gpio_PortWrite);


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