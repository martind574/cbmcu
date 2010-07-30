/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_rtc.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      RTC firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_RTC_H
#define __71x_RTC_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  RTC_GIR  = 0x0008,
  RTC_OWIR = 0x0004,
  RTC_AIR  = 0x0002,
  RTC_SIR  = 0x0001
} RTC_FLAGS;

typedef enum
{
  RTC_GIT  = 0x0008,
  RTC_OWIT = 0x0004,
  RTC_AIT  = 0x0002,
  RTC_SIT  = 0x0001
} RTC_IT;

/* Exported constants --------------------------------------------------------*/
/* Second interrupt */
#define RTC_SI_Mask    0x0001

/* Alarm interrupt */
#define RTC_AI_Mask    0x0002

/* OverFlow interrupt */
#define RTC_OWI_Mask   0x0004

/* Global interrupt */
#define RTC_GI_Mask    0x0008

/* Configuration Flag Mask */
#define RTC_CNF_Mask   0x0010

/* Operation OFF flag */
#define RTC_RTOFF_Mask 0x0020

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
u32 RTC_CounterValue (void);
void RTC_CounterConfig (u32 CounterValue);
u32 RTC_PrescalerValue (void);
void RTC_PrescalerConfig (u32 Xprescaler);
u32 RTC_AlarmValue (void);
void RTC_AlarmConfig (u32 Xalarm);
FlagStatus RTC_FlagStatus (RTC_FLAGS Xflag);
void RTC_FlagClear (RTC_FLAGS Xflag);
void RTC_ITConfig (RTC_IT Xrtcit, FunctionalState NewState);
FunctionalState RTC_ITStatus (RTC_IT Xrtcit);
void RTC_ITClear (RTC_IT Xrtcit);
void RTC_EnterCfgMode(void);
void RTC_ExitCfgMode(void);
void RTC_WaitForLastTask(void);

#endif /*__71x_RTC_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
