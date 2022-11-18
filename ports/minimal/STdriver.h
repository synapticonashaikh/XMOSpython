#ifndef __ST_DRIVERS
#define __ST_DRIVERS
/*--------------------------------------------------------------------------------------------------
*********************************  Header files  *********************************
--------------------------------------------------------------------------------------------------*/

	#include "stdio.h"	
	#include "string.h"
	#include "stdlib.h"	
	#include "stdint.h"
  #include <ctype.h>
/*--------------------------------------------------------------------------------------------------
*********************************  Stucture definition  *********************************
--------------------------------------------------------------------------------------------------*/
/* General definitions */
typedef enum {_RESET = 0, _SET = !_RESET} _FlagStatus, _ITStatus;
typedef enum {_DISABLE = 0, _ENABLE = !_DISABLE} _FunctionalState;
typedef enum {_ERROR = 0, _SUCCESS = !_ERROR} _ErrorStatus;



/* Reset and Clock Control */
typedef struct
{
  volatile uint32_t CR;       /*!< RCC clock control register,                                  Address offset: 0x00 */
  volatile uint32_t PLLCFGR;  /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  volatile uint32_t CFGR;     /*!< RCC clock configuration register,                            Address offset: 0x08 */
  volatile uint32_t CIR;      /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  volatile uint32_t AHB1RSTR; /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  volatile uint32_t AHB2RSTR; /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  volatile uint32_t AHB3RSTR; /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  volatile uint32_t APB1RSTR; /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  volatile uint32_t APB2RSTR; /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  volatile uint32_t AHB1ENR;  /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  volatile uint32_t AHB2ENR;  /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  volatile uint32_t AHB3ENR;  /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  volatile uint32_t APB1ENR;  /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  volatile uint32_t APB2ENR;  /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  volatile uint32_t AHB1LPENR;/*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  volatile uint32_t AHB2LPENR;/*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  volatile uint32_t AHB3LPENR;/*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  volatile uint32_t APB1LPENR;/*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  volatile uint32_t APB2LPENR;/*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  volatile uint32_t BDCR;     /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  volatile uint32_t CSR;      /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  volatile uint32_t SSCGR;     /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  volatile uint32_t PLLI2SCFGR;/*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
  volatile uint32_t PLLSAICFGR;/*!< RCC PLLSAI configuration register,                           Address offset: 0x88 */
  volatile uint32_t DCKCFGR;   /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
  volatile uint32_t CKGATENR;  /*!< RCC Clocks Gated Enable Register,                            Address offset: 0x90 */ /* Only for STM32F412xG, STM32413_423xx and STM32F446xx devices */
  volatile uint32_t DCKCFGR2;  /*!< RCC Dedicated Clocks configuration register 2,               Address offset: 0x94 */ /* Only for STM32F410xx, STM32F412xG, STM32413_423xx and STM32F446xx devices */

} RCCTypeDef;

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t SYSCLK_Frequency; /*!<  SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency;   /*!<  HCLK clock frequency expressed in Hz   */
  uint32_t PCLK1_Frequency;  /*!<  PCLK1 clock frequency expressed in Hz  */
  uint32_t PCLK2_Frequency;  /*!<  PCLK2 clock frequency expressed in Hz  */
}RCCClocksTypeDef;


