/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_emi.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      EMI firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_EMI_H
#define __71x_EMI_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* EMI enable */
#define EMI_ENABLE           0x8000

/* Banks */
#define EMI_BANK0            0x00           
#define EMI_BANK1            0x01           
#define EMI_BANK2            0x02           
#define EMI_BANK3            0x03 

/* EMI data bus lenght */
#define EMI_SIZE_8           0x0000
#define EMI_SIZE_16          0x0001

/* Number of wait states */
#define EMI_0_WaitState      0x00
#define EMI_1_WaitState      0x01
#define EMI_2_WaitStates     0x02
#define EMI_3_WaitStates     0x03
#define EMI_4_WaitStates     0x04
#define EMI_5_WaitStates     0x05
#define EMI_6_WaitStates     0x06
#define EMI_7_WaitStates     0x07
#define EMI_8_WaitStates     0x08
#define EMI_9_WaitStates     0x09
#define EMI_10_WaitStates    0x0A
#define EMI_11_WaitStates    0x0B
#define EMI_12_WaitStates    0x0C
#define EMI_13_WaitStates    0x0D
#define EMI_14_WaitStates    0x0E
#define EMI_15_WaitStates    0x0F
       

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void EMI_Config(u8 Bank_n, u16 B_SIZE, u16 C_LENGTH);
void EMI_Enable(u8 Bank_n, FunctionalState NewState);

#endif /* __71x_EMI_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
