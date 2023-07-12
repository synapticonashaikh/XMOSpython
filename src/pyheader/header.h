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
#ifndef __HEADER_H_
#define __HEADER_H_

	/*Basic definition*/
	#define   SET		1
	#define RESET		0
	#define TRUE		SET
	#define FALSE		RESET	
	#define  ERROR 	   (int8_t)-1	

	/*IO ports-1BIT*/	
    #define PORT1A  (uint32_t)0x10200//XS1_PORT_1A
    #define PORT1B  (uint32_t)0x10000//XS1_PORT_1B
    #define PORT1C  (uint32_t)0x10100//XS1_PORT_1C
    #define PORT1D  (uint32_t)0x10300//XS1_PORT_1D
    #define PORT1E  (uint32_t)0x10600//XS1_PORT_1E
    #define PORT1F  (uint32_t)0x10400//XS1_PORT_1F
    #define PORT1G  (uint32_t)0x10500//XS1_PORT_1G
    #define PORT1H  (uint32_t)0x10700//XS1_PORT_1H
    #define PORT1I  (uint32_t)0x10a00//XS1_PORT_1I
    #define PORT1J  (uint32_t)0x10800//XS1_PORT_1J
    #define PORT1K  (uint32_t)0x10900//XS1_PORT_1K
    #define PORT1L  (uint32_t)0x10b00//XS1_PORT_1L
    #define PORT1M  (uint32_t)0x10c00//XS1_PORT_1M
    #define PORT1N  (uint32_t)0x10d00//XS1_PORT_1N
    #define PORT1O  (uint32_t)0x10e00//XS1_PORT_1O
    #define PORT1P  (uint32_t)0x10f00//XS1_PORT_1P

	/*IO ports-4BITS*/
    #define PORT4A  (uint32_t)0x40000//XS1_PORT_4A
    #define PORT4B  (uint32_t)0x40100//XS1_PORT_4B
    #define PORT4C  (uint32_t)0x40200//XS1_PORT_4C
    #define PORT4D  (uint32_t)0x40300//XS1_PORT_4D
    #define PORT4E  (uint32_t)0x40400//XS1_PORT_4E
    #define PORT4F  (uint32_t)0x40500//XS1_PORT_4F

	/*IO ports-8BITS*/
    #define PORT8A  (uint32_t)0x80000//XS1_PORT_8A
    #define PORT8B  (uint32_t)0x80100//XS1_PORT_8B
    #define PORT8C  (uint32_t)0x80200//XS1_PORT_8C
    #define PORT8D  (uint32_t)0x80300//XS1_PORT_8D

	/*IO ports-16BITS*/
    #define PORT16A  (uint32_t)0x100000//XS1_PORT_16A
    #define PORT16B  (uint32_t)0x100100//XS1_PORT_16B

	/* IO ports-32BITS */
    #define PORT32A  (uint32_t)0x200000//XS1_PORT_32A	

	/* GPIO IQR definition*/
    #define IRQ_FALLING (1)
    #define IRQ_RISING  (2)

    #define DEFAULT_PORT (uint32_t)0x10b00//XS1_PORT_1L


	/*tile nuumber*/
	#define TILE0		(uint8_t)0
	#define TILE1		(uint8_t)1

	/*core number*/
	#define CORE0		(uint8_t)0
	#define CORE1		(uint8_t)1
	#define CORE2		(uint8_t)2	
	#define CORE3		(uint8_t)3
	#define CORE4		(uint8_t)4
	#define CORE5		(uint8_t)5
	#define CORE6		(uint8_t)6	
	#define CORE7		(uint8_t)7

    /*Timer constant*/
    //as the system is working on 100Mhz, the unit time of a cycle is 10ns
    #define    uiUnitTimeMul (uint8_t)10
    #define    ui10nSec      (uint8_t)1 
    #define    ui100nSec     (uint64_t)(ui10nSec   * uiUnitTimeMul)

    #define    ui1uSec       (uint64_t)(ui100nSec * uiUnitTimeMul)
    #define    ui10uSec      (uint64_t)(ui1uSec   * uiUnitTimeMul)
    #define    ui100uSec     (uint64_t)(ui10uSec  * uiUnitTimeMul)

    #define    ui1mSec       (uint64_t)(ui100uSec * uiUnitTimeMul)
    #define    ui10mSec      (uint64_t)(ui1mSec   * uiUnitTimeMul)
    #define    ui100mSec     (uint64_t)(ui10mSec  * uiUnitTimeMul)
    #define    ui1Sec        (uint64_t)(ui100mSec * uiUnitTimeMul)


/* ----------------------------------------------------------------------------
 *                           Includes
 * ----------------------------------------------------------------------------
*/

	/**********Standard Header Files*********/		
		//#include <iostream> 
		#include <stdio.h>
		#include <stdlib.h>
		#include <unistd.h>
		#include <stdint.h>             
		#include <limits.h>	
		#include <string.h>	
		#include <signal.h>
		#include <math.h>
		#include <errno.h>           			
		#include <stdarg.h>
		#include <stddef.h>

	#ifdef USE_SDO_MODULES
		#include "sdo.h"
		#include <dictionary_symbols.h>
	#endif