/* General Purpose I/O */
typedef struct
{
  volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  volatile uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  volatile uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  volatile uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  volatile uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  volatile uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  volatile uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  volatile uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIOTypeDef;

/* GPIO Configuration Mode enumeration */ 
typedef enum
{ 
  GPIO_ModeIN   = 0x00, /*!< GPIO Input Mode */
  GPIO_ModeOUT  = 0x01, /*!< GPIO Output Mode */
  GPIO_ModeAF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_ModeAN   = 0x03  /*!< GPIO Analog Mode */
}GPIOModeTypeDef;

/* GPIO Output type enumeration */  
typedef enum
{ 
  GPIO_OTypePP = 0x00,
  GPIO_OTypeOD = 0x01
}GPIOOTypeTypeDef;

/* GPIO Output Maximum frequency enumeration */ 
typedef enum
{ 
  GPIO_LowSpeed     = 0x00, /*!< Low speed    */
  GPIO_MediumSpeed  = 0x01, /*!< Medium speed */
  GPIO_FastSpeed    = 0x02, /*!< Fast speed   */
  GPIO_HighSpeed    = 0x03  /*!< High speed   */
}GPIOSpeedTypeDef;

/* GPIO Configuration PullUp PullDown enumeration */ 
typedef enum
{ 
  GPIO_PuPdNOPULL = 0x00,
  GPIO_PuPdUP     = 0x01,
  GPIO_PuPdDOWN   = 0x02
}GPIOPuPdTypeDef;

/* GPIO Init structure definition */
typedef struct
{
  uint32_t 					GPIO_Pin	;              
  GPIOModeTypeDef  GPIO_Mode ;     
  GPIOSpeedTypeDef GPIO_Speed;  
  GPIOOTypeTypeDef GPIO_OType;  
  GPIOPuPdTypeDef  GPIO_PuPd ;    
}GPIOInitTypeDef;







/* Universal Synchronous Asynchronous Receiver Transmitter */
typedef struct
{
  volatile uint16_t SR;     /*!< USART Status register,                   Address offset: 0x00 */
  uint16_t      RESERVED0;  /*!< Reserved, 0x02                                                */
  volatile uint16_t DR;     /*!< USART Data register,                     Address offset: 0x04 */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                                */
  volatile uint16_t BRR;    /*!< USART Baud rate register,                Address offset: 0x08 */
  uint16_t      RESERVED2;  /*!< Reserved, 0x0A                                                */
  volatile uint16_t CR1;    /*!< USART Control register 1,                Address offset: 0x0C */
  uint16_t      RESERVED3;  /*!< Reserved, 0x0E                                                */
  volatile uint16_t CR2;    /*!< USART Control register 2,                Address offset: 0x10 */
  uint16_t      RESERVED4;  /*!< Reserved, 0x12                                                */
  volatile uint16_t CR3;    /*!< USART Control register 3,                Address offset: 0x14 */
  uint16_t      RESERVED5;  /*!< Reserved, 0x16                                                */
  volatile uint16_t GTPR;   /*!< USART Guard time and prescaler register, Address offset: 0x18 */
  uint16_t      RESERVED6;  /*!< Reserved, 0x1A                                                */
} USARTTypeDef;


/* USART Init Structure definition */ 
typedef struct
{
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 8 * (OVR8+1)) + 0.5 
                                           Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */
  uint16_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */
  uint16_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */
  uint16_t USART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
  uint16_t USART_Mode;                /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */
  uint16_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USARTInitTypeDef;







typedef struct
{
  uint8_t NVIC_IRQChannel;                    /*!< Specifies the IRQ channel to be enabled or disabled.
                                                   This parameter can be an enumerator of @ref IRQn_Type 
                                                   enumeration (For the complete STM32 Devices IRQ Channels
                                                   list, please refer to stm32f4xx.h file) */
  uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< Specifies the pre-emption priority for the IRQ channel
                                                   specified in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
                                                   A lower priority value indicates a higher priority */
  uint8_t NVIC_IRQChannelSubPriority;         /*!< Specifies the subpriority level for the IRQ channel specified
                                                   in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref MISC_NVIC_Priority_Table
                                                   A lower priority value indicates a higher priority */
  _FunctionalState NVIC_IRQChannelCmd;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                   will be enabled or disabled. 
                                                   This parameter can be set either to ENABLE or DISABLE */   
} NVICInitTypeDef;

 /* USART2 global Interrupt */
typedef enum IRQs
{
 USART2IRQs                 = 38,   
}IRQsType;

/* Structure type to access the System Control Block (SCB).*/
typedef struct
{
  volatile const  uint32_t CPUID;    /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;            /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;            /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;           /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;             /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;             /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t  SHP[12U];        /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;           /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;            /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;            /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;            /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;           /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;            /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;            /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  volatile const  uint32_t PFR[2U];  /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  volatile const  uint32_t DFR;      /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  volatile const  uint32_t ADR;      /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  volatile const  uint32_t MMFR[4U]; /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  volatile const  uint32_t ISAR[5U]; /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;     /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCBType;

typedef struct
{
  volatile uint32_t ISER[8U];    /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];    /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];    /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];    /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];    /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];    /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  volatile  uint32_t STIR;       /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVICType;

