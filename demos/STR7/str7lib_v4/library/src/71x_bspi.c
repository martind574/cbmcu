/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_bspi.c
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides all the BSPI firmware functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "71x_bspi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : BSPI_BSPI0Conf
* Description    : Configure BSPI0 to be available on GPIO0.0 to GPIO0.3 pins.
* Input          : - NewState: specifies the status of the BSPI0.
*                    it can be ENABLE or DISABLE.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_BSPI0Conf(FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    PCU->BOOTCR |= 0x04;
  }
  else
  {
    PCU->BOOTCR &= ~0x04;
  }
}

/*******************************************************************************
* Function Name  : BSPI_Init
* Description    : Initializes the BSPI peripheral control and registers to 
*                  their default reset values.
* Input          : - BSPIx: selects the BSPI peripheral to be initialized where
*                    x can be 0 or 1.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_Init(BSPI_TypeDef *BSPIx)
{
  BSPIx->CSR1 = 0x00;
  BSPIx->CSR2 = 0x41;
  BSPIx->CLK  = 0x06;
}

/*******************************************************************************
* Function Name  : BSPI_Enable
* Description    : Enables/disables the specified BSPI peripheral.
* Input          : - BSPIx: selects the BSPI peripheral to be enabled or
*                    disabled where x can be 0 or 1. 
*                  - NewState: specifies the status of the BSPI
*                    it can be ENABLE or DISABLE.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_Enable(BSPI_TypeDef *BSPIx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    BSPIx->CSR1 |= BSPI_BSPE_Mask;
  }
  else
  {
    BSPIx->CSR1 &= ~BSPI_BSPE_Mask;
  }
}

/*******************************************************************************
* Function Name  : BSPI_MasterEnable
* Description    : Configures the BSPI as a Master or a Slave.
* Input          : - BSPIx: selects the BSPI peripheral to be configured as 
*                    master or slave where x can be 0 or 1.
*                  - NewState: specifies whether configuring BSPI as master or
*                    slave.
*                    ENABLE the specified BSPI will be configured as a master.
*                    DISABLE  the specified BSPI will be configured as a slave.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_MasterEnable(BSPI_TypeDef *BSPIx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    BSPIx->CSR1 |= BSPI_MSTR_Mask;
  }
  else
  {
    BSPIx->CSR1 &= ~BSPI_MSTR_Mask;
  }
}

/*******************************************************************************
* Function Name  : BSPI_TrItSrc
* Description    : Configures the transmit interrupt source.
* Input          : - BSPIx: selects the BSPI peripheral to be configured where
*                    x can be 0 or 1.
*                  - TrItSrc: specifies the transmit interrupt source.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_TrItSrc(BSPI_TypeDef *BSPIx, BSPI_IT_TR TrItSrc)
{
  /* Clear all TIE bits */
  BSPIx->CSR2 &= ~0xC000;
  
  switch (TrItSrc)
  {
   /* Transmit FIFO Empty interrupt selected */	
   case BSPI_TR_FE:
      BSPIx->CSR2 |= 0x4000;
      break;
      
   /* Transmit FIFO Underflow interrupt selected */
   case BSPI_TR_UFL:
     BSPIx->CSR2 |= 0x8000;
     break;
     
   /* Transmit FIFO Full interrupt selected */  
   case BSPI_TR_FF:
     BSPIx->CSR2 |= 0xC000;
     break;
     
   default: break;
  }	
}

/*******************************************************************************
* Function Name  : BSPI_RcItSrc
* Description    : Configures the receive interrupt source.
* Input          : - BSPIx: selects the BSPI peripheral to be configured where
*                    x can be 0 or 1.
*                  - RcItSrc: specifies the source for the receive interrupt.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_RcItSrc(BSPI_TypeDef *BSPIx, BSPI_IT_RC RcItSrc)
{
  /* Clear all RIE bits */	
  BSPIx->CSR1 &= ~0x000C;
  
  switch (RcItSrc)
  {
    /* Receive FIFO Not Empty interrupt selected */
    case BSPI_RC_FNE:
      BSPIx->CSR1 |= 0x0004;
      break;
      
    /* Receive FIFO Full interrupt selected */  
    case BSPI_RC_FF:
      BSPIx->CSR1 |= 0x000C;
      break;
      
    default: break;  
  }
}

/*******************************************************************************
* Function Name  : BSPI_TrFifoDepth
* Description    : Configures the depth of the BSPI transmission FIFO.
* Input          : - BSPIx: selects the BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - TDepth: specifies the depth of the transmit FIFO.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_TrFifoDepth(BSPI_TypeDef *BSPIx, u8 TDepth)
{
  if ((TDepth > 0) && (TDepth < 11))
  {
    TDepth--;
    
    /* Clear all Depth field bits */
    BSPIx->CSR2 &= ~0x3C00;
    
    /* Update the Depth field with new value */
    BSPIx->CSR2 |= TDepth * 0x400;
  }
  else
  {
    BSPIx->CSR2 &= ~0x3C00;
  }
}

