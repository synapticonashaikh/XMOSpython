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

    #define RQST_FROM_APP       0
    #define RQST_FROM_MASTER    1
    #define CHECK_SDO_NO_ERROR  0

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
    uint16_t Dummy=RESET;
/* ----------------------------------------------------------------------------
 *                          FUNCTION DEFINITION
 * ----------------------------------------------------------------------------
*/
/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnSetObjectValue( uint16_t index_, uint8_t subindex, size_t capacity, uint8_t *value)
{ 
    #ifdef USE_SDO_MODULES
        size_t  bytecount = sdo_get_bytecount_by_object_index(index_, subindex);
        uint8_t tmpvalue[MAX_VALUE_BUFFER]     = { RESET };
        unsigned int objpos = RESET; int error =   RESET;

        error = sdo_find_object_position(index_, &objpos);
        if (error == SDO_NO_ERROR) 
        {
            memcpy(&tmpvalue, value, capacity);
            error = sdo_set_all_values_by_object_position(
            objpos, subindex, (uint8_t *)&tmpvalue,
            bytecount, REQUEST_FROM_APP); 
            /* For simple objects there is no lengthy processing necessary. */
            sdo_clear_value_busy_at_position(objpos, subindex);
        }
    #endif
}

/***********************************************************************
 * Function Name: main 
 * Arguments	  : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
int FnReadObject(uint16_t index_,uint16_t subindex, uint8_t capacity)
{
    #ifdef USE_SDO_MODULES
        unsigned int objpos = RESET;  int error = RESET;
        size_t bitsize   = RESET;
        int request_from = REQUEST_FROM_MASTER;
        uint8_t tmp[MAX_VALUE_BUFFER] = { 0 };
        uint8_t value_out[MAX_VALUE_BUFFER] = { 0 };

        error  = sdo_get_value_by_object_index
        (index_, subindex, capacity, RQST_FROM_MASTER,(uint8_t *)&tmp, &bitsize);
        memcpy(value_out, &tmp, BYTES_FROM_BITS(bitsize));
    
        printf("OBJECT VALUE =");
        for(uint8_t ucLoop = RESET; ucLoop < capacity; ucLoop++)
            printf("%x ",tmp[ucLoop]);
        printf("\n\r");
        return RESET;

    #else
         return RESET;
    #endif
}

/***********************************************************************
 * Function Name: main 
 * Arguments    : void
 * Return Type	: int
 * Details	: main function, start of the code
 * *********************************************************************/
void FnSetControlword(uint16_t uiControlwrd)
{
    #ifdef USE_SDO_MODULES
       od_write_value_by_subitem_pos(OD_SUBITEMPOS_CONTROLWORD_0x6040_0, 
       (uint8_t *)&uiControlwrd,sizeof(uiControlwrd));
    #else
         Dummy = uiControlwrd;
    #endif   
}

/***********************************************************************
 * Function Name: main 
 * Arguments	 : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
uint16_t FnGetControlword(void)
{
    #ifdef USE_SDO_MODULES
       uint16_t  ReadControlWord;
       sdo_get_value_by_subitem_position_unsafe(OD_SUBITEMPOS_CONTROLWORD_0x6040_0,(uint8_t *)&ReadControlWord); 
       return ReadControlWord; 
   #else
        return Dummy;
   #endif 
} 

/***********************************************************************
 * Function Name: main 
 * Arguments	 : void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
uint16_t FnGetErrorStatus(void)
{
    #ifdef USE_SDO_MODULES
       uint16_t  ReadErrorStatus;
       sdo_get_value_by_subitem_position_unsafe(OD_SUBITEMPOS_ERROR_CODE_0x603F_0,(uint8_t *)&ReadErrorStatus); 
       return ReadErrorStatus; 
   #else
        return Dummy;
   #endif 
}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnSetModesOfOperation(int8_t ucModes)
{
   #ifdef USE_SDO_MODULES
          od_write_value_by_subitem_pos (OD_SUBITEMPOS_MODES_OF_OPERATION_0x6060_0, (uint8_t *)&ucModes, sizeof(ucModes));
   #else
         Dummy = ucModes;          
   #endif       
}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
uint8_t FnGetModesOfOperation(void)
{
    #ifdef USE_SDO_MODULES
           uint8_t ucModes ;
           od_write_value_by_subitem_pos(OD_SUBITEMPOS_MODES_OF_OPERATION_0x6060_0, (uint8_t *)&ucModes, sizeof(ucModes));
           return ucModes;
    #else
          return Dummy; 
    #endif
}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnSetTargetTorque(int16_t Torque)
{
    #ifdef USE_SDO_MODULES
           od_write_value_by_subitem_pos 
           (OD_SUBITEMPOS_TARGET_TORQUE_0x6071_0, (uint8_t *)&Torque, sizeof(Torque));
    #else
         Dummy = Torque;              
    #endif 
}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnSetTargetVelocity(int16_t Velocity)
{
    #ifdef USE_SDO_MODULES
           od_write_value_by_subitem_pos 
           (OD_SUBITEMPOS_TARGET_VELOCITY_0x60FF_0, (uint8_t *)&Velocity, sizeof(Velocity));
    #else
         Dummy = Velocity;    
    #endif 

    // static int a = SET;
    // FnPortWrite(PORT1M,a); a = !a;
}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
uint16_t FnGetTargetTorque(void)
{ 
   #ifdef USE_SDO_MODULES
       uint16_t TargetTorque;
       sdo_get_value_by_subitem_position_unsafe
       (OD_SUBITEMPOS_TARGET_TORQUE_0x6071_0,(uint8_t *)&TargetTorque);
       return  TargetTorque;
   #else
        return Dummy;
   #endif 

}

/***********************************************************************
 * Function Name: main 
 * Arguments	: void
 * Return Type	: int
 * Details	    : main function, start of the code
 * *********************************************************************/
void FnSetI2TEnableDisable(uint8_t I2TEnDS)
{ 
  #ifdef USE_SDO_MODULES
         od_write_value_by_subitem_pos 
         (OD_SUBITEMPOS_I2T_AND_STALL_PROTECTION_ENABLED_0x200A_1,
         (uint8_t *)&I2TEnDS, sizeof(I2TEnDS));
    #else
         Dummy = I2TEnDS;          
  #endif    
}
