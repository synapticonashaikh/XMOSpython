
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

  #define APPEND                   (1<<0)
  /* If the opened file exists, it will be truncated to zero length before opened */
  #define TRUNC                    (1<<1)
  /* The opened file may only be read */

  #define CMD_FREAD     (uint8_t)2
  #define CMD_FWRITE    (uint8_t)3


  #define NO_ERROR        (int8_t)0
  #define ERROR_BUSY      (int8_t)-10
  #define ERROR_FILENAME  (int8_t)-20
  #define ERROR_FILELEN   (int8_t)-21

  #define BUFFER_LEN      (uint16_t)300

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

#if defined(SOMANET_SOFTWARE_MAIN)
    char ucFileName [(uint8_t)30]= "unknown.txt";
    char ucRdWrBuffer [BUFFER_LEN];
    uint16_t  ucFileStartingAdd = RESET;
    uint16_t  ucFileReadLength  = RESET;
    uint8_t   ucFileCommad      = RESET;    
#elif defined(USE_LOCAL_MAIN)
    char ucDummyFile[BUFFER_LEN]="The data is a dummy. It is read from a dummy buffer to test the modules and function.\n";
#endif
    uint32_t  uiFileFlag        = RESET;

/* ----------------------------------------------------------------------------
 *                           important command
 * ----------------------------------------------------------------------------
*/

/* ----------------------------------------------------------------------------
 *                           Fnction Definitions
 * ----------------------------------------------------------------------------
*/

/***********************************************************************
 * Function Name: file_fread 
 * Arguments	  : three object argument, a is a file name and b is a 
 *                starting point and c is a length of 
 * Return Type	: error code (int)
 * Details	    : To open the file present in storage  
 * *********************************************************************/
STATIC mp_obj_t file_fread(mp_obj_t a,mp_obj_t b,mp_obj_t c)
{

  if( strlen((char *)mp_obj_str_get_str(a)) > (uint8_t)30 )
     { mp_raise_ValueError(MP_ERROR_TEXT("File name is too long")); 
       return MP_OBJ_NEW_SMALL_INT(ERROR_FILENAME); }

  if( MP_OBJ_SMALL_INT_VALUE(c) > BUFFER_LEN )  
    { mp_raise_ValueError(MP_ERROR_TEXT("File length is invalid")); 
      return MP_OBJ_NEW_SMALL_INT(ERROR_FILELEN); }

#if defined(SOMANET_SOFTWARE_MAIN)
      strcpy(ucFileName,(char *)mp_obj_str_get_str(a));
      ucFileStartingAdd   = MP_OBJ_SMALL_INT_VALUE(b);     
      ucFileReadLength    = MP_OBJ_SMALL_INT_VALUE(c);
#endif 

#if defined(SOMANET_SOFTWARE_MAIN)
      ucFileCommad = CMD_FREAD;     
      while( ucFileCommad != RESET )
        { FndelaymSec((uint8_t)1); }
      return  mp_obj_new_str(ucRdWrBuffer,ucFileReadLength);        
#elif defined(USE_LOCAL_MAIN)
      return  mp_obj_new_str(ucDummyFile,MP_OBJ_SMALL_INT_VALUE(c));
#endif
}STATIC MP_DEFINE_CONST_FUN_OBJ_3(file_fread_obj, file_fread);


/***********************************************************************
 * Function Name: file_fopen 
 * Arguments	  : two object argument, a is a file name and b is a flags
 * Return Type	: error code (int)
 * Details	    : To open the file present in storage
 * *********************************************************************/
STATIC mp_obj_t file_fwrite(mp_obj_t a,mp_obj_t b,mp_obj_t c)
{

  if( strlen((char *)mp_obj_str_get_str(a)) > (uint8_t)30 )
     { mp_raise_ValueError(MP_ERROR_TEXT("File name is too long")); 
       return MP_OBJ_NEW_SMALL_INT(ERROR_FILENAME); }

  if( strstr((char *)mp_obj_str_get_str(a),"PythonLog.log") == NULL )
     { mp_raise_ValueError(MP_ERROR_TEXT("Invalid file name")); 
       return MP_OBJ_NEW_SMALL_INT(ERROR_FILENAME); }

  switch (MP_OBJ_SMALL_INT_VALUE(b))
  {
    case APPEND: break; case TRUNC: break;
    default: mp_raise_ValueError(MP_ERROR_TEXT("Invalid file flag")); 
    return MP_OBJ_NEW_SMALL_INT(ERROR_FILENAME);
  }

  if( strlen((char *)mp_obj_str_get_str(c))  > BUFFER_LEN )  
    { mp_raise_ValueError(MP_ERROR_TEXT("File is too large")); 
      return MP_OBJ_NEW_SMALL_INT(ERROR_FILELEN); }

      uiFileFlag   = MP_OBJ_SMALL_INT_VALUE(b);
#if defined(SOMANET_SOFTWARE_MAIN)
      strcpy(ucFileName,(char *)mp_obj_str_get_str(a));      
      strcpy(ucRdWrBuffer,(char *)mp_obj_str_get_str(c));
      ucFileCommad = CMD_FWRITE;     
      while( ucFileCommad != RESET )
           { FndelaymSec((uint8_t)1); }     
#elif defined(USE_LOCAL_MAIN)
      if (uiFileFlag == TRUNC)
          strcpy(ucDummyFile,(char *)mp_obj_str_get_str(c));
      else
          {
            if((strlen(ucDummyFile) + strlen((char *)mp_obj_str_get_str(c))) < BUFFER_LEN ) 
                strcat(ucDummyFile,(char *)mp_obj_str_get_str(c));
          }
#endif 

return MP_OBJ_NEW_SMALL_INT(strlen((char *)mp_obj_str_get_str(c)));
}STATIC MP_DEFINE_CONST_FUN_OBJ_3(file_fwrite_obj, file_fwrite);