/*******************************************************************************
* Function Name  : BSPI_RcFifoDepth
* Description    : Configures the depth of the BSPI reception FIFO.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - RDepth: specifies the depth of the receive FIFO.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_RcFifoDepth(BSPI_TypeDef *BSPIx, u8 RDepth)
{
  if ((RDepth > 0) && (RDepth < 11))
  {
    RDepth--;
    
    /* Clear all Depth field bits */
    BSPIx->CSR1 &= ~0xF000;
    
    /* Update the Depth field with new value */
    BSPIx->CSR1 |= RDepth * 0x1000;
  }
  else
  {
    BSPIx->CSR1 &= ~0xF000;
  }
}

/*******************************************************************************
* Function Name  : BSPI_8bLEn
* Description    : Sets the word length of the receive FIFO and transmit data
*                  registers to either 8 or 16 bits.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - NewState: specifies if the word length is 8 or 16 bits.
*                     ENABLE: enable setting the word length to 8 bits.
*                     DISABLE: disable setting the word length to 8 bits: the
*                     wordlength will be set to 16 bits.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_8bLEn(BSPI_TypeDef *BSPIx, FunctionalState NewState)
{
  /* Wordlength = 16 bits */
  if (NewState == DISABLE)
  {
    BSPIx->CSR1 |= 0x0400;
  }
  /* Wordlength = 8 bits */
  else
  {
    BSPIx->CSR1 &= ~0x0C00;
  }
}

/*******************************************************************************
* Function Name  : BSPI_ClkFEdge
* Description    : Enables capturing the first data sample on the first edge of
*                  SCK or on the second edge.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - NewState: specifies whether capturing the first data sample
*                    on the first edge of SCK is enabled or disabled.
*                     ENABLE: enable capturing the first data sample on the
*                     first edge of SCK.
*                     DISABLE: enable capturing the first data sample on the
*                     second edge of SCK.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_ClkFEdge(BSPI_TypeDef *BSPIx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    BSPIx->CSR1 &= ~BSPI_CPHA_Mask;
  }
  else
  {
    BSPIx->CSR1 |= BSPI_CPHA_Mask;
  }
}

/*******************************************************************************
* Function Name  : BSPI_ClkActiveHigh
* Description    : Configures the clock to be active high or low.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - NewState: specifies whether the clock is active high or low.
*                     ENABLE: Configures the clock to be active High.
*                     DISABLE: Configures the clock to be active Low.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_ClkActiveHigh(BSPI_TypeDef *BSPIx, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    BSPIx->CSR1 &= ~BSPI_CPOL_Mask;
  }
  else
  { 
    BSPIx->CSR1 |= BSPI_CPOL_Mask;
  }
}

/*******************************************************************************
* Function Name  : BSPI_FifoDisable
* Description    : Disables the FIFO of the specified BSPI.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_FifoDisable(BSPI_TypeDef *BSPIx)
{
  BSPIx->CSR2 |= BSPI_DFIFO_Mask;
}

/*******************************************************************************
* Function Name  : BSPI_ClockDividerConfig
* Description    : Configures BSPI clock divider.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - Div: holds the value of the clock divider.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_ClockDividerConfig(BSPI_TypeDef *BSPIx, u8 Div)
{
  BSPIx->CLK = Div;
}

/*******************************************************************************
* Function Name  : BSPI_FlagStatus
* Description    : Checks whether the specified BSPI Flag is set or not.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - flag: specifies the flag to see the status.
* Output         : None.
* Return         : The status of the specified flag.
*                   SET: if the tested flag is set.
*                   RESET: if the corresponding flag is reset.
*******************************************************************************/
FlagStatus BSPI_FlagStatus(BSPI_TypeDef *BSPIx, BSPI_Flags flag)
{
  if (BSPIx->CSR2 & flag)
  {
    return SET;	
  }
  else
  {
    return RESET;	
  }
}

/*******************************************************************************
* Function Name  : BSPI_WordSend
* Description    : Transmit a single Word.
* Input          : - BSPIx: selects BSPI peripheral to be configured 
*                    where x can be 0 or 1.
*                  - Data: the word which will be transmitted.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_WordSend(BSPI_TypeDef *BSPIx, u16 Data)
{
  /* If the word length has been configured as 8-bits word length */	
  if ((BSPIx->CSR1 & 0x0400) == 0)
  {
    Data <<= 8;
  }
  
  BSPIx->TXR = Data;
}

