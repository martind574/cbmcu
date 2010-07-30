/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_i2c.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : This file provides prototypes of I2C functions
*                      and variable used in code sources
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_I2C_H
#define __71x_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "71x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  I2C_CR   = 0x00,
  I2C_SR1  = 0x04,
  I2C_SR2  = 0x08,
  I2C_CCR  = 0x0C,
  I2C_OAR1 = 0x10,
  I2C_OAR2 = 0x14,
  I2C_DR   = 0x18,
  I2C_ECCR = 0x1C
} I2C_Registers;

typedef enum
{
  I2C_Mode10,
  I2C_Mode7
} I2C_Addressing;

typedef enum
{
  I2C_RX,
  I2C_TX
} I2C_Direction;

typedef enum
{
  I2C_TX_NO,
  I2C_TX_SB,
  I2C_TX_AF,
  I2C_TX_ARLO,
  I2C_TX_BERR,
  I2C_TX_ADD_OK,
  I2C_TX_DATA_OK,
  I2C_TX_ONGOING
} I2C_Tx_Status;

typedef enum
{
  I2C_RX_NO,
  I2C_RX_SB,
  I2C_RX_AF,
  I2C_RX_ARLO,
  I2C_RX_BERR,
  I2C_RX_ADD_OK,
  I2C_RX_DATA_OK,
  I2C_RX_ONGOING
} I2C_Rx_Status;

/* Exported constants --------------------------------------------------------*/
#define I2C_SB               0x0001
#define I2C_M_SL             0x0002
#define I2C_ADSL             0x0004
#define I2C_BTF              0x0008
#define I2C_BUSY             0x0010
#define I2C_TRA              0x0020
#define I2C_ADD10            0x0040
#define I2C_EVF              0x0080
#define I2C_GCAL             0x0100
#define I2C_BERR             0x0200
#define I2C_ARLO             0x0400
#define I2C_STOPF            0x0800
#define I2C_AF               0x1000
#define I2C_ENDAD            0x2000
#define I2C_STOP             0x8000
#define I2C_ACK              0x10000
#define I2C_START            0x20000

#define I2C_PESET_Mask       0x20
#define I2C_PERESET          0xDF
#define I2C_ENGC_Mask        0x10
#define I2C_START_Mask       0x08
#define I2C_STOP_Mask        0x02
#define I2C_ACK_Mask         0x04
#define I2C_ITE_Mask         0x01
#define I2C_Event_Mask       0x3FFF

/* I2C Events */
#define  I2C_EVENT_SLAVE_ADDRESS_MATCHED   ( I2C_EVF | I2C_BUSY  | I2C_ADSL)    
#define  I2C_EVENT_SLAVE_BYTE_RECEIVED     ( I2C_EVF | I2C_BUSY  | I2C_BTF )     
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTED  ( I2C_EVF | I2C_BUSY  | I2C_BTF  | I2C_TRA ) 
#define  I2C_EVENT_MASTER_MODE_SELECT      ( I2C_EVF | I2C_BUSY  | I2C_M_SL | I2C_SB )                 
#define  I2C_EVENT_MASTER_MODE_SELECTED    ( I2C_EVF | I2C_BUSY  | I2C_M_SL | I2C_ENDAD )    
#define  I2C_EVENT_MASTER_BYTE_RECEIVED    ( I2C_EVF | I2C_BUSY  | I2C_M_SL | I2C_BTF )                
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED ( I2C_EVF | I2C_BUSY  | I2C_M_SL | I2C_BTF | I2C_TRA )  
#define  I2C_EVENT_MASTER_MODE_ADDRESS10   ( I2C_EVF | I2C_BUSY  | I2C_M_SL | I2C_ADD10 )               
#define  I2C_EVENT_SLAVE_STOP_DETECTED       I2C_STOPF                                  
#define  I2C_EVENT_SLAVE_ACK_FAILURE       ( I2C_EVF | I2C_BUSY | I2C_BTF  | I2C_TRA | I2C_AF)    

#define  I2C_BUS_ERROR_DETECTED       I2C_BERR
#define  I2C_ARBITRATION_LOST         I2C_ARLO
#define  I2C_SLAVE_GENERAL_CALL       (I2C_BUSY | I2C_GCAL)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void I2C_Init (I2C_TypeDef *I2Cx);
void I2C_OnOffConfig (I2C_TypeDef *I2Cx, FunctionalState NewState);
void I2C_GeneralCallConfig (I2C_TypeDef *I2Cx, FunctionalState NewState);
void I2C_STARTGenerate (I2C_TypeDef *I2Cx, FunctionalState NewState);
void I2C_STOPGenerate (I2C_TypeDef *I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig (I2C_TypeDef *I2Cx, FunctionalState NewState);
void I2C_ITConfig (I2C_TypeDef *I2Cx, FunctionalState NewState);
u8 I2C_RegisterRead (I2C_TypeDef *I2Cx, I2C_Registers reg);
FlagStatus I2C_FlagStatus (I2C_TypeDef *I2Cx, u32 Flag);
void I2C_FlagClear (I2C_TypeDef *I2Cx, u32 Flag, ...);
void I2C_SpeedConfig (I2C_TypeDef *I2Cx, u32 Clock);
void I2C_AddressConfig (I2C_TypeDef *I2Cx, u16 Address, I2C_Addressing Mode);
void I2C_FCLKConfig (I2C_TypeDef *I2Cx);
void I2C_AddressSend (I2C_TypeDef *I2Cx, u16 Address, I2C_Addressing Mode,
                      I2C_Direction Direction);
void I2C_ByteSend (I2C_TypeDef *I2Cx, u8 Data);
I2C_Tx_Status I2C_TransmissionStatus (I2C_TypeDef *I2Cx);
u8 I2C_ByteReceive (I2C_TypeDef *I2Cx);
I2C_Rx_Status I2C_ReceptionStatus (I2C_TypeDef *I2Cx);
void I2C_ErrorClear (I2C_TypeDef *I2Cx);
u32 I2C_GetStatus(I2C_TypeDef *I2Cx);
u16 I2C_GetLastEvent(I2C_TypeDef *I2Cx);
FlagStatus I2C_CheckEvent(I2C_TypeDef *I2Cx, u16 I2C_EVENT);

#endif /*__71x_I2C_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
