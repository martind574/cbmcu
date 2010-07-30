/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_lib.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : Peripherals pointers initialization.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#define EXT

/* Includes ------------------------------------------------------------------*/
#include "71x_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ---------------------------------------------------------*/
extern u32 T0TIMI_Addr;
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef DEBUG
/*******************************************************************************
* Function Name  : debug
* Description    : Initialize the pointers to peripherals
* Input          : none
* Output         : none
* Return         : none
*******************************************************************************/
void debug(void)
{
  
  
/************************************* ADC ************************************/
#ifdef _ADC12
  ADC12 = (ADC12_TypeDef *)   ADC12_BASE;
#endif

/************************************* APB ************************************/
#ifdef _APB1
  APB1 = (APB_TypeDef *)    (APB1_BASE + 0x10);
#endif

#ifdef _APB2
  APB2 = (APB_TypeDef *)    (APB2_BASE + 0x10);
#endif

/************************************* BSPI ************************************/
 #ifdef _BSPI0
  BSPI0 = (BSPI_TypeDef *)BSPI0_BASE;
#endif

#ifdef _BSPI1
  BSPI1 = (BSPI_TypeDef *)BSPI1_BASE;
#endif

/************************************* CAN ************************************/
#ifdef _CAN
  CAN = (CAN_TypeDef *)CAN_BASE;
#endif

/************************************* EIC ************************************/
#ifdef _EIC
  EIC = (EIC_TypeDef *)EIC_BASE;
#endif

/************************************* EMI ************************************/
#ifdef _EMI
  EMI = (EMI_TypeDef *)EMI_BASE;
#endif

/************************************* GPIO ************************************/
#ifdef _GPIO0
  GPIO0 = (GPIO_TypeDef *)GPIO0_BASE;
#endif

#ifdef _GPIO1
  GPIO1 = (GPIO_TypeDef *)GPIO1_BASE;
#endif

#ifdef _GPIO2
  GPIO2 = (GPIO_TypeDef *)GPIO2_BASE;
#endif

/************************************* I2C ************************************/
#ifdef _I2C0
  I2C0 = (I2C_TypeDef *)I2C0_BASE;
#endif

#ifdef _I2C1
  I2C1 = (I2C_TypeDef *)I2C1_BASE;
#endif

/************************************* PCU ************************************/
 #ifdef _PCU
  PCU = (PCU_TypeDef *)PCU_BASE;
#endif

/************************************* RCCU ************************************/
#ifdef _RCCU
  RCCU = (RCCU_TypeDef *)RCCU_BASE;
#endif

/************************************* RTC ************************************/
#ifdef _RTC
  RTC = (RTC_TypeDef *)RTC_BASE;
#endif

/************************************* TIM ************************************/
#ifdef _TIM0
  TIM0 = (TIM_TypeDef *)TIM0_BASE;
#endif

#ifdef _TIM1
  TIM1 = (TIM_TypeDef *)TIM1_BASE;
#endif

#ifdef _TIM2
  TIM2 = (TIM_TypeDef *)TIM2_BASE;
#endif

#ifdef _TIM3
  TIM3 = (TIM_TypeDef *)TIM3_BASE;
#endif

/************************************* UART ************************************/
#ifdef _UART0
  UART0 = (UART_TypeDef *)UART0_BASE;
#endif

#ifdef _UART1
  UART1 = (UART_TypeDef *)UART1_BASE;
#endif

#ifdef _UART2
  UART2 = (UART_TypeDef *)UART2_BASE;
#endif

#ifdef _UART3
  UART3 = (UART_TypeDef *)UART3_BASE;
#endif

/************************************* WDG ************************************/
#ifdef _WDG
  WDG = (WDG_TypeDef *)WDG_BASE;
#endif

/************************************* XTI ************************************/
#ifdef _XTI
  XTI = (XTI_TypeDef *)XTI_BASE;
#endif

#ifdef _IRQVectors
  IRQVectors = (IRQVectors_TypeDef *) & T0TIMI_Addr;
#endif
}

#endif  /* DEBUG */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