/*--------------------------------------------------------------------------------------------------
*********************************  Hash definition  *********************************
--------------------------------------------------------------------------------------------------*/

/* AHB1 peripherals */
#define RCC_BASE               (AHB1PERIPH_BASE + 0x3800)
/* Peripheral_declaration */
#define _RCC                 	((RCCTypeDef *) RCC_BASE)
/* RCC_AHB1_Peripherals */ 
#define RCC_AHB1Periph_GPIOA  ((uint32_t)0x00000001)
#define RCC_AHB1Periph_GPIOB  ((uint32_t)0x00000002)
#define RCC_AHB1Periph_GPIOC  ((uint32_t)0x00000004)
#define RCC_AHB1Periph_GPIOD  ((uint32_t)0x00000008)

/*!< SWS configuration */
#define  RCC_CFGR_SWS         ((uint32_t)0x0000000C) /*!< SWS[1:0] bits (System Clock Switch Status) */
#define  RCC_CFGR_SWS_0       ((uint32_t)0x00000004) /*!< Bit 0 */
#define  RCC_CFGR_SWS_1       ((uint32_t)0x00000008) /*!< Bit 1 */

/* Value of the Internal oscillator in Hz*/
#if !defined  (HSI_VALUE)   
  #define HSI_VALUE    ((uint32_t)16000000) 
#endif /* HSI_VALUE */

#if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_Bypass                   ((uint8_t)0x05)

#if !defined  (HSE_STARTUP_TIMEOUT) 
  #define HSE_STARTUP_TIMEOUT    ((uint16_t)0x05000)   /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */ 

/* CR register byte 3 (Bits[23:16]) base address */
#define CR_BYTE3_ADDRESS          ((uint32_t)0x40023802)

/* RCC Flag Mask */
#define FLAG_MASK                 ((uint8_t)0x1F)

/* Peripheral base address in the bit-band region */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000) 
/* Alias word address of HSION bit */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)
#define CR_OFFSET                 (RCC_OFFSET + 0x00)
#define HSION_BitNumber           0x00
#define CR_HSION_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (HSION_BitNumber * 4))

/* Alias word address of PLLON bit */
#define PLLON_BitNumber           0x18
#define CR_PLLON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLON_BitNumber * 4))

/* SW configuration */
/* SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW         ((uint32_t)0x00000003) 

/* RCC_PLL_Clock_Source */
#define RCC_PLLSource_HSI    ((uint32_t)0x00000000)
#define RCC_PLLSource_HSE    ((uint32_t)0x00400000)

#define RCC_SYSCLKSource_PLLPCLK         ((uint32_t)0x00000002)
/* Add legacy definition */
#define  RCC_SYSCLKSource_PLLCLK    RCC_SYSCLKSource_PLLPCLK  


/* ACR register byte 0 (Bits[7:0]) base address  */ 
#define ACR_BYTE0_ADDRESS           ((uint32_t)0x40023C00)

/* Flash_Latency */ 
#define FLASH_Latency_0                ((uint8_t)0x0000)  /*!< FLASH Zero Latency cycle      */
#define FLASH_Latency_1                ((uint8_t)0x0001)  /*!< FLASH One Latency cycle       */
#define FLASH_Latency_2                ((uint8_t)0x0002)  /*!< FLASH Two Latency cycles      */
#define FLASH_Latency_3                ((uint8_t)0x0003)  /*!< FLASH Three Latency cycles    */
#define FLASH_Latency_4                ((uint8_t)0x0004)  /*!< FLASH Four Latency cycles     */
#define FLASH_Latency_5                ((uint8_t)0x0005)  /*!< FLASH Five Latency cycles     */
#define FLASH_Latency_6                ((uint8_t)0x0006)  /*!< FLASH Six Latency cycles      */
#define FLASH_Latency_7                ((uint8_t)0x0007)  /*!< FLASH Seven Latency cycles    */
#define FLASH_Latency_8                ((uint8_t)0x0008)  /*!< FLASH Eight Latency cycles    */
#define FLASH_Latency_9                ((uint8_t)0x0009)  /*!< FLASH Nine Latency cycles     */
#define FLASH_Latency_10               ((uint8_t)0x000A)  /*!< FLASH Ten Latency cycles      */
#define FLASH_Latency_11               ((uint8_t)0x000B)  /*!< FLASH Eleven Latency cycles   */
#define FLASH_Latency_12               ((uint8_t)0x000C)  /*!< FLASH Twelve Latency cycles   */
#define FLASH_Latency_13               ((uint8_t)0x000D)  /*!< FLASH Thirteen Latency cycles */
#define FLASH_Latency_14               ((uint8_t)0x000E)  /*!< FLASH Fourteen Latency cycles */
#define FLASH_Latency_15               ((uint8_t)0x000F)  /*!< FLASH Fifteen Latency cycles  */


