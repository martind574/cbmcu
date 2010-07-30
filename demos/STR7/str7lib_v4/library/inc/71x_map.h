/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : 71x_map.h
* Author             : MCD Application Team
* Version            : V4.0
* Date               : 10/09/2007
* Description        : Peripherals memory mapping and registers structures
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __71x_MAP_H
#define __71x_MAP_H

#ifndef EXT
  #define EXT extern
#endif /* EXT */

/* Includes ------------------------------------------------------------------*/
#include "71x_conf.h"
#include "71x_type.h"

/* Exported types ------------------------------------------------------------*/
/******************************************************************************/
/*                          Peripheral registers structures                   */
/******************************************************************************/

/*------------------------ Analog to Digital Converter -----------------------*/
typedef struct
{
  vu16 DATA0;
  u16  EMPTY1[3];
  vu16 DATA1;
  u16  EMPTY2[3];
  vu16 DATA2;
  u16  EMPTY3[3];
  vu16 DATA3;
  u16  EMPTY4[3];
  vu16 CSR;
  u16  EMPTY5[7];
  vu16 CPR;
  u16  EMPTY6;
} ADC12_TypeDef;

/*------------------------ APB -----------------------------------------------*/
typedef struct
{
  vu32 CKDIS;
  vu32 SWRES;
} APB_TypeDef;

/*------------------------ Buffered Serial Peripheral Interface --------------*/
typedef struct
{
  vu16 RXR;
  u16  EMPTY1;
  vu16 TXR;
  u16  EMPTY2;
  vu16 CSR1;
  u16  EMPTY3;
  vu16 CSR2;
  u16  EMPTY4;
  vu16 CLK;
  u16  EMPTY5;
} BSPI_TypeDef;

/*------------------------ Controller Area Network ---------------------------*/
typedef struct
{
  vu16 CRR;
  u16  EMPTY1;
  vu16 CMR;
  u16  EMPTY2;
  vu16 M1R;
  u16  EMPTY3;
  vu16 M2R;
  u16  EMPTY4;
  vu16 A1R;
  u16  EMPTY5;
  vu16 A2R;
  u16  EMPTY6;
  vu16 MCR;
  u16  EMPTY7;
  vu16 DA1R;
  u16  EMPTY8;
  vu16 DA2R;
  u16  EMPTY9;
  vu16 DB1R;
  u16  EMPTY10;
  vu16 DB2R;
  u16  EMPTY11[27];
} CAN_MsgObj_TypeDef;

typedef struct
{
  vu16 CR;
  u16  EMPTY1;
  vu16 SR;
  u16  EMPTY2;
  vu16 ERR;
  u16  EMPTY3;
  vu16 BTR;
  u16  EMPTY4;
  vu16 IDR;
  u16  EMPTY5;
  vu16 TESTR;
  u16  EMPTY6;
  vu16 BRPR;
  u16  EMPTY7[3];
  CAN_MsgObj_TypeDef sMsgObj[2];
  u16  EMPTY8[16];
  vu16 TR1R;
  u16  EMPTY9;
  vu16 TR2R;
  u16  EMPTY10[13];
  vu16 ND1R;
  u16  EMPTY11;
  vu16 ND2R;
  u16  EMPTY12[13];
  vu16 IP1R;
  u16  EMPTY13;
  vu16 IP2R;
  u16  EMPTY14[13];
  vu16 MV1R;
  u16  EMPTY15;
  vu16 MV2R;
  u16  EMPTY16;
} CAN_TypeDef;

/*------------------------ Enhanced Interrupt Controller ---------------------*/
typedef struct
{
  vu32 ICR;
  vu32 CICR;
  vu32 CIPR;
  u32  EMPTY1[3];
  vu32 IVR;
  vu32 FIR;
  vu32 IER;
  u32  EMPTY2[7];
  vu32 IPR;
  u32  EMPTY3[7];
  vu32 SIR[32];
} EIC_TypeDef;
/*------------------------ External Memory Interface -------------------------*/
typedef struct
{
  vu16 BCON0;
  u16  EMPTY1;
  vu16 BCON1;
  u16  EMPTY2;
  vu16 BCON2;
  u16  EMPTY3;
  vu16 BCON3;
  u16  EMPTY4;
} EMI_TypeDef;

