/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_pcu.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the Power Control Unit functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_pcu.h"
#include "71x_rccu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : PCU_MVRStatus
* Description    : This routine is used to check and return the Main Voltage 
*                  Regulator stability status.
* Input          : None.
* Output         : None.
* Return         : The stability status of the Main Voltage Regulator,
*                  it can be:
*                   STABLE, UNSTABLE
*******************************************************************************/
PCU_VR_Status PCU_MVRStatus (void)
{
  if ((PCU->PWRCR & PCU_VROK_Mask) == 0x00)
  {
    return PCU_UNSTABLE;
  }
 else
  {
    return PCU_STABLE;
  }
}

/*******************************************************************************
* Function Name  : PCU_FlagStatus
* Description    : This routine is used to return the PCU register flag
* Input          : - Xflag: the flag to get the status.
* Output         : None.
* Return         : the status of the flag passed in parameter, it can be: 
*                  SET or RESET 
*******************************************************************************/
FlagStatus PCU_FlagStatus (PCU_Flags Xflag)
{
  if ((PCU->PWRCR & Xflag) == 0x00)
  {
    return RESET;	
  }
  else
  {
    return SET;	
  }
}

/*******************************************************************************
* Function Name  : PCU_VRConfig
* Description    : This routine is used to configure PCU voltage regultors.
* Input          : - Xvr: Specifies the PCU voltage regulator, it can be:
*                     PCU_MVR : Main voltage Regulator
*                     PCU_LPR : Low Power Regulator
*                : - NewState: Specifies whatever the corresponding voltage 
*                    regulator is enabled or bypassed, it can be:
*                     ENABLE : Enable the Voltage Regulator.
*                     DISABLE: Disable ( ByPass ) the VR.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PCU_VRConfig (PCU_VR Xvr, FunctionalState NewState)
{
  vu16 Tmp = PCU->PWRCR;
  
  switch (Xvr)
  {
    case PCU_MVR :
      /* Configure the Main Voltage Regulator */
      if (NewState == DISABLE)
      {
        Tmp |= PCU_VRBYP_Mask;
      }
      else
      {
        Tmp &= ~PCU_VRBYP_Mask;
      }
      break;
      
    case PCU_LPR :
      /* Configure the Low power Voltage Regulator */
      if (NewState == DISABLE)
      {
        Tmp |= PCU_LPRWFI_Mask;
      }
      else
      {
        Tmp &= ~PCU_LPRWFI_Mask;
      }
      break;
  }

  while ((PCU->PWRCR & PCU_BUSY_Mask) == 1)
  {
    /* Wait until the previous write operation is completed */
  }

  /*  Unlock Power Control Register */
  PCU->PWRCR |= PCU_WREN_Mask;
  PCU->PWRCR = Tmp | PCU_WREN_Mask;
}

/*******************************************************************************
* Function Name  : PCU_LVDDisable
* Description    : This routine is used to disable the Low Voltage Detector.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PCU_LVDDisable (void)
{
  
  while ((PCU->PWRCR & PCU_BUSY_Mask) == 1)
  {
    /* Wait until the previous write operation will be completed */
  }

  /*  Unlock Power Control Register */
  PCU->PWRCR |= PCU_WREN_Mask;

  /*  Set the LVD DIS Flag */
  PCU->PWRCR |= PCU_LVD_DIS_Mask;
}

/*******************************************************************************
* Function Name  : PCU_VRStatus
* Description    : This routine is used to get the PCU voltage regultors status.
* Input          : - xVR: the voltage regulator to get its status, it can be:
*                     PCU_MVR : Main voltage Regulator.
*                     PCU_LPR : Low Power Regulator.
* Output         : None.
* Return         : the status of the voltage regulator passed in parameter.
*                  It can be:
*                   ENABLE : the Voltage Regulator is enabled.
*                   DISABLE: the Voltage Regulator is passed.
*******************************************************************************/
FunctionalState PCU_VRStatus (PCU_VR xVR)
{
  if ((PCU->PWRCR & xVR) == 0)
  {
    return ENABLE;	
  }
  else
  {
    return DISABLE;
  }	
}

