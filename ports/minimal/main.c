#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "py/builtin.h"
#include "py/compile.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "shared/runtime/pyexec.h"
//#include "STdriver.h"

//this heap memroy stores the data
#define _STATIC_HEAP_SIZE  (uint16_t)3072

extern void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);
extern int  mp_hal_stdin_rx_chr  (void);


#if MICROPY_ENABLE_COMPILER
void do_str(const char *src, mp_parse_input_kind_t input_kind) 
{
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) 
       {
         mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
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

static char *stack_top;
#if MICROPY_ENABLE_GC
    static char heap[_STATIC_HEAP_SIZE];
#endif

int mp_main(void) 
{ 
    int stack_dummy;
    stack_top = (char *)&stack_dummy;

    #if MICROPY_ENABLE_GC
    gc_init(heap, heap + sizeof(heap));
    #endif
    mp_init();
// do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_FILE_INPUT);
// do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT); 
// do_str("3 * 5", MP_PARSE_FILE_INPUT);        
// do_str("for i in range(10):\r\n", MP_PARSE_SINGLE_INPUT); //  print(i)
// do_str("print('Hello World')", MP_PARSE_SINGLE_INPUT);       

    #if MICROPY_ENABLE_COMPILER
        #if MICROPY_REPL_EVENT_DRIVEN         
            pyexec_event_repl_init();
            for (;;) 
            {
                int c = mp_hal_stdin_rx_chr();
                if (pyexec_event_repl_process_char(c)) 
                {
                    break;
                }
            }
        #else
            pyexec_friendly_repl();
        #endif
     //do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
     //do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
    #else
    pyexec_frozen_module("frozentest.py");
    #endif
    mp_deinit();
    printf("closing the code!\n\r");
    return 0;

}

#if MICROPY_ENABLE_GC
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