/*------------------------ General Purpose IO ports --------------------------*/
typedef struct
{
  vu16 PC0;
  u16  EMPTY1;
  vu16 PC1;
  u16  EMPTY2;
  vu16 PC2;
  u16  EMPTY3;
  vu16 PD;
  u16  EMPTY4;
} GPIO_TypeDef;

/*------------------------ I2C interface -------------------------------------*/
typedef struct
{
  vu8  CR;
  u8   EMPTY1[3];
  vu8  SR1;
  u8   EMPTY2[3];
  vu8  SR2;
  u8   EMPTY3[3];
  vu8  CCR;
  u8   EMPTY4[3];
  vu8  OAR1;
  u8   EMPTY5[3];
  vu8  OAR2;
  u8   EMPTY6[3];
  vu8  DR;
  u8   EMPTY7[3];
  vu8  ECCR;
  u8   EMPTY8[3];
} I2C_TypeDef;

/*------------------------ Power Reset Clock Control unit --------------------*/
typedef struct
{
  vu32 CCR;
  u32  EMPTY1;
  vu32 CFR;
  u32  EMPTY2[3];
  vu32 PLL1CR;
  vu32 PER;
  vu32 SMR;
} RCCU_TypeDef;

typedef struct
{
  vu16 MDIVR;
  u16  EMPTY1;
  vu16 PDIVR;
  u16  EMPTY2;
  vu16 RSTR;
  u16  EMPTY3;
  vu16 PLL2CR;
  u16  EMPTY4;
  vu16 BOOTCR;
  u16  EMPTY5;
  vu16 PWRCR;
  u16  EMPTY6;
} PCU_TypeDef;

/*------------------------ Real Time Clock -----------------------------------*/
typedef struct
{
  vu16 CRH;
  u16  EMPTY1;
  vu16 CRL;
  u16  EMPTY2;
  vu16 PRLH;
  u16  EMPTY3;
  vu16 PRLL;
  u16  EMPTY4;
  vu16 DIVH;
  u16  EMPTY5;
  vu16 DIVL;
  u16  EMPTY6;
  vu16 CNTH;
  u16  EMPTY7;
  vu16 CNTL;
  u16  EMPTY8;
  vu16 ALRH;
  u16  EMPTY9;
  vu16 ALRL;
} RTC_TypeDef;

/*------------------------ TIM -----------------------------------------------*/
typedef struct
{
  vu16 ICAR;
  u16  EMPTY1;
  vu16 ICBR;
  u16  EMPTY2;
  vu16 OCAR;
  u16  EMPTY3;
  vu16 OCBR;
  u16  EMPTY4;
  vu16 CNTR;
  u16  EMPTY5;
  vu16 CR1;
  u16  EMPTY6;
  vu16 CR2;
  u16  EMPTY7;
  vu16 SR;
} TIM_TypeDef;

/*------------------------ Universal Asynchronous Receiver Transmitter -------*/
typedef struct
{
  vu16 BR;
  u16  EMPTY1;
  vu16 TxBUFR;
  u16  EMPTY2;
  vu16 RxBUFR;
  u16  EMPTY3;
  vu16 CR;
  u16  EMPTY4;
  vu16 IER;
  u16  EMPTY5;
  vu16 SR;
  u16  EMPTY6;
  vu16 GTR;
  u16  EMPTY7;
  vu16 TOR;
  u16  EMPTY8;
  vu16 TxRSTR;
  u16  EMPTY9;
  vu16 RxRSTR;
  u16  EMPTY10;  
} UART_TypeDef;

