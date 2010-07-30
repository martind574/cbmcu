/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_emi.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the EMI firmware functions
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_emi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define EMI_BankConfig(Bank)  *(vu16 *)(EMI_BASE + (4 * Bank))

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EMI_Config
* Description    : This routine is used, for each bank, to configure cycle
*                  length and bus size.
* Input          : - Bank_n: selects the bank to be configured, it can be:
*                     EMI_BANK0, EMI_BANK1, EMI_BANK2, EMI_BANK3
*                  - B_SIZE: specifies the effective external bus size for 
*                    an access to Bank n. It can be:
*                     EMI_SIZE_8: 8-bit bus length.
*                     EMI_SIZE_16: 16-bit bus lenght.
*                  - C_LENGTH: specifies the number of wait states to be 
*                    inserted in any read/write cycle performed in Bank n.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EMI_Config (u8 Bank_n, u16 B_SIZE, u16 C_LENGTH)
{   
  EMI_BankConfig(Bank_n) = (B_SIZE & 0x03) | ((C_LENGTH & 0x0F) << 2);
}

/*******************************************************************************
* Function Name  : EMI_Enable
* Description    : This routine is used, for each bank, to enable or disable 
*                  the specified EMI bank.
* Input          : - Bank_n: selects the bank to be configured, it can be:
*                     EMI_BANK0, EMI_BANK1, EMI_BANK2, EMI_BANK3
*                  - NewState: specifies wether the EMI bank will be enabled or
*                    disabled. It can be:
*                     ENABLE: enable the specified EMI bank.
*                     DISABLE: disable the specified EMI bank.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EMI_Enable (u8 Bank_n, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    EMI_BankConfig(Bank_n) |= EMI_ENABLE;
  }
  else
  {
    EMI_BankConfig(Bank_n) &= ~EMI_ENABLE;
  }
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