/* FLASH(up to 1 MB) base address in the alias region */
#define FLASH_BASE            ((uint32_t)0x08000000) 

/* Vector Table base offset field. This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET  0x00 
																	 
/* RCC_APB1_APB2_Clock_Source  */
#define RCC_HCLK_Div1              ((uint32_t)0x00000000)
#define RCC_HCLK_Div2              ((uint32_t)0x00001000)
#define RCC_HCLK_Div4              ((uint32_t)0x00001400)
#define RCC_HCLK_Div8              ((uint32_t)0x00001800)
#define RCC_HCLK_Div16             ((uint32_t)0x00001C00)

/* RCC_AHB_Clock_Source */
#define RCC_SYSCLK_Div1            ((uint32_t)0x00000000)
#define RCC_SYSCLK_Div2            ((uint32_t)0x00000080)
#define RCC_SYSCLK_Div4            ((uint32_t)0x00000090)
#define RCC_SYSCLK_Div8            ((uint32_t)0x000000A0)
#define RCC_SYSCLK_Div16           ((uint32_t)0x000000B0)
#define RCC_SYSCLK_Div64           ((uint32_t)0x000000C0)
#define RCC_SYSCLK_Div128          ((uint32_t)0x000000D0)
#define RCC_SYSCLK_Div256          ((uint32_t)0x000000E0)
#define RCC_SYSCLK_Div512          ((uint32_t)0x000000F0)

/********************  Bit definition for RCC_PLLCFGR register  ***************/
#define  RCC_PLLCFGR_PLLSRC        ((uint32_t)0x00400000)
#define  RCC_PLLCFGR_PLLSRC_HSE    ((uint32_t)0x00400000)
#define  RCC_PLLCFGR_PLLSRC_HSI    ((uint32_t)0x00000000)

#define  RCC_PLLCFGR_PLLM    ((uint32_t)0x0000003F)
#define  RCC_PLLCFGR_PLLM_0  ((uint32_t)0x00000001)
#define  RCC_PLLCFGR_PLLM_1  ((uint32_t)0x00000002)
#define  RCC_PLLCFGR_PLLM_2  ((uint32_t)0x00000004)
#define  RCC_PLLCFGR_PLLM_3  ((uint32_t)0x00000008)
#define  RCC_PLLCFGR_PLLM_4  ((uint32_t)0x00000010)
#define  RCC_PLLCFGR_PLLM_5  ((uint32_t)0x00000020)

#define  RCC_PLLCFGR_PLLN    ((uint32_t)0x00007FC0)
#define  RCC_PLLCFGR_PLLN_0  ((uint32_t)0x00000040)
#define  RCC_PLLCFGR_PLLN_1  ((uint32_t)0x00000080)
#define  RCC_PLLCFGR_PLLN_2  ((uint32_t)0x00000100)
#define  RCC_PLLCFGR_PLLN_3  ((uint32_t)0x00000200)
#define  RCC_PLLCFGR_PLLN_4  ((uint32_t)0x00000400)
#define  RCC_PLLCFGR_PLLN_5  ((uint32_t)0x00000800)
#define  RCC_PLLCFGR_PLLN_6  ((uint32_t)0x00001000)
#define  RCC_PLLCFGR_PLLN_7  ((uint32_t)0x00002000)
#define  RCC_PLLCFGR_PLLN_8  ((uint32_t)0x00004000)

