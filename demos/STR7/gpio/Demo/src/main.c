#include "71x_lib.h"

volatile int a;

void Delay(vu32 nCount);

int main()
{
    #ifdef DEBUG
    debug();    // STR71x library debug
    #endif

    /* MCLK = PCLK1 = PCLK2 = 24MHz*/
    /* Configure PCLK1 = RCLK / 1 */
    RCCU_PCLK1Config (RCCU_DEFAULT);

    /* Configure PCLK2 = RCLK / 1 */
    RCCU_PCLK2Config (RCCU_DEFAULT);

    /* Configure MCLK clock for the CPU, RCCU_DEFAULT = RCLK /1 */
    RCCU_MCLKConfig (RCCU_DEFAULT);

    /* Configure the PLL1 ( * 12 , / 4 ) */
    RCCU_PLL1Config (RCCU_PLL1_Mul_12, RCCU_Div_4) ;

    while(RCCU_FlagStatus(RCCU_PLL1_LOCK) == RESET)
    {
    /* Wait PLL to lock */
    }

    /* Select PLL1_Output as RCLK clock */
    RCCU_RCLKSourceConfig (RCCU_PLL1_Output) ;

    /* Enable GPIO0 and GPIO1 clocks on APB2 */
    APB_ClockConfig (APB2, ENABLE, GPIO0_Periph | GPIO1_Periph);

    /* GPIO configuration ------------------------------------------------------*/
    /* Configure P0.0 to P0.7 as Output Push-Pull */
    GPIO_Config(GPIO0, 0x00FF, GPIO_OUT_PP);

    /* Configure P0.7 to P0.15 as Input TTL */
    GPIO_Config(GPIO0, 0xFF00 , GPIO_IN_TRI_TTL);

    /* Configure P1.4 as Output Push-Pull */
    GPIO_Config(GPIO1, 0x0010, GPIO_OUT_PP);

    /* Configure P1.1 as Input TTL */
    GPIO_Config(GPIO1, 0x0001, GPIO_IN_TRI_TTL);

    GPIO_WordWrite(GPIO0, 0xFF00);

    a = 0;  // Some variable that counts up...

    /*  infinite loop */
    while(1)
    {
         /* Insert delay */
        Delay(0xFFFFF);

        /* GPIO_ByteWrite(GPIO0, GPIO_LSB, ~GPIO_ByteRead(GPIO0, GPIO_LSB)); */

        /* GPIO_BitWrite(GPIO1, 4, ~GPIO_BitRead(GPIO1, 4)); */

        /*  Toggle the GPIO0 port pins */
        GPIO_WordWrite(GPIO0, ~GPIO_WordRead(GPIO0));

        a++;

    }
}

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
