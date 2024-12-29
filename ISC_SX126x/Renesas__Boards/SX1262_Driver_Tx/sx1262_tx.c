#include "hal_data.h"
#include "sx1262_tx.h"
#include "sx1262_driver.h"

sx126x_hal_status_t sx126x_hal_write(const void *context, const uint8_t *command, const uint16_t command_length, const uint8_t *data, const uint16_t data_length)
{
  sx126x_hal_status_t ret = SX126X_HAL_STATUS_OK;

  uint8_t *opcode = (uint8_t *)command;
  uint8_t *tx_buffer = (uint8_t *)data;
  uint16_t opcode_length = command_length;
  uint16_t tx_buffer_length = data_length;

  R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_LOW);
  R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);

  R_SPI_Write(&g_spi1_ctrl, opcode, opcode_length, SPI_BIT_WIDTH_8_BITS);
  //	R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);

  R_SPI_Write(&g_spi1_ctrl, tx_buffer, tx_buffer_length, SPI_BIT_WIDTH_8_BITS);
  //	R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);

  R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
  R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_HIGH);

  return ret;
}

sx126x_hal_status_t sx126x_hal_read(const void *context, const uint8_t *command, const uint16_t command_length, uint8_t *data, const uint16_t data_length)
{
  sx126x_hal_status_t ret = SX126X_HAL_STATUS_OK;

  uint8_t *opcode = (uint8_t *)command;
  uint16_t opcode_length = command_length;

  memset(data, SX126X_NOP, data_length);
  /* Enable SPI slave */
  R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_LOW);
  R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
  /* Send command opcode */
  R_SPI_Write(&g_spi1_ctrl, opcode, opcode_length, SPI_BIT_WIDTH_8_BITS);
  /* read message or response */
  R_SPI_Read(&g_ioport_ctrl, data, data_length, SPI_BIT_WIDTH_8_BITS);
  /* Disable SPI slave */
  R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
  R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_HIGH);

  return ret;
}

sx126x_hal_status_t sx126x_hal_reset(const void *context)
{
  sx126x_hal_status_t ret = SX126X_HAL_STATUS_ERROR;

  R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_LOW);
  R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

  R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_HIGH);
  R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MILLISECONDS);
  ret = SX126X_HAL_STATUS_OK;

  return ret;
}

sx126x_hal_status_t sx126x_hal_wakeup(const void *context)
{
  sx126x_hal_status_t ret = SX126X_HAL_STATUS_OK;
  return ret;
}

sx126x_hal_status_t sx126x_hal_preset(const void *context)
{
  sx126x_hal_status_t ret = SX126X_HAL_STATUS_ERROR;
  /* set reset and cs pin high */
  R_IOPORT_PinWrite(&g_ioport_ctrl, CS, BSP_IO_LEVEL_HIGH);
  R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_HIGH);
  R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);

  return ret;
}
