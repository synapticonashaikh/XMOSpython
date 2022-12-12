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

/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
*/

	/**********Standard Header Files*********/		
     #include "header.h"

/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
 	  port _Port1A  = PORT1A  ;
    port _Port1B  = PORT1B  ;
    port _Port1C  = PORT1C  ;
    port _Port1D  = PORT1D  ;
    port _Port1E  = PORT1E  ;
    port _Port1F  = PORT1F  ;
    port _Port1G  = PORT1G  ;
    port _Port1H  = PORT1H  ;
    port _Port1I  = PORT1I  ;
    port _Port1J  = PORT1J  ;
    port _Port1K  = PORT1K  ;
    port _Port1L  = PORT1L  ;
    port _Port1M  = PORT1M  ;
    port _Port1N  = PORT1N  ;
    port _Port1O  = PORT1O  ;
    port _Port1P  = PORT1P  ;

	/*IO ports-4BITS*/
    port _Port4A  = PORT4A  ;
    port _Port4B  = PORT4B  ;
    port _Port4C  = PORT4C  ;
    port _Port4D  = PORT4D  ;
    port _Port4E  = PORT4E  ;
    port _Port4F  = PORT4F  ;

	/*IO ports-8BITS*/
    port _Port8A  =  PORT8A  ;
    port _Port8B  =  PORT8B  ;
    port _Port8C  =  PORT8C  ;
    port _Port8D  =  PORT8D  ;

	/*IO ports-16BITS*/
    port _Port16A = PORT16A  ;
    port _Port16B = PORT16B  ;

	/*IO ports-32BITS*/
    port _Port32A = PORT32A  ;   

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
inline int32_t FnPortWrite(uint32_t uiport,uint32_t state)
{


    switch (uiport)
    {
        /*IO ports-1BIT*/	
        case PORT1A: _Port1A <: state ; break;
        case PORT1B: _Port1B <: state ; break;
        case PORT1C: _Port1C <: state ; break;  
        case PORT1D: _Port1D <: state ; break;  
        case PORT1E: _Port1E <: state ; break;  
        case PORT1F: _Port1F <: state ; break;  
        case PORT1G: _Port1G <: state ; break;  
        case PORT1H: _Port1H <: state ; break;  
        case PORT1I: _Port1I <: state ; break;  
        case PORT1J: _Port1J <: state ; break;  
        case PORT1K: _Port1K <: state ; break;  
        case PORT1L: _Port1L <: state ; break;  
        case PORT1M: _Port1M <: state ; break;  
        case PORT1N: _Port1N <: state ; break;  
        case PORT1O: _Port1O <: state ; break;  
        case PORT1P: _Port1P <: state ; break;  
        /*IO ports-4BITS*/
        case PORT4A: _Port4A <: state ; break; 
        case PORT4B: _Port4B <: state ; break; 
        case PORT4C: _Port4C <: state ; break; 
        case PORT4D: _Port4D <: state ; break; 
        case PORT4E: _Port4E <: state ; break; 
        case PORT4F: _Port4F <: state ; break; 
        /*IO ports-8BITS*/
        case PORT8A: _Port8A <: state ; break; 
        case PORT8B: _Port8B <: state ; break; 
        case PORT8C: _Port8C <: state ; break; 
        case PORT8D: _Port8D <: state ; break; 
        /*IO ports-16BITS*/
        case PORT16A: _Port16A <: state ; break; 
        case PORT16B: _Port16B <: state ; break; 
        /*IO ports-32BITS*/
        case PORT32A: _Port32A <: state ; break; 
    }
    return state;
}

/***********************************************************************
 * Function Name: main 
 * Arguments    : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
inline int32_t FnPortRead(uint32_t uiport)
{

 int support, state = ERROR;
 switch (uiport)
    {
        /*IO ports-1BIT*/	
        case PORT1A:   _Port1A @ support :> state ; break;
        case PORT1B:   _Port1B @ support :> state ; break;
        case PORT1C:   _Port1C @ support :> state ; break;  
        case PORT1D:   _Port1D @ support :> state ; break;  
        case PORT1E:   _Port1E @ support :> state ; break;  
        case PORT1F:   _Port1F @ support :> state ; break;  
        case PORT1G:   _Port1G @ support :> state ; break;  
        case PORT1H:   _Port1H @ support :> state ; break;  
        case PORT1I:   _Port1I @ support :> state ; break;  
        case PORT1J:   _Port1J @ support :> state ; break;  
        case PORT1K:   _Port1K @ support :> state ; break;  
        case PORT1L:   _Port1L @ support :> state ; break;  
        case PORT1M:   _Port1M @ support :> state ; break;  
        case PORT1N:   _Port1N @ support :> state ; break;  
        case PORT1O:   _Port1O @ support :> state ; break;  
        case PORT1P:   _Port1P @ support :> state ; break;  
        /*IO ports-4BITS*/
        case PORT4A:   _Port4A @ support :> state ; break; 
        case PORT4B:   _Port4B @ support :> state ; break; 
        case PORT4C:   _Port4C @ support :> state ; break; 
        case PORT4D:   _Port4D @ support :> state ; break; 
        case PORT4E:   _Port4E @ support :> state ; break; 
        case PORT4F:   _Port4F @ support :> state ; break; 
        /*IO ports-8BITS*/
        case PORT8A:   _Port8A @ support :> state ; break; 
        case PORT8B:   _Port8B @ support :> state ; break; 
        case PORT8C:   _Port8C @ support :> state ; break; 
        case PORT8D:   _Port8D @ support :> state ; break; 
        /*IO ports-16BITS*/
        case PORT16A: _Port16A @ support :> state ; break; 
        case PORT16B: _Port16B @ support :> state ; break; 
        /*IO ports-32BITS*/
        case PORT32A: _Port32A @ support :> state ; break; 
    }
  return state;
}


/***********************************************************************
 * Function Name: main 
 * Arguments    : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnToggle(void)
{
  static uint8_t toggy = 1;

       toggy = !toggy;
      _Port1L <: toggy;   
      //FndelayuSec(1);
 }

