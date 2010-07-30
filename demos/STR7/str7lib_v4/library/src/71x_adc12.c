/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_adc12.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the ADC12 firmware functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_adc12.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name      : ADC12_Init
* Description        : This routine is used to initialize the ADC12 registers to
*                      their reset values.
* Input              : None.
* Output             : None.
* Return             : None.
*******************************************************************************/
void ADC12_Init(void)
{
  /* Initiate ADC12 registers to their reset values */
  ADC12->CSR  = 0x0000;
  ADC12->CPR  = 0x0005;
}

/*******************************************************************************
* Function Name      : ADC12_ConversionStart
* Description        : This routine is used to launch the conversion.
* Input              : None.
* Output             : None.
* Return             : None.
*******************************************************************************/
void ADC12_ConversionStart (void)
{
  /* Set the ADCen bit of the BOOTCR register */
  PCU->BOOTCR |= ADC12_Start_Mask;
}

/*******************************************************************************
* Function Name      : ADC12_ConversionStop
* Description        : This routine is used to disable the ADC12 cell.
* Input              : None.
* Output             : None.
* Return             : None.
*******************************************************************************/
void ADC12_ConversionStop(void)
{
  /* Clear the ADCen bit of the BOOTCR register */
  PCU->BOOTCR &= ~ADC12_Start_Mask;
}


/*******************************************************************************
* Function Name  : ADC12_ModeConfig
* Description    : This routine is used to select the mode of conversion.
* Input          : - Mode: the mode of conversion. I can be:
*                     ADC12_SINGLE: Single channel mode.
*                     ADC12_ROUND : Round robin mode.
* Output         : None.
* Return         : None.
*******************************************************************************/
void ADC12_ModeConfig (ADC12_Modes Mode)
{
  /* Select the mode of conversion and update the CSR */
  if(Mode == ADC12_SINGLE)
  {
    /* Select Single mode */	
    ADC12->CSR |= ADC12_Mode_Mask;
  }
  else
  {
   /* Select Round Robin mode */	
   ADC12->CSR &= ~ADC12_Mode_Mask;
  }
}

/*******************************************************************************
* Function Name      : ADC12_PrescalerConfig
* Description        : This function is used to configure the ADC sampling 
*                      frequency by setting the prescaler register.
* Input              : - Adc12_clk: specifies the sampling frequency in Hz.
* Output             : None.
* Return             : None.
*******************************************************************************/
void ADC12_PrescalerConfig(u32 Adc12_clk)
{
  u32 temp = 0;

  temp = (vu16)((RCCU_FrequencyValue(RCCU_PCLK2)*10) / (Adc12_clk * 512 * 8));
  
  /* Configure the ADC12_CPR register with the nearest prescaler value */
  if(temp - ((temp/10)*10) < 5)
  {
    ADC12->CPR = (u16)(temp/10);
  }
  else
  {
    ADC12->CPR = (u16)((temp/10)+1);
  }
}

/*******************************************************************************
* Function Name      : ADC12_ChannelSelect
* Description        : This function selects the channel to be converted 
*                      in single channel mode of conversion.
* Input              : - ADC12_Channel: specifies the channel to be converted.
*                        It may be:
*                         ADC12_CHANNEL0 : select channel 0
*                         ADC12_CHANNEL1 : select channel 1
*                         ADC12_CHANNEL2 : select channel 2
*                         ADC12_CHANNEL3 : select channel 3
* Output             : None.
* Return             : None.
*******************************************************************************/
void ADC12_ChannelSelect(ADC12_Channels ADC12_Channel)
{
  /* Clear present selected channel */
  ADC12->CSR &= 0xFFCF;

  /* Update the CSR by the value of the selected channel */
  ADC12->CSR |= ADC12_Channel;
}

/*******************************************************************************
* Function Name      : ADC12_FlagStatus
* Description        : This function is used to test the status of the
*                      specified flag.
* Input              : - flag: specifies the flag to get the status. It can be:
*                         ADC12_DA0: Data Available on Channel 0
*                         ADC12_DA1: Data Available on Channel 1
*                         ADC12_DA2: Data Available on Channel 2
*                         ADC12_DA3: Data Available on Channel 3
*                         ADC12_OR : Overrun
* Output             : None.
* Return             : The status of the specified flag. Its value can be:
*                      SET: if the flag is set.
*                      RESET: if the flag is cleared.
*******************************************************************************/
FlagStatus ADC12_FlagStatus (ADC12_Flags flag)
{
  /* Test on the flag status and return set or RESET */
 if(ADC12->CSR & flag)
  {
    return(SET);
  }
  else
  {
    return(RESET); 	
  }  
}

/*******************************************************************************
* Function Name      : ADC12_ConversionValue
* Description        : This functions gets the conversion result from the 
*                      data register of the specified channel. It returns the
*                      value of the corresponding data register.
* Input              : - ADC12_Channel: specifies the channel to get its result
                         of conversion. It can be:
*                         ADC12_CHANNEL0 : read the DATA0 register.
*                         ADC12_CHANNEL1 : read the DATA1 register.
*                         ADC12_CHANNEL2 : read the DATA2 register.
*                         ADC12_CHANNEL3 : read the DATA3 register.
* Output             : None.
* Return             : The result of conversion of the specified channel.
*******************************************************************************/
u16 ADC12_ConversionValue(ADC12_Channels ADC12_Channel)
{
  /* Clear the correspondent DA bit */
  ADC12->CSR &= ~(1 << (ADC12_Channel >> 4));

  /* Only the 12 MSB of the DATAn Register are taken */
  return *(u16 *)(ADC12_BASE + (ADC12_Channel >> 1)) >> 4;
}


/*******************************************************************************
* Function Name      : ADC12_ITConfig
* Description        : This routine is used to enable or disable the interrupt
*                      routine.
* Input              : - NewState: specifies whether the interrupt will 
*                        be enabled or disabled.
*                         ENABLE: enable the interrupt routine.
*                         DISABLE: disable the interrupt routine.
* Output             : None.
* Return             : None.
*******************************************************************************/
void ADC12_ITConfig(FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    /* If the single mode is selected */
    if (ADC12->CSR & 0x0040)
    {
      /* Set the corresponding interrupt bit according to the selected channel*/
      switch (ADC12->CSR & 0x30)
      {
        case 0x00 :
          ADC12->CSR |= ADC12_IT0_Mask;
          break;
        case 0x10 :
          ADC12->CSR |= ADC12_IT1_Mask;
          break;
        case 0x20 :
          ADC12->CSR |= ADC12_IT2_Mask;
          break;
        case 0x30 :
          ADC12->CSR |= ADC12_IT3_Mask;
          break;
      }
    }

    else
    {
      /* Set all interrupt bits in case of round robin mode is selected */
      ADC12->CSR |= ADC12_IT_Mask;
    }
  }
  else
  {
    /* Clear all interrupt bits */
    ADC12->CSR &= ~ADC12_IT_Mask;
  }
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/

