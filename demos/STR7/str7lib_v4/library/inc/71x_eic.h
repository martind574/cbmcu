/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_eic.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      EIC firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_EIC_H
#define __71x_EIC_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  T0TIMI_IRQChannel    = 0,
  FLASH_IRQChannel     = 1,
  RCCU_IRQChannel      = 2,
  RTC_IRQChannel       = 3,
  WDG_IRQChannel       = 4,
  XTI_IRQChannel       = 5,
  USBHP_IRQChannel     = 6,
  I2C0ITERR_IRQChannel = 7,
  I2C1ITERR_IRQChannel = 8,
  UART0_IRQChannel     = 9,
  UART1_IRQChannel     = 10,
  UART2_IRQChannel     = 11,
  UART3_IRQChannel     = 12,
  SPI0_IRQChannel      = 13,
  SPI1_IRQChannel      = 14,
  I2C0_IRQChannel      = 15,
  I2C1_IRQChannel      = 16,
  CAN_IRQChannel       = 17,
  ADC_IRQChannel       = 18,
  T1TIMI_IRQChannel    = 19,
  T2TIMI_IRQChannel    = 20,
  T3TIMI_IRQChannel    = 21,
  HDLC_IRQChannel      = 25,
  USBLP_IRQChannel     = 26,
  T0TOI_IRQChannel     = 29,
  T0OC1_IRQChannel     = 30,
  T0OC2_IRQChannel     = 31
}IRQChannel_TypeDef;

typedef enum
{
  T0TIMI_FIQChannel     = 0x00000001,
  WDG_FIQChannel        = 0x00000002,
  WDGT0TIMI_FIQChannels = 0x00000003
}FIQChannel_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void EIC_Init(void);
void EIC_IRQConfig(FunctionalState NewState);
void EIC_FIQConfig(FunctionalState NewState);
void EIC_IRQChannelConfig(IRQChannel_TypeDef IRQChannel,
                          FunctionalState NewState);
void EIC_FIQChannelConfig(FIQChannel_TypeDef FIQChannel,
                          FunctionalState NewState);
void EIC_IRQChannelPriorityConfig(IRQChannel_TypeDef IRQChannel, u8 Priority);
void EIC_CurrentPriorityLevelConfig(u8 NewPriorityLevel);
u8 EIC_CurrentPriorityLevelValue(void);
IRQChannel_TypeDef EIC_CurrentIRQChannelValue(void);
FIQChannel_TypeDef EIC_CurrentFIQChannelValue(void);
void EIC_FIQPendingBitClear(FIQChannel_TypeDef FIQChannel);

#endif /*__71x_EIC_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
