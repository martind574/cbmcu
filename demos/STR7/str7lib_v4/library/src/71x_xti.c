/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_xti.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the XTI firmware functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_xti.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : XTI_Init
* Description    : This routine is used to initialize the XTI cell:
*                   -All Wake-Up Lines are disabled
*                   -Interrupt disabled
*                   -Walk-up mode disabled
*                   -Set on the falling edge of the input wake-up line
*                   -All pending bits are cleared
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void XTI_Init (void)
{
  XTI->SR = 0x00;
  XTI->MRH = 0x00;
  XTI->MRL = 0x00;
  XTI->TRH = 0x00;
  XTI->TRL = 0x00;
  XTI->PRH = 0x00;
  XTI->PRL = 0x00;
  
  /* Write the STOP bit twice to reset the STOP state machine */
  XTI->CTRL = 0x00;
  XTI->CTRL = 0x00;
}

/*******************************************************************************
* Function Name  : XTI_ModeConfig
* Description    : This function is used to enable or disable the interrupt and
*                  the wake-up mode of the specified input line.
* Input          : - Mode: this parameter specifies the input line, it can be:
*                    XTI_WakeUp, XTI_Interrupt or XTI_WakeUpInterrupt.
*                  - NewState: used to enable or disable the selected mode.
*                    it can be: ENABLE or DISABLE.
* Output         : None.
* Return         : None.
*******************************************************************************/
void XTI_ModeConfig (XTIMode_TypeDef Mode, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    XTI->CTRL |= Mode;
  }
  else
  {
    XTI->CTRL &= ~Mode;
  }
}

/*******************************************************************************
* Function Name  : XTI_LineModeConfig
* Description    : This routine is used to configure the trigger edge.
* Input          : - Lines: lines to be configured.
*                  - TriggerEdge: specifies the trigger edge polarity of the
*                    specified wake-up lines. It can be:
*                     FallingEdge
*                     RisingEdge
* Output         : None.
* Return         : None.
*******************************************************************************/
void XTI_LineModeConfig (u16 Lines, XTITriggerEdge_TypeDef TriggerEdge)
{
  if (TriggerEdge == XTI_FallingEdge)
  {
    XTI->TRL &= ~Lines;
    XTI->TRH &= ~(Lines >> 8) & 0x00FF;
  }
  else
  {
    XTI->TRL |= Lines;
    XTI->TRH |= (Lines >> 8) & 0x00FF;
  }
}

/*******************************************************************************
* Function Name  : XTI_LineConfig
* Description    : This routine is used to enable and disable the interrupts
*                  lines.
* Input          : - Lines: specifies the lines to be configured. You can select
*                    more than one line, by logically OR’ing them.
*                  - NewState: the input line interrupt new status to be set.
*                    It can be:
*                    ENABLE: to enable the input line interrupt.
*                    DISABLE: to disable the input line interrupt.
* Output         : None
* Return         : None
*******************************************************************************/
void XTI_LineConfig (u16 Lines, FunctionalState NewState)
{
  if (NewState)
  {
    XTI->MRL |= Lines;
    XTI->MRH |= (Lines >> 8 ) & 0x00FF;
  }
  else
  {
    XTI->MRL &= ~Lines;
    XTI->MRH &= ~(Lines >> 8 ) & 0x00FF;
  }
}

/*******************************************************************************
* Function Name  : XTI_InterruptLineValue
* Description    : Gets and returns the input line number that generates an 
*                  Interrupt.
* Input          : None.
* Output         : None.
* Return         : The line number that generates the interrupt.
*******************************************************************************/
u16 XTI_InterruptLineValue (void)
{
  u16 Temp1, Temp2;

  Temp1 = XTI->PRL;
  Temp2 = XTI->PRH;
  return Temp1 | ((u16)Temp2 << 8);
}

/*******************************************************************************
* Function Name  : XTI_PendingBitClear
* Description    : This routine is used to clear the XTI interrupt pending bits.
* Input          : - Lines: specifies the input wake-up lines interrupt 
*                     the input wake-up lines interrupt. You can select more 
*                     than one line by logically OR’ing them.
* Output         : None.
* Return         : None.
*******************************************************************************/
void XTI_PendingBitClear (u16 Lines)
{
  XTI->PRL &= ~Lines;
  XTI->PRH &= ~((Lines >> 8) & 0x00FF);
}

/*******************************************************************************
* Function Name  : XTI_SWIRQGenerate
* Description    : This routine is used to generate a software IRQ interrupt.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void XTI_SWIRQGenerate (void)
{
  XTI->SR = 0x01;
  XTI->SR = 0x00;
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