/*******************************************************************************
* Function Name  : PCU_LVDStatus
* Description    : This routine is used to get and return the LVD status.
* Input          : None.
* Output         : None.
* Return         : The LVD status, it can be:
*                   ENABLE: the LVD is enabled.
*                   DISABLE: the LVD is disabled.
*******************************************************************************/
FunctionalState PCU_LVDStatus (void)
{
  if ((PCU->PWRCR & PCU_LVD_DIS_Mask) == 0)
  {
    return ENABLE;
  }	
  else
  {
    return DISABLE;
  }
}

/*******************************************************************************
* Function Name  : PCU_LPModesConfig
* Description    : This routine is used to configure the different STR71x
*                  low power modes options
* Input          : - PLL1_State: the state of PLL1 when CK_AF selected.It can be:
*                     ENABLE : PLL1 is not disabled when CK_AF is selected.
*                     DISABLE: PLL1 is disabled automaticaty when CK_AF 
*                     is selected as system clock.
*                  - MVR_State: the state of the Main Voltage Regulator when 
*                    CK_AF is selected. It can be:
*                     ENABLE : MVREG is enabled during LPWFI and STOP modes
*                     DISABLE: MVREG is disabled during LPWFI and STOP modes
*                  - FLASH_State: the state of the flash during LPWFI and STOP
*                    modes. It can be:
*                     ENABLE : Flash Stand-by mode during LPWFI and STOP modes
*                     DISABLE: FLASH in powerdown during LPWFI and STOP modes
*                  - LPWFI_State: the state of low power mode during LPWFI.
*                    It can be:
*                     ENABLE : Enable Low power mode during WFI mode (LPWFI)
*                     DISABLE: Disable Low power modeduring WFI mode (WFI).
*                  - LPWFI_Clock: the selected clock during LPWFI. It can be:
                      LPWFI_CLK2_16: CLK2/16 is selected during LPWFI.
*                     LPWFI_CK_AF  : CK_AF is selected during LPWFI.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PCU_LPModesConfig (FunctionalState PLL1_State, FunctionalState MVR_State,
                       FunctionalState FLASH_State, FunctionalState LPWFI_State,
                       LPWFI_Clock_Typedef LPWFI_Clock)
{

  /* Configure if the PLL1 is disabled automatically when CK_AF is selected
   as system clock */
  if (PLL1_State == DISABLE)
  {
    /* PLL1 is disabled when CK_AF is selected */
    RCCU->CFR |= 1 << 4;
  }
  else
  {
    /* PLL1 is not disabled when CK_AF is selected */
    RCCU->CFR &= ~(1 << 4);
  }

  /* Configure the MVREG state during LPWFI and STOP modes */
  if (MVR_State == DISABLE)
  {
    /* MVREG is disabled during LPWFI and STOP modes */
    /*  Unlock Power Control Register */
    PCU->PWRCR |= PCU_WREN_Mask;
    PCU->PWRCR |= PCU_LPRWFI_Mask | PCU_WREN_Mask;
  }
  else
  {
    /* MVREG is enabled during LPWFI and STOP modes */
    /*  Unlock Power Control Register */
    PCU->PWRCR |= PCU_WREN_Mask;
    PCU->PWRCR &= (~(1 << 4)) | PCU_WREN_Mask;
  }

  /* Configure the FLASH state during LPWFI and STOP modes */
  if (FLASH_State == DISABLE)
  {
    /* FLASH in PWD mode during LPWFI and STOP modes */
    FLASHR->CR0 |= 1 << 15;
  }
  else
  {
    /* FLASH is enabled during LPWFI and STOP modes */
    FLASHR->CR0 &= ~(1 << 15);
  }
  /* Configure the low power mode during WFI mode */
  if (LPWFI_State == ENABLE)
  {
    /* Set bit LOPWFI for selecting LPWFI mode */
    RCCU->CCR |= 0x1;
  }
  else
  {
    RCCU->CCR &= ~0x1;
  }
  /* Configure the clock during LPWFI mode */
  if (LPWFI_Clock == LPWFI_CK_AF)
  {
    /* Select the 32KHz as peripheral clock during LPWFI */
    RCCU->CCR  |= 0x2;
  }
  else
  {
    /* Select CLK2/16 as peripheral clock during LPWFI */
    RCCU->CCR  &= ~0x2;
  }
}

