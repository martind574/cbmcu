/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_pcu.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      PCU firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_PCU_H
#define __71x_PCU_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  PCU_WREN = 0x8000,
  PCU_VROK = 0x1000
} PCU_Flags;

typedef enum
{
  PCU_STABLE,
  PCU_UNSTABLE
} PCU_VR_Status;

typedef enum
{
  PCU_MVR = 0x0008,
  PCU_LPR = 0x0010
} PCU_VR;

typedef enum
{
  WFI_CLOCK2_16,
  WFI_Ck_AF
} WFI_CLOCKS;

typedef enum
{
  LPWFI_CLK2_16,
  LPWFI_CK_AF
} LPWFI_Clock_Typedef;

/* Exported constants --------------------------------------------------------*/
/* RCCU_CCR register bits definition */
/* Bit 11: Enable Halt bit */
#define PCU_EN_HALT_Mask     0x00000800

/* Bit 0: Low Power Mode in Wait For interrupt Mode */
#define PCU_LPOWFI_Mask      0x00000001
 
/* PCU_PWRCR register bits definition */
/* Bit 15: PCU register Write Enable Bit */
#define PCU_WREN_Mask        0x8000

/* Bit 14: PCU register Backup logic Busy (programming ongoing) flag */
#define PCU_BUSY_Mask        0x4000

/* Bit 12: Voltage Regulator OK flag */
#define PCU_VROK_Mask        0x1000

/* Bit 8: Low Voltage Detector Disable bit */
#define PCU_LVD_DIS_Mask     0x0100

/* Bit 4: Low Power Regulator in Wait For interrupt Mode bit */
#define PCU_LPRWFI_Mask      0x0010

/* Bit 3: Main Regulator Bypass bit */
#define PCU_VRBYP_Mask       0x0008

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
PCU_VR_Status PCU_MVRStatus (void);
FlagStatus PCU_FlagStatus (PCU_Flags Xflag);
void PCU_VRConfig (PCU_VR xVR, FunctionalState NewState);
FunctionalState PCU_VRStatus (PCU_VR xVR);
void PCU_LVDDisable (void);
FunctionalState PCU_LVDStatus (void);
void PCU_LPModesConfig(FunctionalState PLL1_State, FunctionalState MVR_State,
                       FunctionalState FLASH_State, FunctionalState LPWFI_State,
                       LPWFI_Clock_Typedef LPWFI_Clock);
void PCU_WFI (void);
void PCU_STOP (void);
void PCU_STANDBY( void);
void PCU_FlashBurstCmd (FunctionalState NewState);
void PCU_32OSCCmd (FunctionalState NewState);

#endif /*__71x_PCU_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
