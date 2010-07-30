/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_rtc.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the RTC firmware functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_rtc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : RTC_CounterValue
* Description    : This routine is used to get the current RTC counter value.
* Input          : None.
* Output         : None.
* Return         : The current counter value.
*******************************************************************************/
u32 RTC_CounterValue (void)
{
  u16 Temp1, Temp2;
  
  Temp1 = RTC->CNTL;
  Temp2 = RTC->CNTH;
  return ((u32)Temp2 << 16) | Temp1;
}

/*******************************************************************************
* Function Name  : RTC_CounterConfig
* Description    : This routine is used to update the RTC counter with a new 
*                  value.
* Input          : - CounterValue: the new RTC counter value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_CounterConfig (u32 CounterValue)
{
  /* Wait For Last Task Completition */
  RTC_WaitForLastTask();

  /* Enter to configuration mode */
  RTC_EnterCfgMode();

  /* Update the RTC counter register with the new time and date */
  /* Update the CNTL register */
  RTC->CNTL = (u16)CounterValue;

  /*  Wait For Last Task Completition */
  RTC_WaitForLastTask();

  /* Update the CNTH register */
  RTC->CNTH = (u16)(CounterValue  >> 16);

  /* Wait For Last Task Completition */
  RTC_WaitForLastTask();

  /* Exit From Configuration Mode */
  RTC_ExitCfgMode();
}

/*******************************************************************************
* Function Name  : RTC_PrescalerValue
* Description    : This routine is used to get the RTC prescaler value.
* Input          : None.
* Output         : None.
* Return         : The current RTC prescaler value.
*******************************************************************************/
u32 RTC_PrescalerValue (void)
{
  u16 Temp1, Temp2;
  
  Temp1 = RTC->PRLL;
  Temp2 = RTC->PRLH;
  return (((u32)(Temp2 & 0x000F) << 16) | Temp1);
}

/*******************************************************************************
* Function Name  : RTC_PrescalerConfig
* Description    : This routine is used to configure the prescaler.
* Input          : - Xprescaler: specifies the new RTC prescaler value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_PrescalerConfig (u32 Xprescaler)
{
  if (RTC_PrescalerValue () != Xprescaler)
  {
    /* Wait For Last Task Completion */
    RTC_WaitForLastTask();

    /* Enter In Configuration Mode */
    RTC_EnterCfgMode();

    /* Set the prescaler MSB  part */
    RTC->PRLH = (Xprescaler & 0x000F0000) >> 16;

    /* Wait For Last Task Completion */
    RTC_WaitForLastTask();

    /* Set the prescaler LSB  part */
    RTC->PRLL = (Xprescaler & 0x0000FFFF);

    /* Wait For Last Task Completion */
    RTC_WaitForLastTask();

    /* Exit From Configuration Mode */
    RTC_ExitCfgMode();
  }
}

/*******************************************************************************
* Function Name  : RTC_AlarmValue
* Description    : This routine is used to get the current RTC alarm value.
* Input          : None.
* Output         : None.
* Return         : The current RTC alarm value (u32 format).
*******************************************************************************/
u32 RTC_AlarmValue (void)
{
  u16 Temp1, Temp2;
  
  Temp1 = RTC->ALRL;
  Temp2 = RTC->ALRH;
  return (((u32)Temp2 << 16 ) | Temp1);
}


/*******************************************************************************
* Function Name  : RTC_AlarmConfig
* Description    : This routine is used to set the RTC alarm Value
* Input          : - Xalarm: specifies the new RTC alarm time value.
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_AlarmConfig (u32 Xalarm)
{
  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();

  /* Enter in Configuration Mode */
  RTC_EnterCfgMode();

  /* Set The MSB part of the Alarm Time */
  RTC->ALRH = (Xalarm & 0xFFFF0000) >> 16;

  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();

  /* Set The LSB part of the Alarm Time */
  RTC->ALRL = (Xalarm & 0x0000FFFF);

  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();

  /* Exit From Configuration Mode */
  RTC_ExitCfgMode();
}