/*XMOS related hedaer*/
#ifdef __XC__
	#include <platform.h>
	#include <xs1.h>
#endif

/* ----------------------------------------------------------------------------
 *                           STRUCTURE VARIABLES
 * ----------------------------------------------------------------------------
*/
	/*********union conversion 8 byte **********/
	typedef union
	{

		uint8_t 	ui8[(uint8_t)8] ; int8_t   si8[(uint8_t)8];
		uint16_t	ui16[(uint8_t)4]; int16_t si16[(uint8_t)4];
		uint32_t	ui32[(uint8_t)2]; int32_t si32[(uint8_t)2];
		uint64_t	ui64; int64_t si64;
		float		fl32[(uint8_t)2]; double dd64;

	}UNION8;

	/*********union conversion 4 byte **********/
	typedef union
	{

		uint8_t 	ui8[(uint8_t)4];  int8_t	si8[(uint8_t)4];
		uint16_t	ui16[(uint8_t)2]; int16_t	si16[(uint8_t)2];
		uint32_t	ui32; int32_t si32;
		float		fl32;

	}UNION4;

	/*********union conversion 2 byte **********/
	typedef union
	{

		uint8_t 	ui8[(uint8_t)2]; int8_t	si8[(uint8_t)2];
		uint16_t	ui16; int16_t	si16;

	}UNION2;


	/*********Timer flag **********/
	typedef struct 
	{
		uint8_t  uiTime1mSecFlag   ;
		uint8_t  uiTime10mSecFlag  ;		
		uint8_t  uiTime100mSecFlag ;    
		uint8_t  uiTime1SecFlag  ;
		uint8_t  uiTime1MinFlag  ;
		uint8_t  uiTime1HourFlag ;		
		
	}TIMERF;


	/*********Timer structure **********/
	typedef struct 
	{

		//timer    stTime;
		uint64_t uiCompareTime;
		TIMERF	 TimerFlag;

		uint8_t  uiTime1uSec ;     
		uint8_t  uiTime10uSec ;     
		uint8_t  uiTime100uSec ;     

		uint8_t  uiTime1mSec   ;
		uint8_t  uiTime10mSec  ;		
		uint8_t  uiTime100mSec ;    
		uint8_t  uiTime1Sec  ;
		uint8_t  uiTime1Min  ;
		uint8_t  uiTime1Hour ;

	}TIMER0;

/* ----------------------------------------------------------------------------
 *                           CLASS VARIABLES
 * ----------------------------------------------------------------------------
*/
    /**********************xxxx Class***************************/


/* ----------------------------------------------------------------------------
 *                          GLOBAL VARIABLE DECLARATION
 * ----------------------------------------------------------------------------
*/
	extern uint8_t   ucTimerIRQFlag ;
    extern uint32_t  ucTimerIRQTime ;

 #if ENABLE_DISABLE_GPIO_IRQ == 1
	 extern uint8_t  ucGpioIRQFlag ;
#endif
/* ---------------------------------------------------------------------------
*                           FUNCTIONS DECLARATION
* ----------------------------------------------------------------------------
*/

	void FndelayuSec (uint32_t uiTime);
	void FndelaymSec (uint32_t uiTime);
	void FndelaySec	 (uint32_t uiTime);

	int32_t FnPortWrite (uint32_t uiport,uint32_t state);
	int32_t FnPortRead  (uint32_t uiport);
	void 	FnPortToggle(uint32_t uiport);
	void GPIOInterrupt  (uint32_t uiPort, uint8_t ucMode);
	#if ENABLE_DISABLE_GPIO_IRQ == 1
		void FnGPIOIntrCheck(void);
		void FnGPIOCallbackFunction(void);
	#endif

	void 	 FnSetObjectValue( uint16_t index_, uint8_t subindex, size_t capacity, uint8_t *value);
	int  	 FnReadObject(uint16_t index_,uint16_t subindex, uint8_t capacity);
	void  	 FnSetControlword(uint16_t uiControlwrd);	
	uint16_t FnGetControlword(void);
	uint16_t FnGetErrorStatus(void);
	void     FnSetTargetTorque(int16_t Torque);
	uint16_t FnGetTargetTorque(void);
	void 	 FnSetTargetVelocity(int16_t Velocity);
	void 	 FnSetModesOfOperation(int8_t ucModes);
	uint8_t  FnGetModesOfOperation(void);
	void 	 FnSetI2TEnableDisable(uint8_t I2TEnDS);
	int  	 FnStartTheTimerIrq(uint32_t uiTime);
	void 	 FnEnableTheTimerIRQ(void);	

#endif /*__HEADER_H_*/
