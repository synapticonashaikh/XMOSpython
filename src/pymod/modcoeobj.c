
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
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_SetObjectValue(mp_obj_t arg_in) 
{
    /*check if the list is of 4 element*/
 if (mp_obj_get_int(mp_obj_len(arg_in)) == (uint8_t)4)
  {    
        mp_int_t  index = RESET, subindex = RESET, length = RESET;      
        mp_obj_t  item, iterable = mp_getiter(arg_in, NULL); uint8_t OBJ[50];
        memset(OBJ,RESET,sizeof(OBJ));

        /*parse the first element of the list*/
         item  = mp_iternext(iterable);
    if ( item != MP_OBJ_STOP_ITERATION || item != MP_OBJ_NULL )
         index = mp_obj_get_int(item);
        /*parse the Second element of the list*/    
        item  = mp_iternext(iterable);
    if (item != MP_OBJ_STOP_ITERATION  || item != MP_OBJ_NULL )
        subindex = mp_obj_get_int(item);
        /*parse the third element [nested list] of the list*/ //[,['a','b']]     
        item  = mp_iternext(iterable);
    if (item != MP_OBJ_STOP_ITERATION || item != MP_OBJ_NULL )
      { 
        for (uint8_t ucLoop = RESET; ucLoop < mp_obj_get_int(mp_obj_len(item)) ; ucLoop++ ) { 
             OBJ[ucLoop] = mp_obj_get_int(mp_obj_subscr(item, MP_OBJ_NEW_SMALL_INT(ucLoop), MP_OBJ_SENTINEL)); }
      }
        /*parse the fourth element of the list*/
        item  = mp_iternext(iterable);
    if (item != MP_OBJ_STOP_ITERATION  || item != MP_OBJ_NULL )
        length = mp_obj_get_int(item);
    /*set the object ditctonary!*/
    FnSetObjectValue(index, subindex, length, OBJ );
  }
  else mp_raise_ValueError(MP_ERROR_TEXT("List must have length of exactly 4"));
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(OBJDITC_SetObjectValue_obj, OBJDITC_SetObjectValue);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_WriteControlWord(mp_obj_t cw) 
{
  
      FnSetControlword(MP_OBJ_SMALL_INT_VALUE(cw));
      return mp_const_none;
  
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(OBJDITC_WriteControlWord_obj, OBJDITC_WriteControlWord);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_ReadControlWord(void) 
{
   return MP_OBJ_NEW_SMALL_INT(FnGetControlword( ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(OBJDITC_ReadControlWord_obj, OBJDITC_ReadControlWord);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_ReadErrorStatus(void) 
{
   return MP_OBJ_NEW_SMALL_INT(FnGetErrorStatus( ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(OBJDITC_ReadErrorStatus_obj, OBJDITC_ReadErrorStatus);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_ReadObjectValue(mp_obj_t index, mp_obj_t subindex, mp_obj_t capacity) 
{
       return MP_OBJ_NEW_SMALL_INT
      (FnReadObject(MP_OBJ_SMALL_INT_VALUE(index),
       MP_OBJ_SMALL_INT_VALUE(subindex),
       MP_OBJ_SMALL_INT_VALUE(capacity)));
    
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(OBJDITC_ReadObjectValue_obj, OBJDITC_ReadObjectValue);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_SetModesofOperation(mp_obj_t modes) 
{
        FnSetModesOfOperation(MP_OBJ_SMALL_INT_VALUE(modes));
        return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(OBJDITC_SetModesofOperation_obj, OBJDITC_SetModesofOperation);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_ReadModesofOperation(void) 
{
    return MP_OBJ_NEW_SMALL_INT(FnGetModesOfOperation( ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(OBJDITC_ReadModesofOperation_obj, OBJDITC_ReadModesofOperation);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_SetTargetTorque(mp_obj_t torque) 
{
    FnSetTargetTorque(MP_OBJ_SMALL_INT_VALUE(torque));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(OBJDITC_SetTargetTorque_obj, OBJDITC_SetTargetTorque);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_SetTargetVelocity(mp_obj_t Velocity) 
{
    FnSetTargetVelocity(MP_OBJ_SMALL_INT_VALUE(Velocity));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(OBJDITC_SetTargetVelocity_obj, OBJDITC_SetTargetVelocity);


/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_ReadTargetTorque(void) 
{
    return MP_OBJ_NEW_SMALL_INT(FnGetTargetTorque( ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(OBJDITC_ReadTargetTorque_obj, OBJDITC_ReadTargetTorque);

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC mp_obj_t OBJDITC_I2TEnDs(mp_obj_t I2T_A) 
{
   FnSetI2TEnableDisable(MP_OBJ_SMALL_INT_VALUE(I2T_A));
   return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(OBJDITC_I2TEnDs_obj, OBJDITC_I2TEnDs);


/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
STATIC const mp_rom_map_elem_t OBJDITC_module_globals_table[ ] = 
{

    { MP_OBJ_NEW_QSTR (MP_QSTR___name__)   , MP_OBJ_NEW_QSTR(MP_QSTR_OBJDITC)},
    { MP_ROM_QSTR(MP_QSTR_SetObjectValue)  , MP_ROM_PTR(&OBJDITC_SetObjectValue_obj)},
    { MP_ROM_QSTR(MP_QSTR_ReadObjectValue) , MP_ROM_PTR(&OBJDITC_ReadObjectValue_obj)},    
    { MP_ROM_QSTR(MP_QSTR_WriteControlWord), MP_ROM_PTR(&OBJDITC_WriteControlWord_obj)},
    { MP_ROM_QSTR(MP_QSTR_ReadControlWord) , MP_ROM_PTR(&OBJDITC_ReadControlWord_obj)},
    { MP_ROM_QSTR(MP_QSTR_ReadErrorStatus) , MP_ROM_PTR(&OBJDITC_ReadErrorStatus_obj)},    
    { MP_ROM_QSTR(MP_QSTR_WriteModesofOperation), MP_ROM_PTR(&OBJDITC_SetModesofOperation_obj)},    
    { MP_ROM_QSTR(MP_QSTR_ReadModesofOperation),  MP_ROM_PTR(&OBJDITC_ReadModesofOperation_obj)}, 
    { MP_ROM_QSTR(MP_QSTR_SetTargetVelocity), MP_ROM_PTR(&OBJDITC_SetTargetVelocity_obj)},      
    { MP_ROM_QSTR(MP_QSTR_SetTargetTorque),   MP_ROM_PTR(&OBJDITC_SetTargetTorque_obj)},        
    { MP_ROM_QSTR(MP_QSTR_ReadTargetTorque),  MP_ROM_PTR(&OBJDITC_ReadTargetTorque_obj)},   
    { MP_ROM_QSTR(MP_QSTR_I2TEnDs),           MP_ROM_PTR(&OBJDITC_I2TEnDs_obj)},   

};
STATIC MP_DEFINE_CONST_DICT(OBJDITC_module_globals, OBJDITC_module_globals_table);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
const mp_obj_module_t OBJDITC_module = 
{
    .base    = { &mp_type_module },
    .globals = (  mp_obj_dict_t *)&OBJDITC_module_globals,
};
MP_REGISTER_MODULE(MP_QSTR_OBJDITC, OBJDITC_module);