/*******************************************************************************
* Function Name  : BSPI_ByteBufferSend
* Description    : Transmits 8 bit format data from a buffer.
* Input          : - BSPIx: selects BSPI peripheral to be used where
*                    x can be 0 or 1.
*                  - PtrToBuffer: is an 'u8' pointer to the first byte of the
*                    buffer to be transmitted.
*                  - NbOfWords: the number of words saved in the buffer 
*                    to be sent.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_ByteBufferSend(BSPI_TypeDef *BSPIx, u8 *PtrToBuffer, u8 NbOfWords)
{
  vu8 SendWord = 0;
  
  while (SendWord < NbOfWords)
  {
    BSPI_WordSend(BSPIx, *(PtrToBuffer + SendWord));
    SendWord++;
  }
}

/*******************************************************************************
* Function Name  : BSPI_WordBufferSend
* Description    : Transmits 16 bits data format from a buffer.
* Input          : - BSPIx: selects BSPI peripheral to be used where
*                    x can be 0 or 1.
*                  - PtrToBuffer: is an 'u16' pointer to the first word of the
*                    buffer to be transmitted.
*                  - NbOfWords: indicates the number of words saved in
*                    the buffer to be sent.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_WordBufferSend(BSPI_TypeDef *BSPIx, u16 *PtrToBuffer, u8 NbOfWords)
{
  vu8 SendWord = 0;
  
  while (SendWord < NbOfWords)
  {
    BSPI_WordSend(BSPIx, *(PtrToBuffer + SendWord));
    SendWord++;
  }
}

/*******************************************************************************
* Function Name  : BSPI_WordReceive
* Description    : Returns the recent received word.
* Input          : - BSPIx: selects BSPI peripheral to be used where
*                    x can be 0 or 1.
* Output         : None.
* Return         : The value of the received word.
*******************************************************************************/
u16 BSPI_WordReceive(BSPI_TypeDef *BSPIx)
{
  /* If the word length has been configured as 8-bits word length */
  if((BSPIx->CSR1 & 0x0400) == 0)
  {
    return BSPIx->RXR >> 8 ;
  }
  else
  {
    return BSPIx->RXR;	
  }
}

/*******************************************************************************
* Function Name  : BSPI_ByteBufferReceive
* Description    : Receives number of data words and stores them in user defined
*                  area.
* Input          : - BSPIx: selects BSPI peripheral to be used where
*                    x can be 0 or 1.
*                  - PtrToBuffer: is an 'u8' pointer to the first word of the
*                    defined area to save the received buffer.
*                  - NbOfWords: indicates the number of bytes to be received
*                    in the buffer.
* Output         : The received data.
* Return         : None.
*******************************************************************************/
void BSPI_ByteBufferReceive(BSPI_TypeDef *BSPIx, u8 *PtrToBuffer, u8 NbOfWords)
{
  vu8 ReceiveWord = 0;
  
  while (ReceiveWord < NbOfWords)
  {
    *(PtrToBuffer + ReceiveWord) = BSPI_WordReceive(BSPIx);
    ReceiveWord++;
  }
}

/*******************************************************************************
* Function Name  : BSPI_WordBufferReceive
* Description    : Receives number of 16-bit data words and stores them in user 
*                  defined area.
* Input          : - BSPIx: selects BSPI peripheral to be used where
*                    x can be 0 or 1.
*                  - PtrToBuffer: is an 'u16' pointer to the first word of the
*                    defined area to save the received buffer.
*                  - NbOfWords: indicates the number of words to be received
*                    in the buffer.
* Output         : The received data.
* Return         : None.
*******************************************************************************/
void BSPI_WordBufferReceive(BSPI_TypeDef *BSPIx, u16 *PtrToBuffer, u8 NbOfWords)
{
  vu8 ReceiveWord = 0;
  
  while (ReceiveWord < NbOfWords)
  {
    *(PtrToBuffer + ReceiveWord) = BSPI_WordReceive(BSPIx);
    ReceiveWord++;
  }
}

/*******************************************************************************
* Function Name  : BSPI_ErrItSrc
* Description    : Enables or disables the specified error interrupt.
* Input          : - BSPIx: selects BSPI peripheral to be used where
*                    x can be 0 or 1.
*                  - BSPI_IE: specifies the BSPI error interrupt.
*                  - NewState: specified whether the BSPI interrupt is enabled 
*                    or disabled.
*                     ENABLE  to enable interrupt.
*                     DISABLE to disable interrupt.
* Output         : None.
* Return         : None.
*******************************************************************************/
void BSPI_ErrItSrc(BSPI_TypeDef *BSPIx, BSPI_IT_ERR BSPI_IE,
                   FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    BSPIx->CSR1 |= BSPI_IE;
  }
  else
  {
    BSPIx->CSR1 &= ~BSPI_IE;
  }
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
