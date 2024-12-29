#include "sx126x_hal.h"
#include "hal_data.h"

typedef enum sx126x_commands_e
{
    // Operational Modes Functions
    SX126X_SET_SLEEP                  = 0x84,
    SX126X_SET_STANDBY                = 0x80,
    SX126X_SET_FS                     = 0xC1,
    SX126X_SET_TX                     = 0x83,
    SX126X_SET_RX                     = 0x82,
    SX126X_SET_STOP_TIMER_ON_PREAMBLE = 0x9F,
    SX126X_SET_RX_DUTY_CYCLE          = 0x94,
    SX126X_SET_CAD                    = 0xC5,
    SX126X_SET_TX_CONTINUOUS_WAVE     = 0xD1,
    SX126X_SET_TX_INFINITE_PREAMBLE   = 0xD2,
    SX126X_SET_REGULATOR_MODE         = 0x96,
    SX126X_CALIBRATE                  = 0x89,
    SX126X_CALIBRATE_IMAGE            = 0x98,
    SX126X_SET_PA_CFG                 = 0x95,
    SX126X_SET_RX_TX_FALLBACK_MODE    = 0x93,
    // Registers and buffer Access
    SX126X_WRITE_REGISTER = 0x0D,
    SX126X_READ_REGISTER  = 0x1D,
    SX126X_WRITE_BUFFER   = 0x0E,
    SX126X_READ_BUFFER    = 0x1E,
    // DIO and IRQ Control Functions
    SX126X_SET_DIO_IRQ_PARAMS         = 0x08,
    SX126X_GET_IRQ_STATUS             = 0x12,
    SX126X_CLR_IRQ_STATUS             = 0x02,
    SX126X_SET_DIO2_AS_RF_SWITCH_CTRL = 0x9D,
    SX126X_SET_DIO3_AS_TCXO_CTRL      = 0x97,
    // RF Modulation and Packet-Related Functions
    SX126X_SET_RF_FREQUENCY          = 0x86,
    SX126X_SET_PKT_TYPE              = 0x8A,
    SX126X_GET_PKT_TYPE              = 0x11,
    SX126X_SET_TX_PARAMS             = 0x8E,
    SX126X_SET_MODULATION_PARAMS     = 0x8B,
    SX126X_SET_PKT_PARAMS            = 0x8C,
    SX126X_SET_CAD_PARAMS            = 0x88,
    SX126X_SET_BUFFER_BASE_ADDRESS   = 0x8F,
    SX126X_SET_LORA_SYMB_NUM_TIMEOUT = 0xA0,
    // Communication Status Information
    SX126X_GET_STATUS           = 0xC0,
    SX126X_GET_RX_BUFFER_STATUS = 0x13,
    SX126X_GET_PKT_STATUS       = 0x14,
    SX126X_GET_RSSI_INST        = 0x15,
    SX126X_GET_STATS            = 0x10,
    SX126X_RESET_STATS          = 0x00,
    // Miscellaneous
    SX126X_GET_DEVICE_ERRORS = 0x17,
    SX126X_CLR_DEVICE_ERRORS = 0x07,
} sx126x_commands_t;

typedef enum sx126x_commands_size_e
{
    // Operational Modes Functions
    SX126X_SIZE_SET_SLEEP                  = 2,
    SX126X_SIZE_SET_STANDBY                = 2,
    SX126X_SIZE_SET_FS                     = 1,
    SX126X_SIZE_SET_TX                     = 4,
    SX126X_SIZE_SET_RX                     = 4,
    SX126X_SIZE_SET_STOP_TIMER_ON_PREAMBLE = 2,
    SX126X_SIZE_SET_RX_DUTY_CYCLE          = 7,
    SX126X_SIZE_SET_CAD                    = 1,
    SX126X_SIZE_SET_TX_CONTINUOUS_WAVE     = 1,
    SX126X_SIZE_SET_TX_INFINITE_PREAMBLE   = 1,
    SX126X_SIZE_SET_REGULATOR_MODE         = 2,
    SX126X_SIZE_CALIBRATE                  = 2,
    SX126X_SIZE_CALIBRATE_IMAGE            = 3,
    SX126X_SIZE_SET_PA_CFG                 = 5,
    SX126X_SIZE_SET_RX_TX_FALLBACK_MODE    = 2,
    // Registers and buffer Access
    // Full size: this value plus buffer size
    SX126X_SIZE_WRITE_REGISTER = 3,
    // Full size: this value plus buffer size
    SX126X_SIZE_READ_REGISTER = 4,
    // Full size: this value plus buffer size
    SX126X_SIZE_WRITE_BUFFER = 2,
    // Full size: this value plus buffer size
    SX126X_SIZE_READ_BUFFER = 3,
    // DIO and IRQ Control Functions
    SX126X_SIZE_SET_DIO_IRQ_PARAMS         = 9,
    SX126X_SIZE_GET_IRQ_STATUS             = 2,
    SX126X_SIZE_CLR_IRQ_STATUS             = 3,
    SX126X_SIZE_SET_DIO2_AS_RF_SWITCH_CTRL = 2,
    SX126X_SIZE_SET_DIO3_AS_TCXO_CTRL      = 5,
    // RF Modulation and Packet-Related Functions
    SX126X_SIZE_SET_RF_FREQUENCY           = 5,
    SX126X_SIZE_SET_PKT_TYPE               = 2,
    SX126X_SIZE_GET_PKT_TYPE               = 3,
    SX126X_SIZE_SET_TX_PARAMS              = 3,
    SX126X_SIZE_SET_MODULATION_PARAMS_GFSK = 9,
    SX126X_SIZE_SET_MODULATION_PARAMS_LORA = 5,
    SX126X_SIZE_SET_PKT_PARAMS_GFSK        = 10,
    SX126X_SIZE_SET_PKT_PARAMS_LORA        = 7,
    SX126X_SIZE_SET_CAD_PARAMS             = 8,
    SX126X_SIZE_SET_BUFFER_BASE_ADDRESS    = 3,
    SX126X_SIZE_SET_LORA_SYMB_NUM_TIMEOUT  = 2,
    // Communication Status Information
    SX126X_SIZE_GET_STATUS           = 1,
    SX126X_SIZE_GET_RX_BUFFER_STATUS = 2,
    SX126X_SIZE_GET_PKT_STATUS       = 2,
    SX126X_SIZE_GET_RSSI_INST        = 2,
    SX126X_SIZE_GET_STATS            = 2,
    SX126X_SIZE_RESET_STATS          = 7,
    // Miscellaneous
    SX126X_SIZE_GET_DEVICE_ERRORS = 2,
    SX126X_SIZE_CLR_DEVICE_ERRORS = 3,
    SX126X_SIZE_MAX_BUFFER        = 255,
    SX126X_SIZE_DUMMY_BYTE        = 1,
} sx126x_commands_size_t;

