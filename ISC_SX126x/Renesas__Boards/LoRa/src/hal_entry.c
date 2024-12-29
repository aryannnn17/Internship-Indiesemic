#include "hal_data.h"
#include "sx126x_hal.h"
#include "sx126x.h"
#include "sx126x_context.h"
#include "sx126x_tx.h"
#include <stdio.h>
FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

void system_init(void);
int _write(int file, char *buffer, int count);

void spi_callback(spi_callback_args_t *p_args)
{
    (void)p_args;
}

volatile bool transmitComplete;
void user_uart_callback(uart_callback_args_t *p_args)
{
    switch (p_args->event)
    {
    case UART_EVENT_TX_COMPLETE:
        transmitComplete = true;
        break;
    case UART_EVENT_RX_CHAR:
        break;
    default:
        break;
    }
}

void system_init(void)
{
    R_SCI_UART_Open(&g_uart0_ctrl, &g_uart0_cfg);
}
// lora context;
int _write(int file, char *buffer, int count)
{
    (void)file;
    int tx_count;
    int i;

    for (i = 0, tx_count = 0; i < count; i++, tx_count++)
    {
        transmitComplete = false;
        R_SCI_UART_Write(&g_uart0_ctrl, (uint8_t const *)(buffer + i), 1);
        while (!transmitComplete)
        {
        };
    }
    return tx_count;
}

void hal_entry(void)
{
    //    system_init();
    //    printf("Hello!");
    //    printf()
    // context.frequency=868000000;
    R_SPI_Open(&g_spi1_ctrl, &g_spi1_cfg);

    //    int data = 0x1A;
    while (1)
    {
        tx_setup();
        tx_loop();
        //        sx126x_set_sleep(&context, SX126X_SLEEP_CFG_WARM_START);
        //
        //        sx126x_set_standby(&context, SX126X_STANDBY_CFG_RC);
        //
        //        const sx126x_mod_params_lora_t data = {
        //            .bw = SX126X_LORA_BW_500,
        //            .sf = SX126X_LORA_SF12,
        //            .cr = SX126X_LORA_CR_4_5,
        //            .ldro = 0x01,
        //        };
        //        sx126x_set_lora_mod_params(&context, &data);
        //
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED2, BSP_IO_LEVEL_HIGH);
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED1, BSP_IO_LEVEL_LOW);
        R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);
        //        //            R_SPI_Write(&g_spi1_ctrl, &data, 1,SPI_BIT_WIDTH_8_BITS);
        //        //            R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED2, BSP_IO_LEVEL_LOW);
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED1, BSP_IO_LEVEL_HIGH);
        R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);
    }
#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************/ /**
                                                                                                                       * This function is called at various points during the startup process.  This implementation uses the event that is
                                                                                                                       * called right before main() to set up the pins.
                                                                                                                       *
                                                                                                                       * @param[in]  event    Where at in the start up process the code is currently at
                                                                                                                       **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        IOPORT_CFG_OPEN(&IOPORT_CFG_CTRL, &IOPORT_CFG_NAME);
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable()
{
}
FSP_CPP_FOOTER

#endif
