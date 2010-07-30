/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_eic.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the EIC firmware functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_eic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EIC_Init
* Description    : Initialise the EIC using the load PC instruction
*                   FIQ and IRQ are disabled, 
*                   All channel interrupts are disabled, 
*                   All pending bits are cleared.
*                   The current priority level set to zero, 
*                   IVR register initialized with the upper half of the load PC
*                   instruction op-code, 
*                   All SIR registers are initialized with the offset to the
*                   corresponding IRQ routine vector.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_Init (void)
{
  extern u32 T0TIMI_Addr;
  u8 bCounter;
  u32 dOffset = ((u32) & T0TIMI_Addr);

  /* Disable FIQ and IRQ interrupts */
  EIC->ICR = 0x00000000;

  /* Disable all channels interrupts */
  EIC->IER = 0x00000000;

  /* Clear all pending bits */
  EIC->IPR = 0xFFFFFFFF;

  /* Disable all FIQ channels interrupts and clear FIQ */
  EIC->FIR = 0x0000000C;

  /* channels pending bits */
  /* Set the current priority level to zero */
  EIC->CIPR = 0x00000000;

  /* IVR = high half of load PC instruction */
  EIC->IVR  = 0xE59F0000;

  dOffset = (dOffset + 0x00007E0) << 16;

  /* Initialize SIRn registers */
  for (bCounter = 0; bCounter < 32; bCounter++)
  {
    EIC->SIR[bCounter] = dOffset | 0xF0000000;
    dOffset += 0x00000004 << 16;
  }
}

/*******************************************************************************
* Function Name  : EIC_IRQConfig
* Description    : Enables or Disables IRQ interrupts.
* Input          : - NewState: specifies whether the IRQ is enabled or disabled
*                    it can be:
*                     ENABLE : enables the IRQ interrupt.
*                     DISABLE : disables the IRQ interrupt.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_IRQConfig (FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    EIC->ICR |= 0x0001;
  }
  else
  {
    EIC->ICR &= ~0x0001;
  }
}

/*******************************************************************************
* Function Name  : EIC_FIQConfig
* Description    : Enable or Disable FIQ interrupts.
* Input          : - NewState: the FIQ interrupt new status to be set. 
*                    It can be:
*                     ENABLE: enables the FIQ interrupt.
*                     DISABLE: disables the FIQ interrupt.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_FIQConfig (FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    EIC->ICR |= 0x0002;
  }
  else
  {
    EIC->ICR &= ~0x0002;
  }
}

/*******************************************************************************
* Function Name  : EIC_IRQChannelConfig
* Description    : Configures the specified IRQ Channel.
* Input          : - IRQChannel: the channel to be configured.
*                  - NewState: specifies whether the IRQ channel interrupt will
*                    be enabled or disabled, t can be:
*                     ENABLE: enables the channel interrupt.
*                     DISABLE: disables the channel interrupt.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_IRQChannelConfig (IRQChannel_TypeDef IRQChannel,
                           FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    EIC->IER |= 0x0001 << IRQChannel;
  }
  else
  {
    EIC->IER &= ~(0x0001 << IRQChannel);
  }
}

/*******************************************************************************
* Function Name  : EIC_FIQChannelConfig
* Description    : Configure the FIQ Channel
* Input          : - FIQChannel: the FIQ channel to be configured. It can be:
*                     T0TIMI_FIQChannel, WDG_FIQChannel, WDGT0TIMI_FIQChannels
*                  - NewState: specifies whether the FIQ channel interrupt 
*                    will be enabled or disabled. It can be:
*                     ENABLE: enables the FIQ channel interrupt.
*                     DISABLE: disables the FIQ channel interrupt.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_FIQChannelConfig (FIQChannel_TypeDef FIQChannel,
                          FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    EIC->FIR |= FIQChannel;
  }
  else
  {
    EIC->FIR &= ~FIQChannel;
  }
}

/*******************************************************************************
* Function Name  : EIC_IRQChannelPriorityConfig
* Description    : Configures the selected IRQ channel priority.
* Input          : - IRQChannel: the channel to be configured.
*                  - Priority: specifies the priority of the channel.
*                    Priority variable must take an integer value in the 
*                    range [0..15].
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_IRQChannelPriorityConfig (IRQChannel_TypeDef IRQChannel, u8 Priority)
{
  EIC->SIR[IRQChannel] = (EIC->SIR[IRQChannel] & 0xFFFF0000) \
                         | (u16)Priority & 0x000F;
}

/*******************************************************************************
* Function Name  : EIC_CurrentPriorityLevelConfig
* Description    : Changes the current priority level of the served IRQ routine.
* Input          : - NewPriorityLevelNew: specifies the new priority level.
*                    It must be an integer in the range [0..15].
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_CurrentPriorityLevelConfig (u8 NewPriorityLevel)
{
  vu32 dVal;

  /* Save ICR content */
  dVal = EIC->ICR;

  /* Disable IRQ interrupts. */
  EIC->ICR &= ~0x0001;

  /* Change the current priority */
  EIC->CIPR = NewPriorityLevel;

  /* Restore ICR content */
  EIC->ICR = dVal;
}

/*******************************************************************************
* Function Name  : EIC_CurrentPriorityLevelValue
* Description    : Returns the current priority level of the current served IRQ
*                  routine.
* Input          : None.
* Output         : None.
* Return         : The current priority level
*******************************************************************************/
u8 EIC_CurrentPriorityLevelValue (void)
{
  return EIC->CIPR & 0xF;
}

/*******************************************************************************
* Function Name  : EIC_CurrentIRQChannelValue
* Description    : Returns the current served IRQ channel number.
* Input          : None.
* Output         : None.
* Return         : The current served IRQ channel number.
*******************************************************************************/
IRQChannel_TypeDef EIC_CurrentIRQChannelValue (void)
{
  return (IRQChannel_TypeDef)(EIC->CICR & 0x1F);
}

/*******************************************************************************
* Function Name  : EIC_CurrentFIQChannelValue
* Description    : Gets and returns the current served FIQ channel.
* Input          : None.
* Output         : None.
* Return         : The current served FIQ channel.
*******************************************************************************/
FIQChannel_TypeDef EIC_CurrentFIQChannelValue (void)
{
  return (FIQChannel_TypeDef)((EIC->FIR >> 2) & 0x0003);
}

/*******************************************************************************
* Function Name  : EIC_FIPendingBitClear
* Description    : Clears the FIQ pending bit.
* Input          : - FIQChannel: specifies the FIQ channel to be configured.
*                    It can be:
*                     T0TIMI_FIQChannel, WDG_FIQChannel, WDGT0TIMI_FIQChannels
* Output         : None.
* Return         : None.
*******************************************************************************/
void EIC_FIQPendingBitClear (FIQChannel_TypeDef FIQChannel)
{
  EIC->FIR = (EIC->FIR & 0x0003) | (FIQChannel << 2);
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
