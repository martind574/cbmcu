/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_i2c.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides Code sources I2C functions
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_i2c.h"
#include "71x_rccu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : I2C_Init
* Description    : Initializes I2C peripheral control and registers to their
*                  default reset values.
* Input          : - I2Cx: specifies the I2C to be initialized, it can be:
*                     I2C0, I2C1
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_Init (I2C_TypeDef *I2Cx)
{
  /* Initialize all the register of the specified I2C passed as parameter */
  I2Cx->CR = 0x0;
  I2Cx->CCR = 0x0;
  I2Cx->ECCR = 0x0;
  I2Cx->OAR1 = 0x0;
  I2Cx->OAR2 = 0x0;
  (void)I2Cx->SR1;
  (void)I2Cx->SR2;
  I2Cx->DR = 0x0;
}

/*******************************************************************************
* Function Name  : I2C_OnOffConfig
* Description    : Enables or disables the I2C peripheral.
* Input          : - I2Cx: specifies the I2C to be enabled or disabled.
*                    It can be:
*                     I2C0, I2C1
*                  - NewState: specifies the new status to set. It can be:
*                     ENABLE: enables the I2C peripheral.
*                     DISABLE: disables the I2C peripheral.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_OnOffConfig (I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    /* Enable the I2C selected by setting twice the PE bit on the CR register */
    I2Cx->CR |= I2C_PESET_Mask;
    I2Cx->CR |= I2C_PESET_Mask;
  }
  else
  {
    /* Disable the I2C selected */
    I2Cx->CR &= ~I2C_PESET_Mask;
  }
}

/*******************************************************************************
* Function Name  : I2C_GeneralCallConfig
* Description    : Enables or disables I2C general call option.
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
*                  - NewState: specifies the new status to set. It can be:
*                     ENABLE: enables the I2C general call option.
*                     DISABLE: disables the I2C general call option.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_GeneralCallConfig (I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    I2Cx->CR |= I2C_ENGC_Mask;
  }
  else
  {
    I2Cx->CR &= ~I2C_ENGC_Mask;
  }
}

/*******************************************************************************
* Function Name  : I2C_STARTGenerate
* Description    : Generates I2C communication START condition.
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
*                  - NewState: specifies the new status to set. It can be:
*                     ENABLE: enables the I2C start generation.
*                     DISABLE: disables the I2C start generation.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_STARTGenerate (I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    I2Cx->CR |= I2C_START_Mask;
  }
  else
  {
    I2Cx->CR &= ~I2C_START_Mask;
  }
}

/*******************************************************************************
* Function Name  : I2C_STOPGenerate
* Description    : Generates I2C communication STOP condition.
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
*                  - NewState: specifies the new status to set. It can be:
*                     ENABLE: enables the I2C stop generation.
*                     DISABLE: disables the I2C stop generation.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_STOPGenerate (I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    I2Cx->CR |= I2C_STOP_Mask;
  }
  else
  {
    I2Cx->CR &= ~I2C_STOP_Mask;
  }
}

/*******************************************************************************
* Function Name  : I2C_AcknowledgeConfig
* Description    : Enables or disables I2C acknowledge feature.
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
*                  - NewState: specifies the new status to set. It can be:
*                     ENABLE: enables the I2C acknowledge feature.
*                     DISABLE: disables the I2C acknowledge feature.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_AcknowledgeConfig (I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    I2Cx->CR |= I2C_ACK_Mask;
  }
  else
  {
    I2Cx->CR &= ~I2C_ACK_Mask;
  }
}

/*******************************************************************************
* Function Name  : I2C_ITConfig
* Description    : Enables or disables I2C interrupt feature.
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
*                  - NewState: specifies the new status to set. It can be:
*                     ENABLE: enables the I2C interrupt feature.
*                     DISABLE: disables the I2C interrupt feature.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_ITConfig (I2C_TypeDef *I2Cx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    I2Cx->CR |= I2C_ITE_Mask;
  }
  else
  {
    I2Cx->CR &= ~I2C_ITE_Mask;
  }
}

/*******************************************************************************
* Function Name  : I2C_RegisterRead
* Description    : Reads any I2C register and returns its value.
* Input          : - I2Cx: specifies the I2C to read its register, it can be:
*                     I2C0, I2C1
*                  - reg: specifies the register to be read, it can be:
*                     I2C_CR, I2C_SR1, I2C_SR2, I2C_CCR, I2C_OAR1, I2C_OAR2,
*                     I2C_DR, I2C_ECCR
* Output         : None.
* Return         : the value of the register passed as parameter(u8)
*******************************************************************************/
u8 I2C_RegisterRead (I2C_TypeDef *I2Cx, I2C_Registers reg)
{
  return (*(u8 *)(*((u32 *)&I2Cx) + reg));
}

