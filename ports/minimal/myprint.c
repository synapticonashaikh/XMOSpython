#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "STdriver.h"

static void ftoa_fixed(char *buffer, double value);
static void ftoa_sci  (char *buffer, double value);

void reverse(char *x, char *y)
{
   int begin, end, count = 0;
   while (x[count] != '\0') count++;
   end = count - 1;

   for (begin = 0; begin < count; begin++) 
    {  y[begin] = x[end];  end--;   }
       y[begin] = '\0';
}

void my_itoa(int val,char *ret, int base)
{	
    char rev[30];
    int i = 0;	
	for(; i < 30 && val != 0 ; i++, val /= base )
		ret[i] = "0123456789abcdef"[val % base];
        ret[i] = '\0';

    strcpy (rev,ret);
    reverse(rev,ret);	
}

int my_vfprintf(FILE *file, char const *fmt, va_list arg) {

    int int_temp;
    char char_temp;
    char *string_temp;
    double double_temp;

    char ch;
    int length = 0;

    char buffer[512];

    while ( (ch = *fmt++)) {
        if ( '%' == ch ) {
            switch (ch = *fmt++) {
                /* %% - print out a single %    */
                case '%':
                    fputc('%', file);
                    length++;
                    break;

                /* %c: print out a character    */
                case 'c':
                    char_temp = va_arg(arg, int);
                    fputc(char_temp, file);
                    length++;
                    break;

                /* %s: print out a string       */
                case 's':
                    string_temp = va_arg(arg, char *);
                    fputs(string_temp, file);
                    length += strlen(string_temp);
                    break;

                /* %d: print out an int         */
                case 'd':
                    int_temp = va_arg(arg, int);
                    my_itoa(int_temp, buffer, 10);
                    fputs(buffer, file);
                    length += strlen(buffer);
                    break;

                /* %x: print out an int in hex  */
                case 'x':
                    int_temp = va_arg(arg, int);
                    my_itoa(int_temp, buffer, 16);
                    fputs(buffer, file);
                    length += strlen(buffer);
                    break;

                case 'f':
                    double_temp = va_arg(arg, double);
                    ftoa_fixed(buffer, double_temp);
                    fputs(buffer, file);
                    length += strlen(buffer);
                    break;

                case 'e':
                    double_temp = va_arg(arg, double);
                    ftoa_sci(buffer, double_temp);
                    fputs(buffer, file);
                    length += strlen(buffer);
                    break;
            }
        }
        else {
            putc(ch, file);
            length++;
        }
    }
    return length;
}

int my_cfprintf(char *buff, char const *fmt, va_list arg) 
{

    int int_temp;
    char char_temp;
    char *string_temp;
    double double_temp;

    char ch;
    int length = 0;
    char buffer[30];
    buff[0] = '\0';

    while ((ch = *fmt++)) 
    {
        if ( '%' == ch ) 
        {
            switch (ch = *fmt++) 
            {
                /* %% - print out a single %    */
                case '%':
                     buffer[0]  = '%';
                     buffer[1] = '\0';
                     strcat(buff,buffer);
                    length++;
                    break;

                /* %c: print out a character    */
                case 'c':
                    char_temp = va_arg(arg, int);
                      buffer[0] =   char_temp ;
                      buffer[1] =   '\0';
                      strcat(buff,buffer );
                    length++;
                    break;

                /* %s: print out a string       */
                case 's':
                    string_temp = va_arg(arg, char *);
                    strcat(buff,string_temp );
                    length += strlen(string_temp);
                    break;

                /* %d: print out an int         */
                case 'd':
                    int_temp = va_arg(arg, int);
                    my_itoa(int_temp, buffer, 10);
                    strcat(buff,buffer );
                    length += strlen(buffer);
                    break;

                /* %x: print out an int in hex  */
                case 'x':
                    int_temp = va_arg(arg, int);
                    my_itoa(int_temp, buffer, 16);
                    strcat(buff,buffer );
                    length += strlen(buffer);
                    break;

                case 'f':
                    double_temp = va_arg(arg, double);
                    ftoa_fixed(buffer, double_temp);
                    strcat(buff,buffer );
                    length += strlen(buffer);
                    break;

                case 'e':
                    double_temp = va_arg(arg, double);
                    ftoa_sci(buffer, double_temp);
                    strcat(buff,buffer );
                    length += strlen(buffer);
                    break;
            }
        }
        else 
        {
             buffer[0]  = ch;
             buffer[1] = '\0';
             strcat(buff,buffer);
             length++;
        }
    }
    return length;
}

