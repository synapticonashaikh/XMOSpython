#include <unistd.h>
#include "py/mpconfig.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


// Receive single character
int mp_hal_stdin_rx_chr(void) 
{      
  unsigned char c = 0;
  read(STDIN_FILENO, &c, 1);   
  printf("::%c",c);
  return c;
}  

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) 
{  
    write(STDOUT_FILENO, str, len);
}