typedef struct
{
  vu32 EP0R;
  vu32 EP1R;
  vu32 EP2R;
  vu32 EP3R;
  vu32 EP4R;
  vu32 EP5R;
  vu32 EP6R;
  vu32 EP7R;
  vu32 EP8R;
  vu32 EP9R;
  vu32 EP10R;
  vu32 EP11R;
  vu32 EP12R;
  vu32 EP13R;
  vu32 EP14R;
  vu32 EP15R;
  vu32 CNTR;
  vu32 ISTR;
  vu32 FNR;
  vu32 DADDR;
  vu32 BTABLE;
} USB_TypeDef;

/*------------------------ WATCHDOG ------------------------------------------*/
typedef struct
{
  vu16 CR;
  u16  EMPTY1;
  vu16 PR;
  u16  EMPTY2;
  vu16 VR;
  u16  EMPTY3;
  vu16 CNT;
  u16  EMPTY4;
  vu16 SR;
  u16  EMPTY5;
  vu16 MR;
  u16  EMPTY6;
  vu16 KR;
} WDG_TypeDef;

/*------------------------ External Interrupt Controller ---------------------*/
typedef struct
{
  vu8  SR;
  u8   EMPTY1[7];
  vu8  CTRL;
  u8   EMPTY2[3];
  vu8  MRH;
  u8   EMPTY3[3];
  vu8  MRL;
  u8   EMPTY4[3];
  vu8  TRH;
  u8   EMPTY5[3];
  vu8  TRL;
  u8   EMPTY6[3];
  vu8  PRH;
  u8   EMPTY7[3];
  vu8  PRL;
} XTI_TypeDef;

typedef struct
{
  vu32 CR0;
  vu32 CR1;
  vu32 DR0;
  vu32 DR1;
  vu32 AR;
  vu32 ER;
} FLASHR_TypeDef;


/* IRQ vectors */
typedef struct
{
  vu32 T0TIMI_IRQHandler;
  vu32 RCCU_IRQHandler;
  vu32 RTC_IRQHandler;
  vu32 WDG_IRQHandler;
  vu32 XTI_IRQHandler;
  vu32 USBHP_IRQHandler;
  vu32 I2C0ITERR_IRQHandler;
  vu32 I2C1ITERR_IRQHandler;
  vu32 UART0_IRQHandler;
  vu32 UART1_IRQHandler;
  vu32 UART2_IRQHandler;
  vu32 UART3_IRQHandler;
  vu32 BSPI0_IRQHandler;
  vu32 BSPI1_IRQHandler;
  vu32 I2C0_IRQHandler;
  vu32 I2C1_IRQHandler;
  vu32 CAN_IRQHandler;
  vu32 ADC12_IRQHandler;
  vu32 T1TIMI_IRQHandler;
  vu32 T2TIMI_IRQHandler;
  vu32 T3TIMI_IRQHandler;
  u32  EMPTY1[3];
  vu32 HDLC_IRQHandler;
  vu32 USBLP_IRQHandler;
  u32  EMPTY2[2];
  vu32 T0TOI_IRQHandler;
  vu32 T0OC1_IRQHandler;
  vu32 T0OC2_IRQHandler;
} IRQVectors_TypeDef;

/******************************************************************************/
/*                       Peripheral memory map                                */
/******************************************************************************/
#define RAM_BASE        0x20000000

#define FLASHR_BASE     0x40100000
#define EXTMEM_BASE     0x60000000
#define RCCU_BASE       0xA0000000
#define PCU_BASE        0xA0000040
#define APB1_BASE       0xC0000000
#define APB2_BASE       0xE0000000
#define EIC_BASE        0xFFFFF800

#define I2C0_BASE       (APB1_BASE + 0x1000)
#define I2C1_BASE       (APB1_BASE + 0x2000)
#define UART0_BASE      (APB1_BASE + 0x4000)
#define UART1_BASE      (APB1_BASE + 0x5000)
#define UART2_BASE      (APB1_BASE + 0x6000)
#define UART3_BASE      (APB1_BASE + 0x7000)
#define CAN_BASE        (APB1_BASE + 0x9000)
#define BSPI0_BASE      (APB1_BASE + 0xA000)
#define BSPI1_BASE      (APB1_BASE + 0xB000)
#define USB_BASE        (APB1_BASE + 0x8800)