#define  RCC_PLLCFGR_PLLP    ((uint32_t)0x00030000)
#define  RCC_PLLCFGR_PLLP_0  ((uint32_t)0x00010000)
#define  RCC_PLLCFGR_PLLP_1  ((uint32_t)0x00020000)

#define  RCC_PLLCFGR_PLLR    ((uint32_t)0x70000000)
#define  RCC_PLLCFGR_PLLR_0  ((uint32_t)0x10000000)
#define  RCC_PLLCFGR_PLLR_1  ((uint32_t)0x20000000)
#define  RCC_PLLCFGR_PLLR_2  ((uint32_t)0x40000000)

/* HPRE configuration */
#define  RCC_CFGR_HPRE       ((uint32_t)0x000000F0) /* HPRE[3:0] bits (AHB prescaler) */
#define  RCC_CFGR_HPRE_0     ((uint32_t)0x00000010) /* Bit 0 */
#define  RCC_CFGR_HPRE_1     ((uint32_t)0x00000020) /* Bit 1 */
#define  RCC_CFGR_HPRE_2     ((uint32_t)0x00000040) /* Bit 2 */
#define  RCC_CFGR_HPRE_3     ((uint32_t)0x00000080) /* Bit 3 */

/* PPRE1 configuration */
#define  RCC_CFGR_PPRE1      ((uint32_t)0x00001C00) /* PRE1[2:0] bits (APB1 prescaler) */
#define  RCC_CFGR_PPRE1_0    ((uint32_t)0x00000400) /* Bit 0 */
#define  RCC_CFGR_PPRE1_1    ((uint32_t)0x00000800) /* Bit 1 */
#define  RCC_CFGR_PPRE1_2    ((uint32_t)0x00001000) /* Bit 2 */

/*!< PPRE2 configuration */
#define  RCC_CFGR_PPRE2      ((uint32_t)0x0000E000) /* PRE2[2:0] bits (APB2 prescaler) */
#define  RCC_CFGR_PPRE2_0    ((uint32_t)0x00002000) /* Bit 0 */
#define  RCC_CFGR_PPRE2_1    ((uint32_t)0x00004000) /* Bit 1 */
#define  RCC_CFGR_PPRE2_2    ((uint32_t)0x00008000) /* Bit 2 */

/*RC Flag status*/
#define RCC_FLAG_HSIRDY      ((uint8_t)0x21)
#define RCC_FLAG_HSERDY      ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY      ((uint8_t)0x39)
#define RCC_FLAG_PLLI2SRDY   ((uint8_t)0x3B)
#define RCC_FLAG_PLLSAIRDY   ((uint8_t)0x3D)
#define RCC_FLAG_LSERDY      ((uint8_t)0x41)
#define RCC_FLAG_LSIRDY      ((uint8_t)0x61)
#define RCC_FLAG_BORRST      ((uint8_t)0x79)
#define RCC_FLAG_PINRST      ((uint8_t)0x7A)
#define RCC_FLAG_PORRST      ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST      ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST     ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST     ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST     ((uint8_t)0x7F)


/* Peripheral base address in the alias region */
#define PERIPH_BASE         ((uint32_t)0x40000000)

