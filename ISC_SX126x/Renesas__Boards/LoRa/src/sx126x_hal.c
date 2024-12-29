#include "sx126x_hal.h"
#include "hal_data.h"
#include "sx126x.h"
#include "sx126x_context.h"

sx126x_hal_status_t sx126x_hal_write(lora *context, const uint8_t *command, const uint16_t command_length, const uint8_t *data, const uint16_t data_length)
{
    if (BUSY == BSP_IO_LEVEL_HIGH)
    {
        R_BSP_SoftwareDelay(5000, BSP_DELAY_UNITS_MILLISECONDS);
        if (BUSY == BSP_IO_LEVEL_HIGH)
        {
            sx126x_hal_status_t ret = SX126X_HAL_STATUS_ERROR;
            return ret;
        }
    }
    sx126x_hal_status_t ret = SX126X_STATUS_OK;

    uint8_t *opcode = (uint8_t *)command;
    uint8_t *tx_buffer = (uint8_t *)data;
    uint16_t opcode_length = command_length;
    uint16_t tx_buffer_length = data_length;

    R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    R_SPI_Write(&g_spi1_ctrl, opcode, opcode_length, SPI_BIT_WIDTH_8_BITS);
    //  R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);

    R_SPI_Write(&g_spi1_ctrl, tx_buffer, tx_buffer_length, SPI_BIT_WIDTH_8_BITS);
    //  R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_HIGH);

    return ret;
}

sx126x_hal_status_t sx126x_hal_read(lora *context, const uint8_t *command, const uint16_t command_length, uint8_t *data, const uint16_t data_length)
{
    if (BUSY == BSP_IO_LEVEL_HIGH)
    {
        R_BSP_SoftwareDelay(5000, BSP_DELAY_UNITS_MILLISECONDS);
        if (BUSY == BSP_IO_LEVEL_HIGH)
        {
            sx126x_hal_status_t ret = SX126X_HAL_STATUS_ERROR;
            return ret;
        }
    }
    sx126x_hal_status_t ret = SX126X_STATUS_OK;

    uint8_t *opcode = (uint8_t *)command;
    uint16_t opcode_length = command_length;

    memset(data, SX126X_NOP, data_length);
    /* Enable SPI slave */
    R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    /* Send command opcode */
    R_SPI_Write(&g_spi1_ctrl, opcode, opcode_length, SPI_BIT_WIDTH_8_BITS);
    /* read message or response */
    R_SPI_Read(&g_spi1_ctrl, data, data_length, SPI_BIT_WIDTH_8_BITS);
    /* Disable SPI slave */
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_HIGH);

    return ret;
}

sx126x_hal_status_t sx126x_hal_reset(lora *context)
{
    sx126x_hal_status_t ret = SX126X_STATUS_ERROR;

    R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);

    R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    ret = SX126X_STATUS_OK;

    return ret;
}

sx126x_hal_status_t sx126x_hal_wakeup(lora *context)
{
    sx126x_hal_status_t ret = SX126X_STATUS_OK;
    return ret;
}

sx126x_hal_status_t sx126x_hal_preset(lora *context)
{
    sx126x_hal_status_t ret = SX126X_STATUS_ERROR;
    /* set reset and cs pin high */
    R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_HIGH);
    R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);

    return ret;
}

// bool sx126x_busyCheck(uint32_t timeout)
//{
//     uint32_t t = ;
//     while (digitalRead(sx126x_busy) == HIGH) if (millis() - t > timeout) return true;
//     return false;
// }