int normalize(double *val)
 {
    int exponent      = 0;
    double value      = *val;
    double multiplier = 10.0;
    double check1     = 1.0, check2 =  0.1 ;

    while (value >= check1 ) 
    {
          value /= multiplier;
        ++exponent;
    }

    while (value < check2) 
    {
          value *= multiplier;
        --exponent;
    }
    *val = value;
    return exponent;
}

static void ftoa_fixed(char *buffer, double value) 
{  
    /* carry out a fixed conversion of a double value to a string, with a precision of 5 decimal digits. 
     * Values with absolute values less than 0.000001 are rounded to 0.0
     * Note: this blindly assumes that the buffer will be large enough to hold the largest possible result.
     * The largest value we expect is an IEEE 754 double precision real, with maximum magnitude of approximately
     * e+308. The C standard requires an implementation to allow a single conversion to produce up to 512 
     * characters, so that's what we really expect as the buffer size.     
     */

    int exponent = 0;
    int places = 0;
    static const int width = 4;
    double zero = 0.0 ;

    if (value == zero) 
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }         

    if (value < zero) 
    {
        *buffer++ = '-';
        value = -value;
    }

    exponent = normalize(&value);

    while (exponent > 0) 
    {
        int digit = (int)(value * (double)10) ;
        *buffer++ = digit + '0';
        value = value * 10 - digit;
        ++places;
        --exponent;
    }

    if (places == 0)
        *buffer++ = '0';

    *buffer++ = '.';

    while (exponent < 0 && places < width) {
        *buffer++ = '0';
        --exponent;
        ++places;
    }

    while (places < width) {
        int digit = (int)(value * (double)10.0);
        *buffer++ = digit + '0';
        value = value * (double)10.0 - (double)digit;
        ++places;
    }
    *buffer = '\0';
}

void ftoa_sci(char *buffer, double value) 
{
    int exponent = 0;
    //int places = 0;
    static const int width = 4;
    double zero = 0.0 ;

    if (value == zero) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < zero) {
        *buffer++ = '-';
        value = -value;
    }

    exponent = normalize(&value);

    int digit = (int)(value * (double)10.0);
    *buffer++ = digit + '0';
    value = value * (double)10.0 - (double)digit;
    --exponent;

    *buffer++ = '.';

    for (int i = 0; i < width; i++) {
        int digit = (int)(value * (double)10.0);
        *buffer++ = digit + '0';
        value     = value * (double)10.0 - (double)digit;
    }

    *buffer++ = 'e';
    my_itoa(exponent, buffer, 10);
}

int my_sprintf(char *buff, char const *fmt, ...) 
{
    va_list arg;
    int length;

    va_start(arg, fmt);
    length = my_cfprintf(buff, fmt, arg);
    va_end(arg);
    return length;
}

int my_printf(char const *fmt, ...) 
{
    va_list arg;
    int length;

    va_start(arg, fmt);
    length = my_vfprintf(stdout, fmt, arg);
    va_end(arg);
    return length;
}


int test_main( ) {

    //float floats[] = { 0.0, 1.234e-10, 1.234e+10, -1.234e-10, -1.234e-10 };
    char buffer[200];
    

    my_sprintf(buffer,"%s, %d, %x\n", "Some string", 1, 0x1f34);
    printf("%s",buffer);


    return 0;
}

void FnPrint(char *buffer)
{

    char str[40];
    buffer[0] = '\0';
    RCCClocksTypeDef RCC_Clocks		;
	RCCGetClocksFreq(&RCC_Clocks)	;
	my_sprintf(str,"ALL CLOCK SET TO =\n\r"); strcat(buffer, str);
	my_sprintf(str,"SYSCLK=%lu "  ,	 RCC_Clocks.SYSCLK_Frequency); strcat(buffer, str);
	my_sprintf(str,"HCLK=%lu\n\r" ,	 RCC_Clocks.HCLK_Frequency  ); strcat(buffer, str);
	my_sprintf(str,"PCLK1=%lu\t"  ,	 RCC_Clocks.PCLK1_Frequency ); strcat(buffer, str);
	my_sprintf(str,"PCLK2=%lu\n\r",	 RCC_Clocks.PCLK2_Frequency ); strcat(buffer, str);
	my_sprintf(str,"PLL CLOCK SOURCE=%lu\n\r",(_RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22); strcat(buffer, str);
	my_sprintf(str,"MAIN CLOCK SOUCE=%d\n\r", RCCGetSYSCLKSource());  strcat(buffer, str);		

}