/* Peripheral memory map */
#define APB1PERIPH_BASE      PERIPH_BASE
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE     (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE     (PERIPH_BASE + 0x10000000)

/* AHB1 peripherals */
#define GPIOA_BASE          (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE          (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE          (AHB1PERIPH_BASE + 0x0800)

/* Peripheral_declaration */
#define _GPIOA               ((GPIOTypeDef *) GPIOA_BASE)
#define _GPIOB               ((GPIOTypeDef *) GPIOB_BASE)
#define _GPIOC               ((GPIOTypeDef *) GPIOC_BASE)

/* GPIO_pins_define */
#define GPIO_Pin_0          ((uint16_t)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1          ((uint16_t)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2          ((uint16_t)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3          ((uint16_t)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4          ((uint16_t)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5          ((uint16_t)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6          ((uint16_t)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7          ((uint16_t)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8          ((uint16_t)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9          ((uint16_t)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10         ((uint16_t)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11         ((uint16_t)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12         ((uint16_t)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13         ((uint16_t)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14         ((uint16_t)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15         ((uint16_t)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All        ((uint16_t)0xFFFF)  /* All pins selected */

/* GPIO_Pin_sources */ 
#define GPIO_PinSource0     ((uint8_t)0x00)
#define GPIO_PinSource1     ((uint8_t)0x01)
#define GPIO_PinSource2     ((uint8_t)0x02)
#define GPIO_PinSource3     ((uint8_t)0x03)
#define GPIO_PinSource4     ((uint8_t)0x04)
#define GPIO_PinSource5     ((uint8_t)0x05)
#define GPIO_PinSource6     ((uint8_t)0x06)
#define GPIO_PinSource7     ((uint8_t)0x07)
#define GPIO_PinSource8     ((uint8_t)0x08)
#define GPIO_PinSource9     ((uint8_t)0x09)
#define GPIO_PinSource10    ((uint8_t)0x0A)
#define GPIO_PinSource11    ((uint8_t)0x0B)
#define GPIO_PinSource12    ((uint8_t)0x0C)
#define GPIO_PinSource13    ((uint8_t)0x0D)
#define GPIO_PinSource14    ((uint8_t)0x0E)
#define GPIO_PinSource15    ((uint8_t)0x0F)

/* Bits definition for GPIO_MODER register */
#define GPIO_MODER_MODER0   ((uint32_t)0x00000003)
/* Bits definition for GPIO_OSPEEDR register */
#define GPIO_OSPEEDER_OSPEEDR0 ((uint32_t)0x00000003)
/* Bits definition for GPIO_OTYPER register */
#define GPIO_OTYPER_OT_0    ((uint32_t)0x00000001)
/* Bits definition for GPIO_PUPDR register */
#define GPIO_PUPDR_PUPDR0   ((uint32_t)0x00000003)
/* Add legacy definition */
#define  GPIO_Speed_2MHz    GPIO_Low_Speed    
#define  GPIO_Speed_25MHz   GPIO_Medium_Speed 
#define  GPIO_Speed_50MHz   GPIO_Fast_Speed 
#define  GPIO_Speed_100MHz  GPIO_High_Speed  






/* AHB1 peripherals */
#define USART1_BASE           (APB2PERIPH_BASE + 0x1000)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART6_BASE           (APB2PERIPH_BASE + 0x1400)

/* Peripheral_declaration */
#define _USART2              ((USARTTypeDef *) USART2_BASE)
#define _USART1              ((USARTTypeDef *) USART1_BASE)
#define _USART6              ((USARTTypeDef *) USART6_BASE)
/* STM32F446xx */ 
#define RCC_APB1Periph_USART2 ((uint32_t)0x00020000)
/* AF 7 selection */ 
#define GPIO_AF_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */

/* USART_Flags */
#define USART_FLAG_CTS      ((uint16_t)0x0200)
#define USART_FLAG_LBD      ((uint16_t)0x0100)
#define USART_FLAG_TXE      ((uint16_t)0x0080)
#define USART_FLAG_TC       ((uint16_t)0x0040)
#define USART_FLAG_RXNE     ((uint16_t)0x0020)
#define USART_FLAG_IDLE     ((uint16_t)0x0010)
#define USART_FLAG_ORE      ((uint16_t)0x0008)
#define USART_FLAG_NE       ((uint16_t)0x0004)
#define USART_FLAG_FE       ((uint16_t)0x0002)
#define USART_FLAG_PE       ((uint16_t)0x0001)

/* USART_Interrupt_definition */
  
#define USART_IT_PE         ((uint16_t)0x0028)
#define USART_IT_TXE        ((uint16_t)0x0727)
#define USART_IT_TC         ((uint16_t)0x0626)
#define USART_IT_RXNE       ((uint16_t)0x0525)
#define USART_IT_ORE_RX     ((uint16_t)0x0325) /* In case interrupt is generated if the RXNEIE bit is set */
#define USART_IT_IDLE       ((uint16_t)0x0424)
#define USART_IT_LBD        ((uint16_t)0x0846)
#define USART_IT_CTS        ((uint16_t)0x096A)
#define USART_IT_ERR        ((uint16_t)0x0060)
#define USART_IT_ORE_ER     ((uint16_t)0x0360) /* In case interrupt is generated if the EIE bit is set */
#define USART_IT_NE         ((uint16_t)0x0260)
#define USART_IT_FE         ((uint16_t)0x0160)


/* USART_Word_Length */
#define USART_WordLength_8b  ((uint16_t)0x0000)
#define USART_WordLength_9b  ((uint16_t)0x1000)

/* USART_Stop_Bits */ 
#define USART_StopBits_1     ((uint16_t)0x0000)
#define USART_StopBits_0_5   ((uint16_t)0x1000)
#define USART_StopBits_2     ((uint16_t)0x2000)
#define USART_StopBits_1_5   ((uint16_t)0x3000)

/* USART_Parity */ 
#define USART_Parity_No      ((uint16_t)0x0000)
#define USART_Parity_Even    ((uint16_t)0x0400)
#define USART_Parity_Odd     ((uint16_t)0x0600) 

/* USART_Mode */ 
#define USART_Mode_Rx        ((uint16_t)0x0004)
#define USART_Mode_Tx        ((uint16_t)0x0008)

/* USART_Hardware_Flow_Control */ 
#define USART_HardwareFlowControl_None       ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS        ((uint16_t)0x0100)
#define USART_HardwareFlowControl_CTS        ((uint16_t)0x0200)
#define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x0300)


/******************  Bit definition for USART_CR1 register  *******************/
#define  USART_CR1_SBK        ((uint16_t)0x0001) /*!<Send Break                             */
#define  USART_CR1_RWU        ((uint16_t)0x0002) /*!<Receiver wakeup                        */
#define  USART_CR1_RE         ((uint16_t)0x0004) /*!<Receiver Enable                        */
#define  USART_CR1_TE         ((uint16_t)0x0008) /*!<Transmitter Enable                     */
#define  USART_CR1_IDLEIE     ((uint16_t)0x0010) /*!<IDLE Interrupt Enable                  */
#define  USART_CR1_RXNEIE     ((uint16_t)0x0020) /*!<RXNE Interrupt Enable                  */
#define  USART_CR1_TCIE       ((uint16_t)0x0040) /*!<Transmission Complete Interrupt Enable */
#define  USART_CR1_TXEIE      ((uint16_t)0x0080) /*!<PE Interrupt Enable                    */
#define  USART_CR1_PEIE       ((uint16_t)0x0100) /*!<PE Interrupt Enable                    */
#define  USART_CR1_PS         ((uint16_t)0x0200) /*!<Parity Selection                       */
#define  USART_CR1_PCE        ((uint16_t)0x0400) /*!<Parity Control Enable                  */
#define  USART_CR1_WAKE       ((uint16_t)0x0800) /*!<Wakeup method                          */
#define  USART_CR1_M          ((uint16_t)0x1000) /*!<Word length                            */
#define  USART_CR1_UE         ((uint16_t)0x2000) /*!<USART Enable                           */
#define  USART_CR1_OVER8      ((uint16_t)0x8000) /*!<USART Oversampling by 8 enable         */


/*!< USART CR1 register clear Mask ((~(uint16_t)0xE9F3)) */
#define CR1_CLEAR_MASK            ((uint16_t)(USART_CR1_M | USART_CR1_PCE | \
                                              USART_CR1_PS | USART_CR1_TE | \
                                              USART_CR1_RE))																							
																							
