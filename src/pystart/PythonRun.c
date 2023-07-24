/**************************************************************************************
 **************************************************************************************
 ______________________________________________________________________________________

  Company:
	Synapticon GmbH (https://www.synapticon.com/)
 ______________________________________________________________________________________

  File Name:
	Datatype.xc
 ______________________________________________________________________________________

  Summary:
    This file contains the source code for testing all the data types and 
    their memory allocated size assigned by the xc compiler.
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
    // Heap memroy to store the data of 8 KBytes
    #define _STATIC_HEAP_SIZE (uint16_t)8*1024

    #define  PARSE_SINGLE_INPUT   0
    #define  PARSE_FILE_INPUT     1
    #define  PARSE_EVAL_INPUT     2

/* ----------------------------------------------------------------------------
 *                           INCLUDE
 * ----------------------------------------------------------------------------
*/
    #include "header.h"

    #include "py/builtin.h"
    #include "py/compile.h"
    #include "py/runtime.h"
    #include "py/repl.h"
    #include "py/gc.h"
    #include "py/mperrno.h"
    #include "py/pyexec.h"
    #include "py/readline.h"
    #include "py/interrupt_char.h"
    #include "py/persistentcode.h"
    #include "py/bc.h"
    #include "py/reader.h"

    #define  PARSE_SINGLE_INPUT   0
    #define  PARSE_FILE_INPUT     1
    #define  PARSE_EVAL_INPUT     2

/* ----------------------------------------------------------------------------
 *                          EXTERNAL FUNCTION
 * ----------------------------------------------------------------------------
*/

    extern void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);
    extern int  mp_hal_stdin_rx_chr  (void);

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
    static char *stack_top;
    uint8_t ucGCInitFlag = RESET;
    #if MICROPY_ENABLE_GC
        static char heap[_STATIC_HEAP_SIZE];
    #endif   

/* ----------------------------------------------------------------------------
 *                          FUNCTION DEFINITION
 * ----------------------------------------------------------------------------
*/
/***********************************************************************
 * Function Name: main
 * Arguments	: void
 * Return Type	: int
 * Details	: main function, start of the code
 * *********************************************************************/
#if MICROPY_ENABLE_COMPILER
void do_str(const char *src, mp_parse_input_kind_t input_kind)
{
    nlr_buf_t nlr;
    if ( nlr_push(&nlr) == 0)
       {
         mp_lexer_t *lex  = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
         qstr source_name = lex->source_name;
         mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
         mp_obj_t module_fun = mp_compile(&parse_tree, source_name, true);
         mp_call_function_0(module_fun);
         nlr_pop( );
       }
    else
       {
         // uncaught exception
         mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
       }
}
#endif

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
#if defined(SOMANET_SOFTWARE_MAIN) || defined(USE_LOCAL_MAIN)
        #pragma stackfunction 2000
#endif
void FnStopTheScript(void)
{
  mp_sched_lock( ); gc_lock( );
  mp_raise_type(&mp_type_SystemExit);
  mp_sched_unlock(); gc_unlock( );

  /*deinit*/ 
  mp_deinit( );
}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
#if defined(SOMANET_SOFTWARE_MAIN) || defined(USE_LOCAL_MAIN)
        #pragma stackfunction 1000
#endif
int FnMPInterpreterConsole(void)
{
    int stack_dummy;
    stack_top = (char *)&stack_dummy;

    #if MICROPY_ENABLE_GC
    gc_init(heap, heap + sizeof(heap));
    #endif
    mp_init( );

    #if MICROPY_ENABLE_COMPILER
        #if MICROPY_REPL_EVENT_DRIVEN
            pyexec_event_repl_init( );
            for (;;)
            {
                int c = mp_hal_stdin_rx_chr( );
                if (pyexec_event_repl_process_char(c))
                {
                    break;
                }
            }
        #else
            pyexec_friendly_repl( );
        #endif
    #else
        pyexec_frozen_module("frozentest.py",true);
    #endif
    mp_deinit( );
    printf("closing the code!\n\r");
    return 0;

}

/***********************************************************************
 * Function Name: main
 * Arguments	: void
 * Return Type	: int
 * Details	: main function, start of the code
 * *********************************************************************/
#if defined(SOMANET_SOFTWARE_MAIN) || defined(USE_LOCAL_MAIN)
    #pragma stackfunction 1000
#endif
char * FnRunTheCommand(char *ByteCode, uint32_t CodeLen, uint8_t BytecodeORStr)
{

    int stack_dummy;
    stack_top = (char *)&stack_dummy;    
    static char *ret  = "Sucess!";

    #if MICROPY_ENABLE_GC
    if (ucGCInitFlag == RESET)
    {   ucGCInitFlag = SET;
        gc_init(heap, heap + sizeof(heap));
        FnEnableTheTimerIRQ( ); //enable the timer
    }
    #endif
    /*init the mp stack*/
       mp_init( );

    if (BytecodeORStr == SET)
    {
      #ifdef USE_LOCAL_MAIN
            printf("Script:\n%s",(char *)ByteCode, strlen(ByteCode));
      #endif
      #if MICROPY_ENABLE_COMPILER
          do_str(ByteCode, PARSE_FILE_INPUT);
      #endif
    }
    else
    {
        FnEnableTheTimerIRQ( ); //enable the timer interrupt
        mp_reader_t reader;
        mp_reader_new_mem(&reader,(byte *)ByteCode, CodeLen, 0);
        mp_module_context_t *context = m_new_obj(mp_module_context_t);
        context->module.globals = mp_globals_get();
        mp_compiled_module_t compiled_module;
        compiled_module.context = context;
        mp_raw_code_load(&reader, &compiled_module);
        mp_obj_t module_fun = mp_make_function_from_raw_code(compiled_module.rc, context, NULL);
        mp_call_function_0(module_fun);
    }

    /*deinit*/ 
    mp_deinit( );
    return ret;
}

/***********************************************************************
 * Function Name: main
 * Arguments	: void
 * Return Type	: int
 * Details	: main function, start of the code
 * *********************************************************************/
#if MICROPY_ENABLE_GC
#if defined(SOMANET_SOFTWARE_MAIN) || defined(USE_LOCAL_MAIN)
    #pragma stackfunction 1000
#endif
void gc_collect(void)
{
    // WARNING: This gc_collect implementation doesn't try to get root
    // pointers from CPU registers, and thus may function incorrectly.
    void *dummy;
    gc_collect_start( );
    gc_collect_root(&dummy, ((mp_uint_t)stack_top - (mp_uint_t)&dummy) / sizeof(mp_uint_t));
    gc_collect_end( );
    //printing the memory remaining is not necessary
    //gc_dump_info( );
}
#endif

/***********************************************************************
 * Function Name: main
 * Arguments	: void
 * Return Type	: int
 * Details	: main function, start of the code
 * *********************************************************************/
mp_lexer_t *mp_lexer_new_from_file(const char *filename)
{  mp_raise_OSError(MP_ENOENT); }

mp_import_stat_t mp_import_stat(const char *path)
{ return MP_IMPORT_STAT_NO_EXIST;}

void nlr_jump_fail(void *val)
{ while (1) {  }; }

void NORETURN __fatal_error(const char *msg)
{ while (1) {  }; }

#ifndef NDEBUG
void MP_WEAK __assert_func(const char *file, int line, const char *func, const char *expr) {
    printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif

