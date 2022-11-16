/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/*--------------------------------------------------------------------------------------------------
*********************************  Header files  *********************************
--------------------------------------------------------------------------------------------------*/

	#include "STdriver.h"

/*--------------------------------------------------------------------------------------------------
*********************************  Header files  *********************************
--------------------------------------------------------------------------------------------------*/

	#define ui16BufferSize (uint16_t)300
	
/*--------------------------------------------------------------------------------------------------
*********************************  Global variable  *********************************
--------------------------------------------------------------------------------------------------*/

	static volatile const uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};	
	int8_t uc8Buffer[ui16BufferSize];
	uint16_t ui16BufferCount = _RESET ;
	
/*--------------------------------------------------------------------------------------------------
*********************************  Function Definition  *********************************
--------------------------------------------------------------------------------------------------*/

/*****************************************************************************
 **@Function 		  	: 	FnClockConfigInit
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
char * FnCapital(char *buffer)
{
    int j=0;
    while (buffer[j]) 
    { buffer[j] = toupper(buffer[j]);  j++;    }

    return buffer;
}


/*****************************************************************************
 **@Function 		  	: 	FnClockConfigInit
 **@Descriptions		: 	
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void FnClockConfigInit(void)
{

	volatile uint32_t StartUpCounter = _RESET ;	
	//volatile uint32_t	ClockStatus		 = _RESET ;		
	
	/* Reset the RCC clock configuration to the default reset state ------------*/
			RCCDeInit()	;
			RCCHSEConfig(RCC_HSE_OFF)		; 
			RCCHSICmd(_ENABLE);
			
			while((RCCGetFlagStatus(RCC_FLAG_HSIRDY) == _RESET)&(StartUpCounter <  HSE_STARTUP_TIMEOUT )) 
						 {
               StartUpCounter++; 
             }
             
             StartUpCounter = 0;
			
											//PLLM, PLLN, PLLP, PLLQ, PLLR
			RCCPLLConfig		(RCC_PLLSource_HSI,8,100,2,2,2);
			RCCSYSCLKConfig (RCC_SYSCLKSource_PLLCLK)	  	;
			RCCPCLK2Config	(RCC_HCLK_Div2)								;
			RCCPCLK1Config	(RCC_HCLK_Div4)								;
			RCCHCLKConfig	  (RCC_SYSCLK_Div1)							;
			FLASHSetLatency (FLASH_Latency_3)							;	
			RCCPLLCmd				(_ENABLE);
			while(RCCGetFlagStatus(RCC_FLAG_PLLRDY) == _RESET) ;
		  
			_SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
			
			RCCAHB1PeriphClockCmd(  RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC , _ENABLE);
}	

/*****************************************************************************
 **@Function 		  	: 	FnDebuggComPortInit
 **@Descriptions		: 	USART3 COM port init
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void FnGPIOInit(void)
{
	
	/* Enable the GPIOA peripheral */ 
	GPIOInitTypeDef   General_GPIOINIT 			   ;
	General_GPIOINIT.GPIO_Pin 	= GPIO_Pin_5	 ;
	General_GPIOINIT.GPIO_OType =  GPIO_OTypePP;
	General_GPIOINIT.GPIO_PuPd 	=  GPIO_PuPdUP ;		 
	General_GPIOINIT.GPIO_Mode 	=  GPIO_ModeOUT;
	GPIOInit (_GPIOA, &General_GPIOINIT)	; 	   

}	

/*****************************************************************************
 **@Function 		  	: 	FnDebuggComPortInit
 **@Descriptions		: 	USART3 COM port init
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void FnSerialInit(void)
{

	/*USART Standard peripheral structures*/
	USARTInitTypeDef USART_InitStructure		;
	GPIOInitTypeDef 	GPIO_InitStructure		;
	NVICInitTypeDef 	stNVIC_InitStructure	;

	/* Enable GPIO clock */
	RCCAHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOA , _ENABLE);
	
	/* Enable UART clock */
	RCCAPB1PeriphClockCmd( RCC_APB1Periph_USART2, _ENABLE);

	/* Configure USART Tx as alternate function  */
	GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_2	  ;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OTypePP	;
	GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPdUP		;
	GPIO_InitStructure.GPIO_Mode 		= GPIO_ModeAF		;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_HighSpeed;
	GPIOInit(_GPIOA, &GPIO_InitStructure)	;
	
	/* Configure USART Rx as alternate function  */
	GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_3 ;
	GPIOInit(_GPIOA, &GPIO_InitStructure)	;
	
	/* Connect PXx to USARTx_Tx*/
	GPIOPinAFConfig(_GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	/* Connect PXx to USARTx_Rx*/
	GPIOPinAFConfig(_GPIOA, GPIO_PinSource3, GPIO_AF_USART2);		

	/*USART3 parameter setting*/
	USART_InitStructure.USART_BaudRate 	 					= (uint32_t)115200  		; 
	USART_InitStructure.USART_WordLength 					= USART_WordLength_8b		;
	USART_InitStructure.USART_StopBits 	 					= USART_StopBits_1			;
	USART_InitStructure.USART_Parity 		 					= USART_Parity_No				;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx ;	

	/* USART configuration */
	USARTInit(_USART2, &USART_InitStructure);	
		
	/* NVIC Structure Init*/
	stNVIC_InitStructure.NVIC_IRQChannel 										= USART2IRQs;
	stNVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= _RESET ;
	stNVIC_InitStructure.NVIC_IRQChannelSubPriority 				= _RESET ;
	stNVIC_InitStructure.NVIC_IRQChannelCmd 								= _ENABLE;
	NVICInit(&stNVIC_InitStructure);
	
	/* Enable USART2 interrupt*/
	//USARTITConfig(_USART2,USART_IT_RXNE,_ENABLE);
	
	//USARTClearFlag(_USART2, 
	//								USART_FLAG_LBD  | USART_FLAG_FE	  | USART_FLAG_TC  | 
	//								USART_FLAG_IDLE | USART_FLAG_RXNE | USART_FLAG_PE  |
	//								USART_FLAG_ORE  | USART_FLAG_NE   | USART_FLAG_CTS /*| USART_FLAG_TXE   */		);
	

	/* Enable USART */
	USARTCmd(_USART2, _ENABLE);
	
	/*TEST print*/	
	printf(" COM PORT INIT [USART2@115200bps].\n\r");
	RCCClocksTypeDef RCC_Clocks		;
	RCCGetClocksFreq(&RCC_Clocks)	;
	printf("ALL CLOCK SET TO =\n\r")	;
	printf("SYSCLK=%lu "  ,	 RCC_Clocks.SYSCLK_Frequency);
	printf("HCLK=%lu\n\r" ,	 RCC_Clocks.HCLK_Frequency  );
	printf("PCLK1=%lu\t"  ,	 RCC_Clocks.PCLK1_Frequency );
	printf("PCLK2=%lu\n\r",	 RCC_Clocks.PCLK2_Frequency );
	printf("PLL CLOCK SOURCE=%lu\n\r",(_RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22);
	printf("MAIN CLOCK SOUCE=%d\n\r", RCCGetSYSCLKSource());		

}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCAHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, _FunctionalState NewState)
{
  if (NewState != _DISABLE)
  { _RCC->AHB1ENR |= RCC_AHB1Periph;  }
  else
  { _RCC->AHB1ENR &= ~RCC_AHB1Periph;  }
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCAPB1PeriphClockCmd(uint32_t RCC_APB1Periph, _FunctionalState NewState)
{
  if (NewState != _DISABLE)
  {  _RCC->APB1ENR |= RCC_APB1Periph;  }
  else
  {  _RCC->APB1ENR &= ~RCC_APB1Periph; }
}

/*****************************************************************************
 **@Function 		  	: 	RCC_DeInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCDeInit(void)
{
  /* Set HSION bit */
  _RCC->CR |= (uint32_t)0x00000001;
  /* Reset CFGR register */
  _RCC->CFGR = 0x00000000;
  /* Reset HSEON, CSSON, PLLON, PLLI2S and PLLSAI(STM32F42xxx/43xxx/446xx/469xx/479xx devices) bits */
  _RCC->CR &= (uint32_t)0xEAF6FFFF;  
  /* Reset PLLCFGR register */
  _RCC->PLLCFGR = 0x24003010;
  /* Reset PLLI2SCFGR register */
  _RCC->PLLI2SCFGR = 0x20003000;
  /* Reset PLLSAICFGR register, only available for STM32F42xxx/43xxx/446xx/469xx/479xx devices */
  _RCC->PLLSAICFGR = 0x24003000;
  /* Reset HSEBYP bit */
  _RCC->CR &= (uint32_t)0xFFFBFFFF;
  /* Disable all interrupts */
  _RCC->CIR = 0x00000000;
  /* Disable Timers clock prescalers selection, only available for STM32F42/43xxx and STM32F413_423xx devices */
  _RCC->DCKCFGR = 0x00000000;
  
}