/*******************************************************************************
* Function Name  : PCU_WFI
* Description    : This routine is used to enter into WFI and LPWFI modes.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PCU_WFI (void)
{
  /* Reset bit WFI in the RCCU_SMR register */
  RCCU->SMR &= 0xFE ;
}

/*******************************************************************************
* Function Name  : PCU_STOP
* Description    : This routine is used to enter into STOP mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PCU_STOP (void)
{
  vu32 temp;

  /* Set bit ID1St and WKUP-int bits in XTI_CTRL register */
  XTI->CTRL |= 0x03;

  /* Reset the STOP bit in XTI_CTRL register */
  XTI->CTRL &= 0x03;
  
  /* Reset the STOP_I bit in the CLK_FLAG register */
  RCCU->CFR &= 0xBFFF;
  
  /* Write '1' to Stop Bit */
  XTI->CTRL |= 0x04;
  
  /* Write '0' to Stop Bit */
  XTI->CTRL &= 0x03;
  
  /* Write '1' to Stop Bit */
  XTI->CTRL |= 0x04;
  
  /* Some dummy instructions after the STOP sequence */
  temp = 0;
  temp = 1;
  temp = 2;
  temp = 3;
  temp = 4;
  temp = 5;
  temp = 6;
  temp = 7;
  temp = 8;
}

/*******************************************************************************
* Function Name  : PCU_STANDBY
* Description    : This routine is used to enter into STANDBY mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PCU_STANDBY (void)
{
  /* Enter in Standby mode */
  PCU->PWRCR |= 0x8000;
  PCU->PWRCR |= 0x0040;
}

/*******************************************************************************
* Function Name  : PCU_FlashBurstCmd
* Description    : This routine is used to set the FLASH in LP/BURTS mode
* Input          : - NewState: specifies whether the FLASH BURST mode is enabled
*                    or disabled. It can be:
*                     ENABLE : FLASH in BURST mode (default mode)
*                     DISABLE: FLASH in LP mode, the maximum allowed execution
*                     frequency = 33MHz
* Output         : None.                   
* Return         : None.
*******************************************************************************/
void PCU_FlashBurstCmd (FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    PCU->PWRCR |= 0x8000;
    PCU->PWRCR |= 0x8200;
  }
  else
  {
    PCU->PWRCR |= 0x8000;
    PCU->PWRCR &= ~0x8200;
  }
}

/*******************************************************************************
* Function Name  : PCU_32OSCCmd
* Description    : This routine is used to Enable/Disable the 32KHz oscillator
* Input          : - NewState: specifies whether the 32 kHz oscillator is 
*                    enabled or disabled. It can be:
*                     ENABLE  : 32KHz oscillator is enabled
*                     DISABLE : The 32KHz oscillator is bypassed, and allow an
*                     external reference clock to feed the Real Time Clock, or 
*                     a Backup clock source to the whole system.
* Return         : None
*******************************************************************************/
void PCU_32OSCCmd (FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    PCU->PWRCR |= 0x8000;
    PCU->PWRCR |= 0x8080;
  }
  else
  {
    PCU->PWRCR |= 0x8000;
    PCU->PWRCR &= ~0x8080;
  }
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/