sx126x_hal_status_t sx126x_set_sleep( const void* context, const sx126x_sleep_cfgs_t cfg )
{
    const uint8_t buf[SX126X_SIZE_SET_SLEEP] = {
        SX126X_SET_SLEEP,
        ( uint8_t ) cfg,
    };
    return ( sx126x_hal_status_t ) sx126x_hal_write( context, buf, SX126X_SIZE_SET_SLEEP, 0, 0 );
}

sx126x_hal_status_t sx126x_set_standby( const void* context, const sx126x_standby_cfg_t cfg )
{
    const uint8_t buf[SX126X_SIZE_SET_STANDBY] = {
        SX126X_SET_STANDBY,
        ( uint8_t ) cfg,
    };
    return ( sx126x_hal_status_t ) sx126x_hal_write( context, buf, SX126X_SIZE_SET_STANDBY, 0, 0 );
}


sx126x_hal_status_t sx126x_hal_write(const void *context, const uint8_t *command, const uint16_t command_length, const uint8_t *data, const uint16_t data_length)
{
    sx126x_hal_status_t ret = SX126X_HAL_STATUS_OK ;

    uint8_t* opcode = (uint8_t*) command;
	uint8_t* tx_buffer = (uint8_t*) data;
	uint16_t opcode_length = command_length;
	uint16_t tx_buffer_length = data_length;

	R_IOPORT_PinWrite(&g_ioport_ctrl,CS, BSP_IO_LEVEL_LOW);
	R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MILLISECONDS);

	R_SPI_Write(&g_spi1_ctrl, opcode, opcode_length,SPI_BIT_WIDTH_8_BITS);
//	R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);

	R_SPI_Write(&g_spi1_ctrl, tx_buffer, tx_buffer_length,SPI_BIT_WIDTH_8_BITS);
//	R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);

	R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MILLISECONDS);
	R_IOPORT_PinWrite(&g_ioport_ctrl,CS, BSP_IO_LEVEL_HIGH);

	return ret;
}

sx126x_hal_status_t sx126x_hal_read( const void *context, const uint8_t* command, const uint16_t command_length,uint8_t *data, const uint16_t data_length )
{
    sx126x_hal_status_t ret = SX126X_HAL_STATUS_OK;

    uint8_t* opcode = (uint8_t*)command;
    uint16_t opcode_length = command_length;

    memset(data, SX126X_NOP, data_length);
    /* Enable SPI slave */
    R_IOPORT_PinWrite(&g_ioport_ctrl,CS, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MILLISECONDS);
    /* Send command opcode */
    R_SPI_Write(&g_spi1_ctrl, opcode, opcode_length,SPI_BIT_WIDTH_8_BITS);
    /* read message or response */
    R_SPI_Read(&g_ioport_ctrl, data, data_length, SPI_BIT_WIDTH_8_BITS);
    /* Disable SPI slave */
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MILLISECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl,CS, BSP_IO_LEVEL_HIGH);

    return ret;
}

sx126x_hal_status_t sx126x_hal_reset( const void *context)
{
    sx126x_hal_status_t ret = SX126X_HAL_STATUS_ERROR;

    R_IOPORT_PinWrite(&g_ioport_ctrl,RESET, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MILLISECONDS);

    R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(100,BSP_DELAY_UNITS_MILLISECONDS);
    ret = SX126X_HAL_STATUS_OK;

    return ret;
}

sx126x_hal_status_t sx126x_hal_wakeup( const void *context )
{
    sx126x_hal_status_t ret = SX126X_HAL_STATUS_OK;
    return ret;
}

sx126x_hal_status_t sx126x_hal_preset( const void* context )
{
    sx126x_hal_status_t ret = SX126X_HAL_STATUS_ERROR;
    /* set reset and cs pin high */
    R_IOPORT_PinWrite(&g_ioport_ctrl,CS, BSP_IO_LEVEL_HIGH);
    R_IOPORT_PinWrite(&g_ioport_ctrl, RESET, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(10,BSP_DELAY_UNITS_MILLISECONDS);

    return ret;
}