/*******************************************************************************
* Function Name  : I2C_FlagStatus
* Description    : Checks whether any I2C Flag is set or not.
* Input          : - I2Cx: specifies the I2C to read its flags, it can be:
*                     I2C0, I2C1
*                  - Flag: the flag to be read.
* Output         : None.
* Return         : The specified flag status, it can be:
*                   SET: if the tested flag is set.
*                   RESET: if the tested flag is reset.
*******************************************************************************/
FlagStatus I2C_FlagStatus (I2C_TypeDef *I2Cx, u32 Flag)
{
  u16 Flag1 = 0, Flag2 = 0, Flag3 = 0, Tmp = 0;

  Flag1 = I2Cx->SR1;
  Flag2 = I2Cx->SR2;
  Flag2 = Flag2<<8;
  Flag3 = I2Cx->CR;

  /* Get all the I2C flags in a unique register*/
  Tmp = (((Flag1 | (Flag2)) & I2C_Event_Mask) | (Flag3<<14)); 
  
  /* Check the status of the specified I2C flag */
  if((Tmp & Flag) != RESET)
  {
    /* Return SET if I2C_FLAG is set */
    return SET;
  }
  else
  {
    /* Return RESET if I2C_FLAG is reset */
    return RESET;
  }
}
/*******************************************************************************
* Function Name  : I2C_GetLastEvent                                  
* Description    : Gets the last I2Cx event that has occurred.                  
* Input          : - I2Cx: specifies the I2C to read its flags, it can be:
*                     I2C0, I2C1.  
* Output         : None.                          
* Return         : The Last happened Event.                           
*******************************************************************************/
u16 I2C_GetLastEvent(I2C_TypeDef *I2Cx)
{
  u16 Flag1 = 0, Flag2 = 0, LastEvent = 0;

  Flag1 = I2Cx->SR1;
  Flag2 = I2Cx->SR2;
  Flag2 = Flag2<<8;
  /* Get the last event value from I2C status register */
  LastEvent = (((Flag1 | (Flag2)) & I2C_Event_Mask));
  /* Return the last event */
  return LastEvent;
}

/*******************************************************************************
* Function Name  : I2C_CheckEvent                                         
* Description    : Checks whether the Last I2C Event is equal to the one passed 
*                  as parameter.                                              
* Input          : - I2Cx: specifies the I2C to read its flags, it can be:
*                     I2C0, I2C1
                   - I2C_EVENT: specifies the event to be checked. This parameter
*                    can be one of the following values:
*                         - I2C_EVENT_SLAVE_ADDRESS_MATCHED
*                         - I2C_EVENT_SLAVE_BYTE_RECEIVED
*                         - I2C_EVENT_SLAVE_BYTE_TRANSMITTED
*                         - I2C_EVENT_SLAVE_ACK_FAILURE 
*                         - I2C_EVENT_MASTER_MODE_SELECT
*                         - I2C_EVENT_MASTER_MODE_SELECTED
*                         - I2C_EVENT_MASTER_BYTE_RECEIVED
*                         - I2C_EVENT_MASTER_BYTE_TRANSMITTED
*                         - I2C_EVENT_MASTER_MODE_ADDRESS10
*                         - I2C_EVENT_SLAVE_STOP_DETECTED
* Output         : None                                      
* Return         : An FlagStatus enumuration value:
*                         - SET: Last event is equal to the I2C_Event
*                         - RESET: Last event is different from the I2C_Event        
*******************************************************************************/
FlagStatus I2C_CheckEvent(I2C_TypeDef *I2Cx, u16 I2C_EVENT)
{
  u16  LastEvent = I2C_GetLastEvent(I2Cx);

  /* Check whether the last event is equal to I2C_EVENT */
  if (LastEvent == I2C_EVENT)
  {
    /* Return SUCCESS when last event is equal to I2C_EVENT */
    return SET;
  }
  else
  {
    /* Return ERROR when last event is different from I2C_EVENT */
    return RESET;
  }
}

