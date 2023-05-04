#include "mpconfig.h"
#include "header.h"

// Receive single character
int mp_hal_stdin_rx_chr(void) 
{      
  unsigned char c = 0, d;
  d = read(STDIN_FILENO, &c, 1);   
  return c;
}  

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) 
{ 
    unsigned char d;   
    if(len!= RESET )
    d = write(STDOUT_FILENO, str, len);
    fflush(stdout);
}

