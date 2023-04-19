/**************************************************************************************
 **************************************************************************************
 ______________________________________________________________________________________

  Company:
	Synapticon GmbH (https://www.synapticon.com/)
 ______________________________________________________________________________________

  File Name:
	header.h
 ______________________________________________________________________________________

  Summary:
    This file contains all the definitions, includes, and extensions required 
    to run other source code.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __interrupt_h__
#define __interrupt_h__

/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
*/
  #include "py/mphal.h"
  #include "py/mpirq.h"
  #include "py/obj.h"
  #include "header.h"
  #include "py/runtime.h"
  #include "mpconfig.h"
  

#define store_args0(c) \
  asm("kentsp 20; stw %0, sp[1]; krestsp 20"::"r"(c));

#define store_args1(c,x) \
  asm("kentsp 20; stw %0, sp[1]; stw %1, sp[2]; krestsp 20"::"r"(c),"r"(x));

#define store_args2(c,x0,x1)       \
  asm("kentsp 22; stw %0, sp[1];" \
      "stw %1, sp[2];" \
      "stw %2, sp[3];"  \
      " krestsp 22"::"r"(c),"r"(x0),"r"(x1));

#define store_args3(c,x0,x1,x2)   \
  asm("kentsp 22; stw %0, sp[1];" \
      "stw %1, sp[2];" \
      "stw %2, sp[3];"  \
      "stw %3, sp[4];"  \
      " krestsp 22"::"r"(c),"r"(x0),"r"(x1),"r"(x2));

#define load_args0(f) \
  "ldw r0, sp[1]\n"

#define load_args1(f)\
      "ldw r0, sp[1]\n" \
      "ldw r1, sp[2]\n"

#define load_args2(f)\
      "ldw r0, sp[1]\n" \
      "ldw r1, sp[2]\n" \
      "ldw r2, sp[3]\n"

#define load_args3(f)\
      "ldw r0, sp[1]\n" \
      "ldw r1, sp[2]\n" \
      "ldw r2, sp[3]\n" \
      "ldw r3, sp[4]\n"

#define save_state(f,args)                         \
  ".linkset __"#f"_handler_r0_save, "#args"+12\n"   \
  "stw r0, sp[" "__"#f"_handler_r0_save" "]\n" \
  ".linkset __"#f"_handler_r1_save, "#args"+13\n"   \
  "stw r1, sp[" "__"#f"_handler_r1_save" "]\n" \
  ".linkset __"#f"_handler_r2_save, "#args"+2\n"   \
  "stw r2, sp[" "__"#f"_handler_r2_save" "]\n" \
  ".linkset __"#f"_handler_r3_save, "#args"+3\n"   \
  "stw r3, sp[" "__"#f"_handler_r3_save" "]\n" \
  ".linkset __"#f"_handler_r11_save, "#args"+11\n"   \
  "stw r11, sp[" "__"#f"_handler_r11_save" "]\n" \
  ".linkset __"#f"_handler_lr_save, "#args"+14\n"   \
  "stw lr, sp[" "__"#f"_handler_lr_save" "]\n"

#define restore_state(f,args)                  \
  "ldw r0, sp[" "__"#f"_handler_r0_save" "]\n" \
  "ldw r1, sp[" "__"#f"_handler_r1_save" "]\n" \
  "ldw r2, sp[" "__"#f"_handler_r2_save" "]\n" \
  "ldw r3, sp[" "__"#f"_handler_r3_save" "]\n" \
  "ldw r11, sp[" "__"#f"_handler_r11_save" "]\n" \
  "ldw lr, sp[" "__"#f"_handler_lr_save" "]\n"


#define STRINGIFY0(x) #x
#define STRINGIFY(x) STRINGIFY0(x)

#define ENABLE_INTERRUPTS() asm("setsr " STRINGIFY(XS1_SR_IEBLE_SET(0, 1)))

#define DISABLE_INTERRUPTS() asm("clrsr " STRINGIFY(XS1_SR_IEBLE_SET(0, 1)))

//int ksp_enter, ksp_exit, r11_store;

#ifdef __XS2A__
#define ISSUE_MODE_SINGLE ".issue_mode single\n"
#define ISSUE_MODE_DUAL ".issue_mode dual\n"
#else
#define ISSUE_MODE_SINGLE
#define ISSUE_MODE_DUAL
#endif

#define do_interrupt_handler(f,args)    \
  asm(ISSUE_MODE_SINGLE\
      ".align 4\n" \
      "__" #f "_handler:\n"  \
      "ENTSP_lu6 0\n" \
      "kentsp " #args "/2*2 + 20\n" \
      "__kent:" \
      save_state(f,args)    \
      load_args ## args (f) \
      "bl " #f "\n" \
      restore_state(f,args)       \
      "krestsp " #args "/2*2 + 20 \n" \
      "__kret:\n" \
      "kret\n");

#define register_interrupt_handler(f, args, nstackwords) \
  asm (" .section .dp.data,       \"adw\", @progbits\n"  \
       " .globl __" #f "_kernel_stack_end\n" \
       " .globl __" #f "_handler\n" \
       " .align 8\n"                                    \
       "__" #f "_kernel_stack:\n" \
       " .space  " #nstackwords ", 0\n" \
       "__" #f "_kernel_stack_end:\n" \
       " .space 4\n"\
       " .text\n");                             \
      do_interrupt_handler(f, args)

#define set_interrupt_handler(f, args, c, ...) \
  asm("ldaw r11, dp[__" #f "_kernel_stack_end];ldaw r10, sp[0]; " \
      "set sp,r11;stw r10, sp[0]; krestsp 0":::"r10","r11");      \
  store_args ## args(c, __VA_ARGS__) \
  asm("ldap r11, __" #f "_handler; setv res[%0],r11"::"r"(c):"r11");    \
  asm("setc res[%0], 0xa; eeu res[%0]"::"r"(c));                        \
  asm("setsr (((0) & ~(((1 << 0x1) - 1) << 0x1)) | (((1) << 0x1) & (((1 << 0x1) - 1) << 0x1)))");

/* ----------------------------------------------------------------------------
 *                           STRUCTURE VARIABLES
 * ----------------------------------------------------------------------------
*/

typedef struct _machine_pin_obj_t
{
    mp_obj_base_t base;
    uint8_t pin_id;
    char *name;
    uint8_t eic;
    uint8_t adc0;
    uint8_t adc1;
    uint8_t sercom1;
    uint8_t sercom2;
    uint8_t tc;
    uint8_t tcc1;
    uint8_t tcc2;
} machine_pin_obj_t;

typedef struct _machine_pin_irq_obj_t {
    mp_irq_obj_t base;
    uint32_t flags;
    uint32_t trigger;
    uint8_t pin_id;
} machine_pin_irq_obj_t;


typedef struct {
    mp_obj_base_t base;
    qstr name;
    uint8_t idx;
    uint8_t fn;
    uint8_t unit;
    uint8_t type;
    void *reg; // The peripheral associated with this AF
} pin_af_obj_t;

typedef struct {
    mp_obj_base_t base;
    qstr name;
    uint32_t port   : 4;
    uint32_t pin    : 5;    // Some ARM processors use 32 bits/PORT
    uint32_t num_af : 4;
    uint32_t adc_channel : 5; // Some ARM processors use 32 bits/PORT
    uint32_t adc_num  : 3;  // 1 bit per ADC
    uint32_t pin_mask;
    /*pin_gpio_t*/ machine_pin_obj_t *gpio;
    const pin_af_obj_t *af;
    uint8_t pin_id;
} pin_obj_t; 




#endif /*__interrupt_h__*/
