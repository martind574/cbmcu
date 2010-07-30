/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_wdg.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      WDG firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_WDG_H
#define __71x_WDG_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"
#include "71x_rccu.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void WDG_Enable (void);
void WDG_CntRefresh (void);
void WDG_PrescalerConfig (u8 Prescaler);
void WDG_CntReloadUpdate (u16 PreLoadValue);
void WDG_PeriodValueConfig (u32 Time);
void WDG_CntOnOffConfig (FunctionalState NewState);
void WDG_ECITConfig (FunctionalState NewState);
void WDG_ECFlagClear (void);
u16 WDG_ECStatus (void);

#endif /*__71x_WDG_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
