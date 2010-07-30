/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_adc12.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      ADC12 firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_ADC12_H
#define __71x_ADC12_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"
#include "71x_rccu.h"

/* Exported types ------------------------------------------------------------*/
/* ADC12 Conversion modes */
typedef enum
{
  ADC12_SINGLE,
  ADC12_ROUND
} ADC12_Modes;

/* ADC12 Channels */
typedef enum
{
  ADC12_CHANNEL0 = 0x00,
  ADC12_CHANNEL1 = 0x10,
  ADC12_CHANNEL2 = 0x20,
  ADC12_CHANNEL3 = 0x30
} ADC12_Channels;

/* ADC12 control status register flag */
typedef enum
{
  ADC12_DA0 = 0x0001,
  ADC12_DA1 = 0x0002,
  ADC12_DA2 = 0x0004,
  ADC12_DA3 = 0x0008,
  ADC12_OR  = 0x2000
} ADC12_Flags;

/* Exported constants --------------------------------------------------------*/
/* Masks for the update of interrupt bit for channel n */
#define ADC12_IT0_Mask       0x0100
#define ADC12_IT1_Mask       0x0200
#define ADC12_IT2_Mask       0x0400
#define ADC12_IT3_Mask       0x0800

/* Mask for the update of all the interrupt bit in the CSR */
#define ADC12_IT_Mask        0x0F00

/* Mask for Selecting mode */
#define ADC12_Mode_Mask      0x0040

/* Mask for configuring the converter */
#define ADC12_Start_Mask     0x0020

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC12_Init(void);
void ADC12_ConversionStart (void);
void ADC12_ConversionStop(void);
void ADC12_ModeConfig (ADC12_Modes ConversionMode);
void ADC12_PrescalerConfig(u32 Adc12_clk);
void ADC12_ChannelSelect(ADC12_Channels ADC12_Channel);
FlagStatus ADC12_FlagStatus (ADC12_Flags flag);
u16 ADC12_ConversionValue(ADC12_Channels ADC12_Channel);
void ADC12_ITConfig (FunctionalState NewState);

#endif /* __71x_ADC12_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