/* STOP[1:0] bits (STOP bits) */
#define  USART_CR2_STOP                      ((uint16_t)0x3000)            

/******************  Bit definition for USART_CR3 register  *******************/
#define  USART_CR3_EIE                       ((uint16_t)0x0001)            /*!<Error Interrupt Enable      */
#define  USART_CR3_IREN                      ((uint16_t)0x0002)            /*!<IrDA mode Enable            */
#define  USART_CR3_IRLP                      ((uint16_t)0x0004)            /*!<IrDA Low-Power              */
#define  USART_CR3_HDSEL                     ((uint16_t)0x0008)            /*!<Half-Duplex Selection       */
#define  USART_CR3_NACK                      ((uint16_t)0x0010)            /*!<Smartcard NACK enable       */
#define  USART_CR3_SCEN                      ((uint16_t)0x0020)            /*!<Smartcard mode enable       */
#define  USART_CR3_DMAR                      ((uint16_t)0x0040)            /*!<DMA Enable Receiver         */
#define  USART_CR3_DMAT                      ((uint16_t)0x0080)            /*!<DMA Enable Transmitter      */
#define  USART_CR3_RTSE                      ((uint16_t)0x0100)            /*!<RTS Enable                  */
#define  USART_CR3_CTSE                      ((uint16_t)0x0200)            /*!<CTS Enable                  */
#define  USART_CR3_CTSIE                     ((uint16_t)0x0400)            /*!<CTS Interrupt Enable        */
#define  USART_CR3_ONEBIT                    ((uint16_t)0x0800)            /*!<USART One bit method enable */