/*****************************************************************************
 **@Function 		  	: 	RCCHSEConfig
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/
void RCCHSEConfig(uint8_t RCC_HSE)
{
  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  *(volatile uint8_t *) CR_BYTE3_ADDRESS = RCC_HSE_OFF;
  /* Set the new HSE configuration -------------------------------------------*/
  *(volatile uint8_t *) CR_BYTE3_ADDRESS = RCC_HSE;
}

/*****************************************************************************
 **@Function 		  	: 	RCCHSEConfig
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/
void RCCHSICmd(_FunctionalState NewState)
{  *(volatile uint32_t *) CR_HSION_BB = (uint32_t)NewState; }

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
uint8_t RCCGetSYSCLKSource(void)
{
  return ((uint8_t)(_RCC->CFGR & RCC_CFGR_SWS));
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCGetClocksFreq(RCCClocksTypeDef* RCC_Clocks)
{
  uint32_t tmp = 0, presc = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)  
  uint32_t pllr = 2;
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */
  
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = _RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
  case 0x00:  /* HSI used as system clock source */
    RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
    break;
  case 0x04:  /* HSE used as system clock  source */
    RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
    break;
  case 0x08:  /* PLL P used as system clock  source */
    
    /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
    SYSCLK = PLL_VCO / PLLP
    */    
    pllsource = (_RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
    pllm = _RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
    
    if (pllsource != 0)
    {
      /* HSE used as PLL clock source */
      pllvco = (HSE_VALUE / pllm) * ((_RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
    }
    else
    {
      /* HSI used as PLL clock source */
      pllvco = (HSI_VALUE / pllm) * ((_RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
    }
    
    pllp = (((_RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >>16) + 1 ) *2;
    RCC_Clocks->SYSCLK_Frequency = pllvco/pllp;
    break;

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
  case 0x0C:  /* PLL R used as system clock  source */
    /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
    SYSCLK = PLL_VCO / PLLR
    */    
    pllsource = (_RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
    pllm = _RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
    
    if (pllsource != 0)
    {
      /* HSE used as PLL clock source */
      pllvco = (HSE_VALUE / pllm) * ((_RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
    }
    else
    {
      /* HSI used as PLL clock source */
      pllvco = (HSI_VALUE / pllm) * ((_RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
    }
    
    pllr = (((_RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >>28) + 1 ) *2;
    RCC_Clocks->SYSCLK_Frequency = pllvco/pllr;    
    break;
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */
    
  default:
    RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
    break;
  }
  /* Compute HCLK, PCLK1 and PCLK2 clocks frequencies ------------------------*/
  
  /* Get HCLK prescaler */
  tmp = _RCC->CFGR & RCC_CFGR_HPRE;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

  /* Get PCLK1 prescaler */
  tmp = _RCC->CFGR & RCC_CFGR_PPRE1;
  tmp = tmp >> 10;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

  /* Get PCLK2 prescaler */
  tmp = _RCC->CFGR & RCC_CFGR_PPRE2;
  tmp = tmp >> 13;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCPLLConfig(uint32_t RCC_PLLSource, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ, uint32_t PLLR)
{  _RCC->PLLCFGR = PLLM | (PLLN << 6) | (((PLLP >> 1) -1) << 16) | (RCC_PLLSource) | (PLLQ << 24) | (PLLR << 28); }

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 	
void RCCPCLK1Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  tmpreg = _RCC->CFGR;
  /* Clear PPRE1[2:0] bits */
  tmpreg &= ~RCC_CFGR_PPRE1;
  /* Set PPRE1[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK;
  /* Store the new value */
  _RCC->CFGR = tmpreg;
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCPCLK2Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;
  tmpreg = _RCC->CFGR;
  /* Clear PPRE2[2:0] bits */
  tmpreg &= ~RCC_CFGR_PPRE2;
  /* Set PPRE2[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK << 3;
  /* Store the new value */
  _RCC->CFGR = tmpreg;
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCHCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;
  tmpreg = _RCC->CFGR;
  /* Clear HPRE[3:0] bits */
  tmpreg &= ~RCC_CFGR_HPRE;
  /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
  tmpreg |= RCC_SYSCLK;
  /* Store the new value */
  _RCC->CFGR = tmpreg;
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void RCCPLLCmd(_FunctionalState NewState)
{  *(volatile uint32_t *) CR_PLLON_BB = (uint32_t)NewState; }

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void FLASHSetLatency(uint32_t FLASH_Latency)
{  /* Perform Byte access to FLASH_ACR[8:0] to set the Latency value */
  *(volatile uint8_t *)ACR_BYTE0_ADDRESS = (uint8_t)FLASH_Latency;
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 	
void RCCSYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;
  tmpreg = _RCC->CFGR;
  /* Clear SW[1:0] bits */
  tmpreg &= ~RCC_CFGR_SW;
  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;
  /* Store the new value */
  _RCC->CFGR = tmpreg;
}
/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
_FlagStatus RCCGetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  _FlagStatus bitstatus = _RESET;

  /* Get the RCC register index */
  tmp = RCC_FLAG >> 5;
  if (tmp == 1)               /* The flag to check is in CR register */
  {    statusreg = _RCC->CR;   }
  else if (tmp == 2)          /* The flag to check is in BDCR register */
  {    statusreg = _RCC->BDCR; }
  else                       /* The flag to check is in CSR register */
  {    statusreg = _RCC->CSR;  }

  /* Get the flag position */
  tmp = RCC_FLAG & FLAG_MASK;
  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)_RESET)
  {    bitstatus = _SET;  }
  else
  {    bitstatus = _RESET;}
  /* Return the flag status */
  return bitstatus;
}

/*****************************************************************************
 **@Function 		  	: 	NVIC_Init
 **@Descriptions		: 	
 **@parameters			: 	NVIC_InitTypeDef* NVIC_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void NVICInit(NVICInitTypeDef* NVIC_InitStruct)
{
  uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != _DISABLE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((_SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  (uint8_t)(NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub);
        
    tmppriority = tmppriority << 0x04;
        
    _NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    _NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    _NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/*****************************************************************************
 **@Function 		  	: 	NVIC_Init
 **@Descriptions		: 	
 **@parameters			: 	NVIC_InitTypeDef* NVIC_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void USART2_IRQHandler(void)
{
      /* Read one byte from the receive data register */
	  if( USARTGetFlagStatus(_USART2,USART_IT_RXNE) == _SET )
			{ USARTClearFlag    (_USART2,USART_IT_RXNE);
							uint8_t  ucData;
							ucData = USARTReceiveData(_USART2);
							uc8Buffer[ui16BufferCount++] = ucData;
							uc8Buffer[ui16BufferCount]   = _RESET;
						
							if( ucData == (char)'\n')
								{ ucData = _RESET;
								  //STprint((const char *)uc8Buffer,ui16BufferCount);	
								  memset(uc8Buffer,_RESET,ui16BufferCount);
								  ui16BufferCount = _RESET ;	
								}	
							
								if ( ui16BufferCount >= ui16BufferSize)
								{		 ucData = _RESET;
									   memset(uc8Buffer,_RESET,ui16BufferCount);
										 ui16BufferCount = _RESET ;	
								}
			}					
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void GPIOInit(GPIOTypeDef* GPIOx, GPIOInitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

  /* ------------------------- Configure the port pins ---------------- */
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      if ((GPIO_InitStruct->GPIO_Mode == GPIO_ModeOUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_ModeAF))
      {
        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Output mode configuration*/
        GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }
      /* Pull-up Pull down resistor configuration*/
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}

/*****************************************************************************
 **@Function 		  	: 	GPIOInit
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct
 **@return					: 	None
*****************************************************************************/ 
void GPIOPinAFConfig(GPIOTypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp 	= 0x00;
  uint32_t temp_2 = 0x00;
  
  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
  GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
  GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}

/*****************************************************************************
 **@Function 		  	: 	GPIOSetBits
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin
 **@return					: 	None
*****************************************************************************/
void GPIOSetBits(GPIOTypeDef* GPIOx, uint16_t GPIO_Pin)
{  GPIOx->BSRR = GPIO_Pin; }

/*****************************************************************************
 **@Function 		  	: 	GPIOResetBits
 **@Descriptions		: 	
 **@parameters			: 	GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin
 **@return					: 	None
*****************************************************************************/
void GPIOResetBits(GPIOTypeDef* GPIOx, uint16_t GPIO_Pin)
{ GPIOx->BSRR = (uint32_t)GPIO_Pin << 16; }

/*****************************************************************************
 **@Function 		  	: 	USARTSendData
 **@Descriptions		: 	
 **@parameters			: 	USART_TypeDef* USARTx, uint16_t Data
 **@return					: 	None
*****************************************************************************/
void USARTSendData(USARTTypeDef* USARTx, uint16_t Data )
{  USARTx->DR = (Data & (uint16_t)0x01FF);}

/*****************************************************************************
 **@Function 		  	: 	USARTSendData
 **@Descriptions		: 	
 **@parameters			: 	USART_TypeDef* USARTx, uint16_t Data
 **@return					: 	None
*****************************************************************************/
uint16_t USARTReceiveData(USARTTypeDef* USARTx)
{    return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);   }

/*****************************************************************************
 **@Function 		  	: 	USARTGetFlagStatus
 **@Descriptions		: 	
 **@parameters			: 	USART_TypeDef* USARTx, uint16_t USART_FLAG
 **@return					: 	FlagStatus
*****************************************************************************/
_FlagStatus USARTGetFlagStatus(USARTTypeDef* USARTx, uint16_t USART_FLAG)
{
  _FlagStatus bitstatus = _RESET;
  /* The CTS flag is not available for UART4 and UART5 */
  if (USART_FLAG == USART_FLAG_CTS){  } 
  if ((USARTx->SR & USART_FLAG) != (uint16_t)_RESET)
  {  bitstatus = _SET;  }
  else
  {  bitstatus = _RESET;}
  return bitstatus;
}

/*****************************************************************************
 **@Function 		  	: 	USARTGetFlagStatus
 **@Descriptions		: 	
 **@parameters			: 	USART_TypeDef* USARTx, uint16_t USART_FLAG
 **@return					: 	FlagStatus
*****************************************************************************/
void USARTITConfig(USARTTypeDef* USARTx, uint16_t USART_IT, _FunctionalState NewState)
{
  uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
  uint32_t usartxbase = 0x00;

  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_IT == USART_IT_CTS)  {  } 
    
  usartxbase = (uint32_t)USARTx;

  /* Get the USART register index */
  usartreg = (((uint8_t)USART_IT) >> 0x05);

  /* Get the interrupt position */
  itpos = USART_IT & IT_MASK;
  itmask = (((uint32_t)0x01) << itpos);
    
  if (usartreg == 0x01) /* The IT is in CR1 register */
  {  usartxbase += 0x0C; }
  else if (usartreg == 0x02) /* The IT is in CR2 register */
  {  usartxbase += 0x10; }
  else /* The IT is in CR3 register */
  {  usartxbase += 0x14; }
  if (NewState != _DISABLE)
  { *(volatile uint32_t*)usartxbase  |= itmask;  }
  else
  { *(volatile uint32_t*)usartxbase &= ~itmask;  }

}

/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void USARTClearFlag(USARTTypeDef* USARTx, uint16_t USART_FLAG)
{
  /* The CTS flag is not available for UART4 and UART5 */
  if ((USART_FLAG & USART_FLAG_CTS) == USART_FLAG_CTS){  } 
       
  USARTx->SR = (uint16_t)~USART_FLAG;
}

/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void USARTInit(USARTTypeDef* USARTx, USARTInitTypeDef* USART_InitStruct)
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  RCCClocksTypeDef RCC_ClocksStatus;

  /* The hardware flow control is available only for USART1, USART2, USART3 and USART6 */
  if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)  {  }

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;

  /* Clear STOP[13:12] bits */
  tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);

  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit :
      Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  /* Write to USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;

/*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;

  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR1_CLEAR_MASK);

  /* Configure the USART Word Length, Parity and mode: 
     Set the M bits according to USART_WordLength value 
     Set PCE and PS bits according to USART_Parity value
     Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;

  /* Write to USART CR1 */
  USARTx->CR1 = (uint16_t)tmpreg;

/*---------------------------- USART CR3 Configuration -----------------------*/  
  tmpreg = USARTx->CR3;

  /* Clear CTSE and RTSE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);

  /* Configure the USART HFC : 
      Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;

  /* Write to USART CR3 */
  USARTx->CR3 = (uint16_t)tmpreg;

/*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate */
  RCCGetClocksFreq(&RCC_ClocksStatus);

  if ((USARTx == _USART1) || (USARTx == _USART6))
  { apbclock = RCC_ClocksStatus.PCLK2_Frequency;  }
  else
  { apbclock = RCC_ClocksStatus.PCLK1_Frequency;  }
  
  /* Determine the integer part */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* Integer part computing in case Oversampling mode is 8 Samples */
    integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));    
  }
  else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
  {
    /* Integer part computing in case Oversampling mode is 16 Samples */
    integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));    
  }
  tmpreg = (integerdivider / 100) << 4;

  /* Determine the fractional part */
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

  /* Implement the fractional part in the register */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  { tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);   }
  else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
  { tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);  }
  
  /* Write to USART BRR register */
  USARTx->BRR = (uint16_t)tmpreg;
}