/*******************************************************************************
* Function Name  : I2C_FlagClear
* Description    : Clears the I2C Flag passed as a parameter
* Input          : - I2Cx: specifies the I2C to clear its flags, it can be:
*                     I2C0, I2C1 
*                  - Flag: the flag to be read, it can be:
*                     I2C_ADD10, I2C_EVF, I2C_BERR, I2C_ARLO, I2C_STOPF
*                     I2C_AF, I2C_ENDAD, I2C_SB, I2C_ADSL, I2C_BTF, I2C_TRA
*                     I2C_M_SL, I2C_GCAL
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_FlagClear (I2C_TypeDef *I2Cx, u32 Flag, ...)
{
  u8 Tmp = (u8) * ((u32 *) & Flag + sizeof(Flag));


  /* flags that need a read of the SR2 register to be cleared */
  if (Flag == I2C_ADD10 || Flag == I2C_EVF || Flag == I2C_BERR 
      || Flag == I2C_ARLO || Flag == I2C_STOPF || Flag == I2C_AF
      || Flag == I2C_ENDAD)
  {
    /* Read the SR2 register */
    (void)I2Cx->SR2;
    
    /* Two flags need a second step to be cleared */
    switch (Flag)
    {
      case  I2C_ADD10:
        I2Cx->DR = Tmp;
        break;
        
      case  I2C_ENDAD:
        I2Cx->CR |= I2C_PESET_Mask;
        break;
    }
  }
  /* flags that need a read of the SR1 register to be cleared */
  else if (Flag == I2C_SB || Flag == I2C_ADSL || Flag == I2C_BTF
            || Flag == I2C_TRA)
  {
    /* Read the SR1 register */
    (void)I2Cx->SR1;
    if (Flag == I2C_SB)
    {
      I2Cx->DR = Tmp;
    }
    else if (Flag == I2C_BTF || Flag == I2C_TRA)
    {
      (void)I2Cx->DR;
    }
  }
  /*flags that need the PE bit to be cleared */
  else if (Flag == I2C_M_SL || Flag == I2C_GCAL)
  {
    I2C_OnOffConfig (I2Cx, DISABLE);
    I2C_OnOffConfig (I2Cx, ENABLE);
  }
}

/*******************************************************************************
* Function Name  : I2C_SpeedConfig
* Description    : Selects I2C clock speed and configures its corresponding mode
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
*                  - Clock: the I2C expected clock in Hertz.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_SpeedConfig (I2C_TypeDef *I2Cx, u32 Clock)
{
  u32 PCLK1 = 0;
  u16 result = 0;
  
  /* Get the FCLK frequency using the RCCU library */
  PCLK1 = RCCU_FrequencyValue (RCCU_PCLK1);
  
  /* Test on speed mode */
  /* Update the CCR and ECCR registers */

  /* If Standard mode is selected */
  if (Clock <= 100000)
  {
    result = ((PCLK1 / Clock) - 7) / 2;
    /* Clear FM/SM bit */
    I2Cx->CCR = result & 0x7f;
  }
 /* If Fast mode is selected */
  else if (Clock <= 400000)
  {
    result = ((PCLK1 / Clock) - 9) / 3;
    
    /* set FM/SM bit */
    I2Cx->CCR = result | 0x80;
  }
  I2Cx->ECCR = result >> 7;
}

/*******************************************************************************
* Function Name  : I2C_AddressConfig
* Description    : Defines the I2C bus address of the interface.
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
*                  - Address: an u16 parameter indicating the interface
*                    address.
*                  - Mode: specifies the addressing mode, it can be:
*                     I2C_Mode7, I2C_Mode10
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_AddressConfig (I2C_TypeDef *I2Cx, u16 Address, I2C_Addressing Mode)
{
  /* Update OAR1 bit[7:1] by the lowest byte of address */
  I2Cx->OAR1 = (u8)Address;

  if (Mode == I2C_Mode10)
  {
    /* Update Add8 and add9 bits in OAR2 */
    I2Cx->OAR2 |= (Address & 0x0300) >> 7;
  }
}

/*******************************************************************************
* Function Name  : I2C_FCLKConfig
* Description    : Configures I2C frequency bits according to PCLK1 frequency.
*                  The selected I2C must be disabled.
* Input          : - I2Cx: specifies the I2C to be configured, it can be:
*                     I2C0, I2C1
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_FCLKConfig (I2C_TypeDef *I2Cx)
{
  u32 PCLK1 = 0;
  
  /* Get the PCLK1 frequency using the RCCU library */
  PCLK1 = RCCU_FrequencyValue (RCCU_PCLK1);
  
  /* Test the value of the PCLK1 and affect FR0, FR1 and FR2 of the OAR2
   register*/
  if (PCLK1 > 5000000)
  {
    if (PCLK1 < 10000000)
    {
      I2Cx->OAR2 |= 0x00;
    }
    else if (PCLK1 < 16670000)
    {
      I2Cx->OAR2 |= 0x20;
    }
    else if (PCLK1 < 26670000)
    {
      I2Cx->OAR2 |= 0x40;
    }
    else if (PCLK1 < 40000000)
    {
      I2Cx->OAR2 |= 0x60;
    }
    else if (PCLK1 < 53330000)
    {
      I2Cx->OAR2 |= 0x80;
    }
    else if (PCLK1 < 66000000)
    {
      I2Cx->OAR2 |= 0xA0;
    }
    else if (PCLK1 < 80000000)
    {
      I2Cx->OAR2 |= 0xC0;
    }
    else if (PCLK1 < 100000000)
    {
      I2Cx->OAR2 |= 0xE0;
    }
  }
}