/***********************************************************************
 * Function Name: file_GetFileDescriptor 
 * Arguments	  : none
 * Return Type	: file descriptor (int)
 * Details	    : As our storage system is slow, we shall use this 
 *                function to get the descriptor  
 * *********************************************************************/
STATIC const mp_rom_map_elem_t file_module_globals_table[] = 
{
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_file) },
    { MP_ROM_QSTR(MP_QSTR_fread),  MP_ROM_PTR(&file_fread_obj) },
    { MP_ROM_QSTR(MP_QSTR_fwrite), MP_ROM_PTR(&file_fwrite_obj) },

    { MP_ROM_QSTR(MP_QSTR_APPEND), MP_ROM_INT(APPEND)},
    { MP_ROM_QSTR(MP_QSTR_TRUNC),  MP_ROM_INT(TRUNC) },

};STATIC MP_DEFINE_CONST_DICT(file_module_globals, file_module_globals_table);

const mp_obj_module_t file_module = 
{
    .base    = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&file_module_globals,
};MP_REGISTER_MODULE(MP_QSTR_file, file_module);

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
/* STATIC mp_obj_t board_clockinfo(void) 
{
    int a = 1;
    char buffer [50]= {'\0'}; 
    sprintf(buffer,"this is just for test=%d\n\r",a);
    mp_printf(&mp_plat_print, buffer);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(board_clockinfo_obj, board_clockinfo); */

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
/*STATIC mp_obj_t board_healthinfo(mp_obj_t a) 
{
  int abc = 200;
   return MP_OBJ_NEW_SMALL_INT(abc);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(board_healthinfo_obj, board_healthinfo); */

/***********************************************************************
 * Function Name : main 
 * Arguments	 : void
 * Return Type	 : int
 * Details	 : main function, start of the code 
 * *********************************************************************/
/*STATIC mp_obj_t board_add(mp_obj_t a, mp_obj_t b) 
{
   return MP_OBJ_NEW_SMALL_INT(MP_OBJ_SMALL_INT_VALUE(a) + MP_OBJ_SMALL_INT_VALUE(b));
} STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_add_obj, board_add); */

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
/*STATIC mp_obj_t board_mul(mp_obj_t a, mp_obj_t b) 
{    
   return mp_obj_new_float((mp_float_t)(mp_obj_float_get(a) * mp_obj_float_get(b) ));
}STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_mul_obj, board_mul); */
#endif

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
/* STATIC mp_obj_t board_mul10(mp_obj_t a) 
{
   mp_float_t f;
   mp_obj_get_float_maybe(a,&f);
   return mp_obj_new_float(f * 10);
} STATIC MP_DEFINE_CONST_FUN_OBJ_1(board_mul10_obj, board_mul10); */
#endif

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
/*STATIC mp_obj_t board_strcat(mp_obj_t a, mp_obj_t b) 
{
  strcat((char *)mp_obj_str_get_str(a),mp_obj_str_get_str(b));
  return mp_obj_new_str(mp_obj_str_get_str(a),strlen(mp_obj_str_get_str(a)));

}STATIC MP_DEFINE_CONST_FUN_OBJ_2(board_strcat_obj, board_strcat); */

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code 
 * *********************************************************************/
/*STATIC const mp_rom_map_elem_t board_module_globals_table[] = 
{
     { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_board) },
     { MP_ROM_QSTR(MP_QSTR_clockinfo),    MP_ROM_PTR(&board_clockinfo_obj) },
     { MP_ROM_QSTR(MP_QSTR_healthinfo),   MP_ROM_PTR(&board_healthinfo_obj)},
     { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&board_add_obj) },
    #if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT   
        { MP_ROM_QSTR(MP_QSTR_mul),   MP_ROM_PTR(&board_mul_obj) },    
        { MP_ROM_QSTR(MP_QSTR_mul10), MP_ROM_PTR(&board_mul10_obj) },
    #endif    
     { MP_ROM_QSTR(MP_QSTR_strcat), MP_ROM_PTR(&board_strcat_obj)},

};STATIC MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);

const mp_obj_module_t board_module = 
{
    .base    = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&board_module_globals,
};MP_REGISTER_MODULE(MP_QSTR_board, board_module);*/
