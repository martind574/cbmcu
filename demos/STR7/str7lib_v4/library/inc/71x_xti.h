/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_xti.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      XTI firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_XTI_H
#define __71x_XTI_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  XTI_WakeUp = 1,
  XTI_Interrupt,
  XTI_WakeUpInterrupt
} XTIMode_TypeDef;

typedef enum
{
  XTI_FallingEdge,
  XTI_RisingEdge
} XTITriggerEdge_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define XTI_Line0            0x0001
#define XTI_Line1            (XTI_Line0 << 1)
#define XTI_Line2            (XTI_Line1 << 1)
#define XTI_Line3            (XTI_Line2 << 1)
#define XTI_Line4            (XTI_Line3 << 1)
#define XTI_Line5            (XTI_Line4 << 1)
#define XTI_Line6            (XTI_Line5 << 1)
#define XTI_Line7            (XTI_Line6 << 1)
#define XTI_Line8            (XTI_Line7 << 1)
#define XTI_Line9            (XTI_Line8 << 1)
#define XTI_Line10           (XTI_Line9 << 1)
#define XTI_Line11           (XTI_Line10 << 1)
#define XTI_Line12           (XTI_Line11 << 1)
#define XTI_Line13           (XTI_Line12 << 1)
#define XTI_Line14           (XTI_Line13 << 1)
#define XTI_Line15           (XTI_Line14 << 1)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void XTI_Init (void);
void XTI_ModeConfig (XTIMode_TypeDef Mode, FunctionalState NewState);
void XTI_LineModeConfig (u16 Lines, XTITriggerEdge_TypeDef TriggerEdge);
void XTI_LineConfig (u16 Lines, FunctionalState NewState);
u16 XTI_InterruptLineValue (void);
void XTI_PendingBitClear (u16 Lines);
void XTI_SWIRQGenerate (void);

#endif /*__71x_XTI_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