/*******************************************************************************
* Function Name  : I2C_AddressSend
* Description    : Sends the slave address with which the next communication
*                  will be performed.
* Input          : - I2Cx: specifies the I2C which will send the slave address, 
*                    it can be:
*                     I2C0, I2C1
*                  - Address: indicates the slave address which will be 
*                    transmitted
*                  - Mode: specifies the addressing mode, it can be:
*                     I2C_Mode10, I2C_Mode7
*                  - Direction: specifies the communication direction,
*                    it can be:
*                     I2C_RX, I2C_TX
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_AddressSend (I2C_TypeDef *I2Cx, u16 Address, I2C_Addressing Mode,
                      I2C_Direction Direction)
{

  /* If the 10 bit addressing mode is selected */	
  if (Mode == I2C_Mode10)
  {
    /* Update the DR register by generated header */
    I2Cx->DR = ((Address >> 7) | 0xF0) & 0xFE;
    
    /* Wait till I2C_ADD10 flag is set */
    while ((I2Cx->SR1 & 0x40) == 0)
    {
      /* Wait*/
    }
    
    /* clear I2C_ADD10 flag */
    (void)I2Cx->SR2;
    
    I2Cx->DR = (u8)Address;
    
    /* Test on the direction to define the read/write bit */
    if (Direction == I2C_RX)
    {
      /* Wait till I2C_ENDAD flag is set */
      while ((I2Cx->SR2 & 0x20) == 0)
      {
        /* Wait*/
      }
      
      I2Cx->CR |= 0x20;
      
      /* Repeated START Generate */
      I2C_STARTGenerate (I2Cx, ENABLE);
      
      /* Test on SB flag status */
      while ((I2Cx->SR1 & 0x01) == 0)
      {
      }
      I2Cx->DR = ((Address >> 7) | 0xF1);
    }
  }
  /* If the 7 bit addressing mode is selected */
  else
  {
    if (Direction == I2C_RX)
    {
      Address |= 0x01;
    }
    else
    {
      Address &= ~0x01;
    }
    I2Cx->DR = (u8)Address;
  }
}

/*******************************************************************************
* Function Name  : I2C_ByteSend
* Description    : Transmits a single byte.
* Input          : - I2Cx: specifies the I2C which will send the single byte, 
*                    it can be:
*                     I2C0, I2C1
*                  - Data: the byte to be transmitted.
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_ByteSend (I2C_TypeDef *I2Cx, u8 Data)
{
  /* Write in the DR register the byte to be sent */
  I2Cx->DR = Data;
}

/*******************************************************************************
* Function Name  : I2C_TransmissionStatus
* Description    : Reports the current transmission status.
* Input          : - I2Cx: specifies the I2C whose transmission status will be  
*                    tested,it can be:
*                     I2C0, I2C1
* Output         : None.
* Return         : The transmission status, it can be:
*                   I2C_TX_NO, I2C_TX_SB, I2C_TX_AF, I2C_TX_ARLO, I2C_TX_BERR,
*                   I2C_TX_ADD_OK, I2C_TX_DATA_OK, I2C_TX_ONGOING
*******************************************************************************/
I2C_Tx_Status I2C_TransmissionStatus (I2C_TypeDef *I2Cx)
{
  u8 SR1value = 0;
  u8 SR2value = 0;
  I2C_Tx_Status NewState = I2C_TX_NO;

  SR1value = I2Cx->SR1;
  SR2value = I2Cx->SR2;
  if ((I2Cx->SR1 & 0x10) == 0)
  {
    NewState = I2C_TX_NO;
  }
  /* If I2C_SB bit is set */
  else if (I2Cx->SR1 & 0x01)
  {
     NewState = I2C_TX_SB;
  }
  /* If I2C_ACK  and I2C_AF are both set */
  else if ((SR2value & 0x10) && (I2Cx->CR & 0x04))
  {
    NewState = I2C_TX_AF;
  }
  /* If I2C_ARLO is set in multimaster mode */
  else if (SR2value & 0x04)
  {
    NewState = I2C_TX_ARLO;
  }
  /* If I2C_BERR bit is set */
  else if (SR2value & 0x02)
  {
    NewState = I2C_TX_BERR;
  }
  /* If I2C_EVF and I2C_ENDAD are both set */
  else if ((SR1value & 0x80) && (I2Cx->SR2 & 0x20))
  {
    NewState = I2C_TX_ADD_OK;
  }
  /* If I2C_TRA and I2C_BTF are both set */  
  else if ((I2Cx->SR1 & 0x20) && (I2Cx->SR1 & 0x08))
  {
    NewState = I2C_TX_DATA_OK;
  }
  else
  {
    NewState = I2C_TX_ONGOING;
  }

  return NewState;
}

