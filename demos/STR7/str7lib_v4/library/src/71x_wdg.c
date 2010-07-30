/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_WDG.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the WDG firmware functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_wdg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : WDG_Enable
* Description    : Enables the Watchdog Mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_Enable (void)
{
  WDG->CR |= 0x01;
}

/*******************************************************************************
* Function Name  : WDG_CntRefresh
* Description    : Refreshs and update the WDG counter to avoid a system reset.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_CntRefresh (void)
{
  /* Write the first value in the key register */
  WDG->KR = 0xA55A;

  /* Write the second value in the key register */
  WDG->KR = 0x5AA5;
}

/*******************************************************************************
* Function Name  : WDG_PrescalerConfig
* Description    : Sets the counter prescaler value. The clock to Timer Counter 
*                  is divided by (Prescaler + 1)
* Input          : - Prescaler: specifies the prescaler value (8 bit).
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_PrescalerConfig (u8 Prescaler)
{
  WDG->PR = Prescaler;
}

/*******************************************************************************
* Function Name  : WDG_CntReloadUpdate
* Description    : Updates the counter pre-load value.
* Input          : - PreLoadValue: specifies the pre-load value (16 bit)
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_CntReloadUpdate (u16 PreLoadValue)
{
  WDG->VR = PreLoadValue;
}

/*******************************************************************************
* Function Name  : WDG_CntOnOffConfig
* Description    : Starts or stops the free auto-reload timer to count down.
* Input          : - NewState: specifies how the timer have to be started 
*                    or stopped. It can be:
*                     ENABLE: the counter loads the Timer pre-load value and
*                     starts counting.
*                     DISABLE: the counter is stopped.
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_CntOnOffConfig (FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    WDG->CR |= 0x0002;
  }
  else
  {
    WDG->CR &= ~0x0002;
  }
}

/*******************************************************************************
* Function Name  : WDG_ECITConfig
* Description    : Enables or Disables the WDG end of count interrupt.
* Input          : - NewState: specifies whether the WDG  end of count interrupt
*                    is enabled or disabled, it can be:
*                     ENABLE: enables the WDG IRQ interrupt.
*                     DISABLE: disables the WDG IRQ interrupt.
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_ECITConfig (FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    WDG->MR |= 0x0001;
  }
  else
  {
    WDG->MR &= ~0x0001;
  }
}

/*******************************************************************************
* Function Name  : WDG_ECFlagClear
* Description    : Clears the end of count flag.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_ECFlagClear (void)
{
  WDG->SR = 0x0000;
}

/*******************************************************************************
* Function Name  : WDG_ECStatus
* Description    : Reads and returns the status register.
* Input          : None.
* Output         : None.
* Return         : The end of count status.
*******************************************************************************/
u16 WDG_ECStatus (void)
{
  return WDG->SR;
}

/*******************************************************************************
* Function Name  : abs_value
* Description    : Returns the absolute value of x.
* Input          :  x: the number to compute its absolute value.
* Output         : None.
* Return         : None.
*******************************************************************************/
static long abs_value(long x)
{
  if (x > 0)
  {
    return x;	
  }	
  else
  {
    return (-x);	
  }
}

/*******************************************************************************
* Function Name  : FindFactors
* Description    : Searchs for the best (a,b) values that fit n = a*b
*                  with the following constraints: 1<=a<=256, 1<=b<=65536
* Input          : - n: the number to decompose.
* Output         : - a: a pointer to the first factor.
*                  - b: a pointer to the second factor.
* Return         : None.
*******************************************************************************/
static void FindFactors(u32 n, u16 *a, u32 *b)
{
  u32 b0;
  u16 a0;
  long err, err_min = n;

  *a = a0 = ((n - 1) / 65536ul) + 1;
  *b = b0 = n / *a;

  for (; *a <= 256; (*a)++)
  {
    *b = n / *a;
    err = (long) * a * (long) * b - (long)n;
    if (abs_value(err) > (*a / 2))
    {
      (*b)++;
      err = (long) * a * (long) * b - (long)n;
    }
    if (abs_value(err) < abs_value(err_min))
    {
      err_min = err;
      a0 = *a;
      b0 = *b;
      if (err == 0)
      {
        break;
      }
    }
  }

  *a = a0;
  *b = b0;
}

/*******************************************************************************
* Function Name  : WDG_PeriodValueConfig
* Description    : Sets the prescaler and counter reload value.
* Input          : Time: the amount of needed time, in microseconds.
* Output         : None.
* Return         : None.
*******************************************************************************/
void WDG_PeriodValueConfig ( u32 Time )
{
  u16 a;
  u32 n, b;

  n = Time * (RCCU_FrequencyValue(RCCU_PCLK2) / 1000000);
  FindFactors(n, &a, &b);
  WDG->PR = a - 1;
  WDG->VR = b - 1;
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