/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void USARTCmd(USARTTypeDef* USARTx, _FunctionalState NewState)
{
  if(NewState != _DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_UE;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_UE);
  }
}

/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void STprint(const char *data, uint16_t length)
{
		for (uint16_t loop = _RESET ; loop < length ; loop++ )
		{
			USARTSendData(_USART2, (uint8_t)data[loop]);
			/* Loop until the end of transmission */
			while (USARTGetFlagStatus(_USART2, USART_FLAG_TC) == _RESET) {  }	
		}
}

/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
int STReceive(void)
{
		 while(  USARTGetFlagStatus(_USART2,USART_FLAG_RXNE) == _RESET){};					
			       USARTClearFlag    (_USART2,USART_FLAG_RXNE);
      return USARTReceiveData  (_USART2);
}


/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
void STBlink(void)
{
  GPIOSetBits(_GPIOA,GPIO_Pin_5);
  for (volatile uint32_t uiloop = _RESET ; uiloop <(uint32_t)0xFF00; uiloop++){};
  GPIOResetBits(_GPIOA,GPIO_Pin_5);
  for (volatile uint32_t uiloop = _RESET ; uiloop <(uint32_t)0xFF00; uiloop++){};  
}

/*****************************************************************************
 **@Function 		  	: 	PUTCHAR_PROTOTYPE
 **@Descriptions		: 	printf prototype
 **@parameters			: 	None
 **@return					: 	None
*****************************************************************************/ 
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USARTSendData(_USART2, (uint8_t) ch);
  /* Loop until the end of transmission */
  while (USARTGetFlagStatus(_USART2, USART_FLAG_TC) == _RESET)  {  }
         USARTClearFlag(_USART2, USART_FLAG_TC);
  return ch;
}
