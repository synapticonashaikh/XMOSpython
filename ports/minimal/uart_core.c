#include <unistd.h>
#include "py/mpconfig.h"
#include "STdriver.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


// Receive single character
int mp_hal_stdin_rx_chr(void) 
{      return STReceive(); }  

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) 
{  STprint(str, len); }