#define XTI_BASE        (APB2_BASE + 0x101C)
#define GPIO0_BASE      (APB2_BASE + 0x3000)
#define GPIO1_BASE      (APB2_BASE + 0x4000)
#define GPIO2_BASE      (APB2_BASE + 0x5000)
#define ADC12_BASE      (APB2_BASE + 0x7000)
#define TIM0_BASE       (APB2_BASE + 0x9000)
#define TIM1_BASE       (APB2_BASE + 0xA000)
#define TIM2_BASE       (APB2_BASE + 0xB000)
#define TIM3_BASE       (APB2_BASE + 0xC000)
#define RTC_BASE        (APB2_BASE + 0xD000)
#define WDG_BASE        (APB2_BASE + 0xE000)

#define EMI_BASE        (EXTMEM_BASE + 0x0C000000)

#define FLASHR  ((FLASHR_TypeDef *)FLASHR_BASE)

/*******************************************************************************
                            Peripheral declaration
*******************************************************************************/

/*------------------------ Non Debug Mode ------------------------------------*/
#ifndef DEBUG
#ifdef _ADC12
  #define ADC12               ((ADC12_TypeDef *)ADC12_BASE)
#endif /*ADC12*/

#ifdef _APB1
  #define APB1                ((APB_TypeDef *)(APB1_BASE+0x10))
#endif /*APB1*/

#ifdef _APB2
  #define APB2                ((APB_TypeDef *)(APB2_BASE+0x10))
#endif /*APB2*/

#ifdef _BSPI0
  #define BSPI0               ((BSPI_TypeDef *)BSPI0_BASE)
#endif /*BSPI0*/

#ifdef _BSPI1
  #define BSPI1               ((BSPI_TypeDef *)BSPI1_BASE)
#endif /*BSPI1*/

#ifdef _CAN
  #define CAN                 ((CAN_TypeDef *)CAN_BASE)
#endif /*CAN*/

#ifdef _EIC
  #define EIC                 ((EIC_TypeDef *)EIC_BASE)
#endif /*EIC*/

#ifdef _EMI
  #define EMI                 ((EMI_TypeDef *)EMI_BASE)
#endif /*EMI*/

#ifdef _GPIO0
  #define GPIO0               ((GPIO_TypeDef *)GPIO0_BASE)
#endif /*GPIO0*/

#ifdef _GPIO1
  #define GPIO1               ((GPIO_TypeDef *)GPIO1_BASE)
#endif /*GPIO1*/

#ifdef _GPIO2
  #define GPIO2               ((GPIO_TypeDef *)GPIO2_BASE)
#endif /*GPIO2*/

#ifdef _I2C0
  #define I2C0                ((I2C_TypeDef *)I2C0_BASE)
#endif /*I2C0*/

#ifdef _I2C1
  #define I2C1                ((I2C_TypeDef *)I2C1_BASE)
#endif /*I2C1*/

#ifdef _PCU
  #define PCU                 ((PCU_TypeDef *)PCU_BASE)
#endif /*PCU*/

#ifdef _RCCU
  #define RCCU                ((RCCU_TypeDef *)RCCU_BASE)
#endif /*RCCU*/

#ifdef _RTC
  #define RTC                 ((RTC_TypeDef *)RTC_BASE)
#endif /*RTC*/

#ifdef _TIM0
  #define TIM0                ((TIM_TypeDef *)TIM0_BASE)
#endif /*TIM0*/

#ifdef _TIM1
  #define TIM1                ((TIM_TypeDef *)TIM1_BASE)
#endif /*TIM1*/

#ifdef _TIM2
  #define TIM2                ((TIM_TypeDef *)TIM2_BASE)
#endif /*TIM2*/

#ifdef _TIM3
  #define TIM3                ((TIM_TypeDef *)TIM3_BASE)
#endif /*TIM3*/