/*******************************************************************************
* Function Name  : RTC_FlagStatus
* Description    : This routine is used to check whether the specified RTC flag
*                  is set or not
* Input          : - Xflag: designates an RTC flag, it can be:
*                     RTC_GIR, RTC_OWIR, RTC_AIR or RTC_SIR
* Output         : None.
* Return         : The specified flag status, it can be: SET or RESET
*******************************************************************************/
FlagStatus RTC_FlagStatus (RTC_FLAGS Xflag)
{
  if ((RTC->CRL & Xflag) == 0)
  {
    return RESET;
  }	
  else
  {
    return SET;
  }
}

/*******************************************************************************
* Function Name  : RTC_FlagClear
* Description    : This routine is used to clear the specified RTC flag.
* Input          : - Xflag: designates an RTC flag, it can be:
*                     RTC_GIR, RTC_OWIR, RTC_AIR or RTC_SIR
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_FlagClear (RTC_FLAGS Xflag)
{
  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();

  /* Enter In Configuration Mode */
  RTC_EnterCfgMode();

  /* Clear an RTC flag */
  RTC->CRL &= ~Xflag;

  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();

  /* Exit From Configuration Mode */
  RTC_ExitCfgMode();
}

/*******************************************************************************
* Function Name  : RTC_ITConfig
* Description    : This routine is used to enable or disable the specified RTC
*                  interrupt.
* Input          : - Xrtcit: designates an RTC interrupts. It can be:
*                     RTC_GIT, RTC_OWIT, RTC_AIT or RTC_SIT
*                  - NewState: designates the new interrupt status. It can be:
*                     ENABLE: the corresponding interrupt is enabled.
*                     DISABLE: the corresponding interrupt is disabled.
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_ITConfig (RTC_IT Xrtcit, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    RTC->CRH |= Xrtcit;
  }
  else
  {
    RTC->CRH &= ~Xrtcit;
  }
}

/*******************************************************************************
* Function Name  : RTC_ITStatus
* Description    : This routine checks whether the specified RTC interrupt
*                  is enabled or not.
* Input          : - Xrtcit: designates an RTC interrupts to check its status.
*                    It can be:
*                    RTC_GIT, RTC_OWIT, RTC_AIT or RTC_SIT
* Output         : None.
* Return         : The interrupt status. It can be:
*                  ENABLE: the corresponding interrupt is enabled.
*                  DISABLE: the corresponding interrupt is disabled.
*******************************************************************************/
FunctionalState RTC_ITStatus (RTC_IT Xrtcit)
{
  if ((RTC->CRH & Xrtcit) == 0)
  {
    return DISABLE;	 
  }
  else
  {
    return ENABLE;	
  }
}

/*******************************************************************************
* Function Name  : RTC_ITClear
* Description    : This routine is used to clear the specified interrupt 
*                  pending request.
* Input          : - Xrtcit : designates an RTC interrupt, it can be:
*                     RTC_GIT, RTC_OWIT, RTC_AIT or RTC_SIT
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_ITClear (RTC_IT Xrtcit)
{
  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();

  /* Enter In Configuration Mode */
  RTC_EnterCfgMode();

  /* Clear an RTC interrupt */
  RTC->CRL &= ~Xrtcit;

  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();

  /* Exit From Configuration Mode */
  RTC_ExitCfgMode();
}

/*******************************************************************************
* Function Name  : RTC_EnterCfgMode
* Description    : This routine is used to enter in the Configuration mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_EnterCfgMode(void)
{
  /* Set the CNF flag to enter in the Configuration mode */
  RTC->CRL |= RTC_CNF_Mask;

  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();
}

/*******************************************************************************
* Function Name  : RTC_ExitCfgMode
* Description    : This routine is used to exit from the Configuration mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_ExitCfgMode(void)
{
  /* Reset the CNF flag to exit from the Configuration mode */
  RTC->CRL &= ~RTC_CNF_Mask;

  /* Wait For Last Task Completion */
  RTC_WaitForLastTask();
}

/*******************************************************************************
* Function Name  : RTC_WaitForLastTask
* Description    : This routine is used to wait for the task to be completed
*                  on the RTC registers.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void RTC_WaitForLastTask(void)
{
  /* Loop until the Last operation Completion */
  while (!(RTC->CRL & RTC_RTOFF_Mask))
  {}
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