/*!< USART CR3 register clear Mask ((~(uint16_t)0xFCFF)) */
#define CR3_CLEAR_MASK            ((uint16_t)(USART_CR3_RTSE | USART_CR3_CTSE))		

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	

/* Memory mapping of Core Hardware */
/* System Control Space Base Address */	
#define SCS_BASE            (0xE000E000UL)	
/* System Control Block Base Address */	
#define SCB_BASE            (SCS_BASE +  0x0D00UL)      
/* NVIC Base Address */	
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                   
/* NVIC configuration struct */	
#define _NVIC                ((NVICType *) NVIC_BASE)  	
/* SCB configuration struct */
#define _SCB                 ((SCBType *) SCB_BASE) 
/*!< USART Interrupts mask */
#define IT_MASK             ((uint16_t)0x001F)	
	
	
/*--------------------------------------------------------------------------------------------------
*********************************  Hash definition  *********************************
--------------------------------------------------------------------------------------------------*/
extern void FnClockConfigInit(void);
extern void FnGPIOInit(void);
extern void FnSerialInit(void);

extern void RCCAHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, _FunctionalState NewState);
extern void RCCAPB1PeriphClockCmd(uint32_t RCC_APB1Periph, _FunctionalState NewState);
extern void RCCGetClocksFreq(RCCClocksTypeDef* RCC_Clocks);
extern void RCCHSEConfig(uint8_t RCC_HSE);
extern void RCCHSICmd(_FunctionalState NewState);
extern void RCCPLLConfig(uint32_t RCC_PLLSource, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ, uint32_t PLLR);
extern void RCCPCLK1Config(uint32_t RCC_HCLK);
extern void RCCPCLK2Config(uint32_t RCC_HCLK);
extern void RCCHCLKConfig(uint32_t RCC_SYSCLK);
extern void RCCSYSCLKConfig(uint32_t RCC_SYSCLKSource);
extern uint8_t RCCGetSYSCLKSource(void);
extern _FlagStatus RCCGetFlagStatus(uint8_t RCC_FLAG);
extern void RCCPLLCmd(_FunctionalState NewState);
extern void RCCDeInit(void);
extern void FLASHSetLatency(uint32_t FLASH_Latency); 
extern void GPIOPinAFConfig(GPIOTypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);
extern void GPIOInit(GPIOTypeDef* GPIOx, GPIOInitTypeDef* GPIO_InitStruct);
extern void GPIOSetBits(GPIOTypeDef* GPIOx, uint16_t GPIO_Pin);
extern void GPIOResetBits(GPIOTypeDef* GPIOx, uint16_t GPIO_Pin);
extern void STprint(const char *data, uint16_t length);
extern int  STReceive(void);
extern void STBlink(void);
extern void USARTSendData(USARTTypeDef* USARTx, uint16_t Data);	
extern uint16_t USARTReceiveData(USARTTypeDef* USARTx);
extern _FlagStatus USARTGetFlagStatus(USARTTypeDef* USARTx, uint16_t USART_FLAG);
extern void NVICInit(NVICInitTypeDef* NVIC_InitStruct);
extern void USARTInit(USARTTypeDef* USARTx, USARTInitTypeDef* USART_InitStruct);
extern void USARTITConfig(USARTTypeDef* USARTx, uint16_t USART_IT, _FunctionalState NewState);
extern void USARTClearFlag(USARTTypeDef* USARTx, uint16_t USART_FLAG);
extern void USARTCmd(USARTTypeDef* USARTx, _FunctionalState NewState);
extern char * FnCapital(char *buffer);

#endif /*__ST_DRIVERS*/
