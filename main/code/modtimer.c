#include "../../py/runtime.h"
#include "header.h"


/*************************************************************************/
STATIC mp_obj_t delay_delayuSec(mp_obj_t a) 
{
  FndelayuSec(MP_OBJ_SMALL_INT_VALUE(a));
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(delay_delayuSec_obj, delay_delayuSec);

/*************************************************************************/
STATIC mp_obj_t delay_delaymSec(mp_obj_t a) 
{
  FndelayuSec(MP_OBJ_SMALL_INT_VALUE(a));
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(delay_delaymSec_obj, delay_delaymSec);

/*************************************************************************/
STATIC mp_obj_t delay_delaySec(mp_obj_t a) 
{
  FndelaySec(MP_OBJ_SMALL_INT_VALUE(a));
  return mp_const_none; 
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(delay_delaySec_obj, delay_delaySec);

/*************************************************************************/
/*************************************************************************/
STATIC const mp_rom_map_elem_t delay_module_globals_table[] = 
{

    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_delay) },
    { MP_ROM_QSTR(MP_QSTR_delayuSec),  MP_ROM_PTR(&delay_delayuSec_obj) },
    { MP_ROM_QSTR(MP_QSTR_delaymSec),  MP_ROM_PTR(&delay_delaymSec_obj) },
    { MP_ROM_QSTR(MP_QSTR_delaySec),   MP_ROM_PTR(&delay_delaySec_obj) },
};
STATIC MP_DEFINE_CONST_DICT(delay_module_globals, delay_module_globals_table);

const mp_obj_module_t delay_module = 
{
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&delay_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_delay, delay_module);
