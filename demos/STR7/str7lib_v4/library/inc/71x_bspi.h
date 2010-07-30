/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_bspi.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file contains all the functions prototypes for the
*                      BSPI firmware library.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_BSPI_H
#define __71x_BSPI_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Error interruption sources */
typedef enum {
  BSPI_BEIE    = 0x80,  /* Bus Error Interrupt Enable     */
  BSPI_REIE    = 0x10,  /* Receive Error Interrupt Enable */
  BSPI_ALL_ERR = 0x90   /* All Error Interrupt            */
} BSPI_IT_ERR;

/* Flags */
typedef enum {
  BSPI_BERR = 0x004,  /* Bus Error flag                 */
  BSPI_RFNE = 0x008,  /* Receive FIFO Not Empty flag    */
  BSPI_RFF  = 0x010,  /* Receive FIFO Full flag         */
  BSPI_ROFL = 0x020,  /* Receiver Overflow flag         */
  BSPI_TFE  = 0x040,  /* Transmit FIFO Empty flag       */
  BSPI_TUFL = 0x080,  /* Transmit Underflow flag        */
  BSPI_TFF  = 0x100,  /* Transmit FIFO Full flag        */
  BSPI_TFNE = 0x200   /* Transmit FIFO Not Empty flag   */
} BSPI_Flags;

/* Transmit interruption sources */
typedef enum {
  BSPI_TR_FE,   /* Interrupt on Transmit FIFO Empty */
  BSPI_TR_UFL,  /* Interrupt on Transmit underflow  */
  BSPI_TR_FF,   /* Interrupt on Transmit FIFO Full  */
  BSPI_TR_DIS   /* All transmit Interrupts Disabled */
} BSPI_IT_TR;

/* Receive interruption sources */
typedef enum {
  BSPI_RC_FNE,  /* Interrupt on Receive FIFO Not Empty */
  BSPI_RC_FF,   /* Interrupt on Receive FIFO Full      */
  BSPI_RC_DIS   /* All Receive Interrupt Disabled      */
} BSPI_IT_RC;

/* Exported constants --------------------------------------------------------*/
#define BSPI_BSPE_Mask     0x01   /* BSPI System Enable (BSPIx_CSR1 bit 0)    */
#define BSPI_DFIFO_Mask    0x01   /* Disable FIFO (BSPIx_CSR2 bit 0)          */
#define BSPI_CPHA_Mask     0x200  /* Clock Phase Select (BSPIx_CR1 bit 9)     */
#define BSPI_CPOL_Mask     0x100  /* Clock Polarity Select (BSPIx_CR1 bit 8)  */
#define BSPI_MSTR_Mask     0x02   /* Master/Slave Select (BSPIx_CR1 bit 1)    */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void BSPI_BSPI0Conf(FunctionalState NewState);
void BSPI_Init(BSPI_TypeDef *BSPIx);
void BSPI_Enable(BSPI_TypeDef *BSPIx, FunctionalState NewState);
void BSPI_MasterEnable(BSPI_TypeDef *BSPIx, FunctionalState NewState);
void BSPI_TrItSrc(BSPI_TypeDef *BSPIx, BSPI_IT_TR TrItSrc);
void BSPI_RcItSrc(BSPI_TypeDef *BSPIx, BSPI_IT_RC RcItSrc);
void BSPI_TrFifoDepth(BSPI_TypeDef *BSPIx, u8 TDepth);
void BSPI_RcFifoDepth(BSPI_TypeDef *BSPIx, u8 RDepth);
void BSPI_8bLEn(BSPI_TypeDef *BSPIx, FunctionalState NewState);
void BSPI_ClkFEdge(BSPI_TypeDef *BSPIx, FunctionalState NewState);
void BSPI_ClkActiveHigh(BSPI_TypeDef *BSPIx, FunctionalState NewState);
void BSPI_FifoDisable(BSPI_TypeDef *BSPIx);
void BSPI_ClockDividerConfig(BSPI_TypeDef *BSPIx, u8 Div);
FlagStatus BSPI_FlagStatus(BSPI_TypeDef *BSPIx, BSPI_Flags flag);
void BSPI_WordSend(BSPI_TypeDef *BSPIx, u16 Data);
void BSPI_ByteBufferSend(BSPI_TypeDef *BSPIx, u8 *PtrToBuffer, u8 NbOfWords);
void BSPI_WordBufferSend(BSPI_TypeDef *BSPIx, u16 *PtrToBuffer, u8 NbOfWords);
u16 BSPI_WordReceive(BSPI_TypeDef *BSPIx);
void BSPI_ByteBufferReceive(BSPI_TypeDef *BSPIx, u8 *PtrToBuffer, u8 NbOfWords);
void BSPI_WordBufferReceive(BSPI_TypeDef *BSPIx, u16 *PtrToBuffer, u8 NbOfWords);
void BSPI_ErrItSrc(BSPI_TypeDef *BSPIx, BSPI_IT_ERR BSPI_IE,
                   FunctionalState NewState);

#endif /* __71x_BSPI_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
