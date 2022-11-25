#include "py/runtime.h"
#include "header.h"


/*************************************************************************/
STATIC mp_obj_t delay_delay1us(void) 
{
    Fndelay1us();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_delay1us_obj, delay_delay1us);

/*************************************************************************/
STATIC mp_obj_t delay_delay10us(void) 
{
    Fndelay10us();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_delay10us_obj, delay_delay10us);

/*************************************************************************/
STATIC mp_obj_t delay_delay100us(void) 
{
    Fndelay100us();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_delay100us_obj, delay_delay100us);

/*************************************************************************/
STATIC mp_obj_t delay_delay1ms(void) 
{
    Fndelay1ms();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_delay1ms_obj, delay_delay1ms);


/*************************************************************************/
STATIC mp_obj_t delay_delay10ms(void) 
{
    Fndelay10ms();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_delay10ms_obj, delay_delay10ms);

/*************************************************************************/
STATIC mp_obj_t delay_delay100ms(void) 
{
    Fndelay100ms();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_delay100ms_obj, delay_delay100ms);

/*************************************************************************/
STATIC mp_obj_t delay_delay1s(void) 
{
    Fndelay1s();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(delay_delay1s_obj, delay_delay1s);

/*************************************************************************/
/*************************************************************************/
STATIC const mp_rom_map_elem_t delay_module_globals_table[] = 
{

    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_delay) },
    { MP_ROM_QSTR(MP_QSTR_delay1us),   MP_ROM_PTR(&delay_delay1us_obj) },
    { MP_ROM_QSTR(MP_QSTR_delay10us),  MP_ROM_PTR(&delay_delay10us_obj) },
    { MP_ROM_QSTR(MP_QSTR_delay100us), MP_ROM_PTR(&delay_delay100us_obj) },
    { MP_ROM_QSTR(MP_QSTR_delay1ms),   MP_ROM_PTR(&delay_delay1ms_obj) },
    { MP_ROM_QSTR(MP_QSTR_delay10ms),  MP_ROM_PTR(&delay_delay10ms_obj) },        
    { MP_ROM_QSTR(MP_QSTR_delay100ms), MP_ROM_PTR(&delay_delay100ms_obj) },
    { MP_ROM_QSTR(MP_QSTR_delay1s),    MP_ROM_PTR(&delay_delay1s_obj) },

};
STATIC MP_DEFINE_CONST_DICT(delay_module_globals, delay_module_globals_table);

const mp_obj_module_t delay_module = 
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&delay_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_delay, delay_module);