/*******************************************************************************
* Function Name  : I2C_ByteReceive
* Description    : Returns the received byte.
* Input          : - I2Cx: specifies the I2C peripheral to get a received data.  
*                    It can be:
*                     I2C0, I2C1
* Output         : None.
* Return         : The value of the received byte
*******************************************************************************/
u8 I2C_ByteReceive (I2C_TypeDef *I2Cx)
{
  
  while ((I2Cx->SR1 & 0x08) == 0)
  {
    /* Wait till I2C_BTF bit is set */
  }
  return I2Cx->DR;
}

/*******************************************************************************
* Function Name  : I2C_ReceptionStatus
* Description    : Reports the current reception status.
* Input          : - I2Cx: specifies the I2C whose reception status will be  
*                    tested,it can be:
*                     I2C0, I2C1
* Output         : None.
* Return         : The current receprtion status, it can be:
*                   I2C_RX_NO, I2C_RX_SB, I2C_RX_AF, I2C_RX_ARLO, I2C_RX_BERR,
*                   I2C_RX_ADD_OK, I2C_RX_DATA_OK, I2C_RX_ONGOING
*******************************************************************************/
I2C_Rx_Status I2C_ReceptionStatus (I2C_TypeDef *I2Cx)
{
  u8 SR1value = 0;
  u8 SR2value = 0;
  I2C_Rx_Status NewState = I2C_RX_NO;
  SR1value = I2Cx->SR1;
  SR2value = I2Cx->SR2;

  if ((I2Cx->SR1 & 0x10) == 0)
  {
    NewState = I2C_RX_NO;
  }
  /* If I2C_SB bit is set */
  else if (I2Cx->SR1 & 0x01)
  {
    NewState = I2C_RX_SB;
  }
  /* If I2C_ACK and I2C_AF are both set */
  else if ((SR2value & 0x10) && (I2Cx->CR & 0x04))
  {
    NewState = I2C_RX_AF;
  }
  /* If I2C_ARLO is set */
  else if (SR2value & 0x04)
  {
    NewState = I2C_RX_ARLO;
  }
  /* If I2C_BERR bit is set */
  else if (SR2value & 0x02)
  {
    NewState = I2C_RX_BERR;
  }
  /* If I2C_EVF is set and I2C_BTF is not set */
  else if ((SR1value & 0x80) && (I2Cx->SR1 & 0x08) == 0)
  {
    NewState = I2C_RX_ADD_OK;
  }
  /* If I2C_TRA is cleared and  I2C_BTF is set */
  else if (((I2Cx->SR1 & 0x20) == 0) && (I2Cx->SR1 & 0x08))
  {
    NewState = I2C_RX_DATA_OK;
  }
  else
  {
    NewState = I2C_RX_ONGOING;
  }
  return NewState;
}

/*******************************************************************************
* Function Name  : I2C_ErrorClear
* Description    : Clears any error flag.
* Input          : - I2Cx: specifies the I2C which error flags will be cleared.  
*                    It can be:
*                     I2C0, I2C1
* Output         : None.
* Return         : None.
*******************************************************************************/
void I2C_ErrorClear (I2C_TypeDef *I2Cx)
{
  /* Clear all error flags by reading the SR2 register */
  (void)I2Cx->SR2;
}

/*******************************************************************************
* Function Name  : I2C_GetStatus
* Description    : Reads the I2C status registers.
* Input          : - I2Cx: specifies the I2C to get its status registers.  
*                    It can be:
*                     I2C0, I2C1
* Output         : None.
* Return         : The I2C status registers value.
*******************************************************************************/
u32 I2C_GetStatus (I2C_TypeDef *I2Cx)
{
  u32 i2c_cr, i2c_sr1, i2c_sr2;

  i2c_cr  = I2Cx->CR;
  i2c_sr1 = I2Cx->SR1;
  i2c_sr2 = I2Cx->SR2;

  return (((i2c_cr) << 14) | (i2c_sr1 | (i2c_sr2 << 8)) & I2C_Event_Mask);
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/