#ifdef _UART0
  #define UART0               ((UART_TypeDef *)UART0_BASE)
#endif /*UART0*/

#ifdef _UART1
  #define UART1               ((UART_TypeDef *)UART1_BASE)
#endif /*UART1*/

#ifdef _UART2
  #define UART2               ((UART_TypeDef *)UART2_BASE)
#endif /*UART2*/

#ifdef _UART3
  #define UART3               ((UART_TypeDef *)UART3_BASE)
#endif /*UART3*/

#ifdef _WDG
  #define WDG                 ((WDG_TypeDef *)WDG_BASE)
#endif /*WDG*/

#ifdef _XTI
  #define XTI                 ((XTI_TypeDef *)XTI_BASE)
#endif /*XTI*/

#ifdef _IRQVectors
#define IIRQVectorsRQVectors ((IRQVectors_TypeDef *)&T0TIMI_Addr)
#endif /*XTI*/
/*------------------------ Debug Mode ----------------------------------------*/
#else   /* DEBUG */
#ifdef _ADC12
    EXT ADC12_TypeDef         *ADC12;
#endif

#ifdef _APB1
    EXT APB_TypeDef           *APB1;
#endif /*APB1*/

#ifdef _APB2
    EXT APB_TypeDef           *APB2;
#endif /*APB2*/

#ifdef _BSPI0
    EXT BSPI_TypeDef          *BSPI0;
#endif /*BSPI0*/

#ifdef _BSPI1
    EXT BSPI_TypeDef          *BSPI1;
#endif /*BSPI1*/

#ifdef _CAN
    EXT CAN_TypeDef           *CAN;
#endif /*CAN*/

#ifdef _EIC
    EXT EIC_TypeDef           *EIC;
#endif /*EIC*/

#ifdef _EMI
    EXT EMI_TypeDef           *EMI;
#endif /*EMI*/

#ifdef _GPIO0
    EXT GPIO_TypeDef          *GPIO0;
#endif /*GPIO0*/

#ifdef _GPIO1
    EXT GPIO_TypeDef          *GPIO1;
#endif /*GPIO1*/

#ifdef _GPIO2
    EXT GPIO_TypeDef          *GPIO2;
#endif /*GPIO2*/

#ifdef _I2C0
    EXT I2C_TypeDef           *I2C0;
#endif /*I2C0*/

#ifdef _I2C1
    EXT I2C_TypeDef           *I2C1;
#endif /*I2C1*/

#ifdef _PCU
    EXT PCU_TypeDef           *PCU;
#endif /*PCU*/

#ifdef _RCCU
    EXT RCCU_TypeDef          *RCCU;
#endif /*RCCU*/

#ifdef _RTC
    EXT RTC_TypeDef           *RTC;
#endif /*RTC*/

#ifdef _TIM0
    EXT TIM_TypeDef           *TIM0;
#endif /*TIM0*/

#ifdef _TIM1
    EXT TIM_TypeDef           *TIM1;
#endif /*TIM1*/

#ifdef _TIM2
    EXT TIM_TypeDef           *TIM2;
#endif /*TIM2*/

#ifdef _TIM3
    EXT TIM_TypeDef           *TIM3;
#endif /*TIM3*/

#ifdef _UART0
    EXT UART_TypeDef          *UART0;
#endif /*UART0*/

#ifdef _UART1
    EXT UART_TypeDef          *UART1;
#endif /*UART1*/

#ifdef _UART2
    EXT UART_TypeDef          *UART2;
#endif /*UART2*/

#ifdef _UART3
    EXT UART_TypeDef          *UART3;
#endif /*UART3*/

#ifdef _WDG
    EXT WDG_TypeDef           *WDG;
#endif /*WDG*/

#ifdef _XTI
    EXT XTI_TypeDef           *XTI;
#endif /*XTI*/

#ifdef _IRQVectors
    EXT IRQVectors_TypeDef    *IRQVectors;
#endif
#endif  /* DEBUG */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
    
#endif  /*__71x_MAP_H*/

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
