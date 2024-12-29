/**
 * Radio data transfer - write
 *
 * @remark Shall be implemented by the user
 *
 * @param [in] _lora          Radio implementation parameters
 * @param [in] command          Pointer to the buffer to be transmitted
 * @param [in] command_length   Buffer size to be transmitted
 * @param [in] data             Pointer to the buffer to be transmitted
 * @param [in] data_length      Buffer size to be transmitted
 *
 * @returns Operation status
 */
llcc68_hal_status_t llcc68_hal_write( const lora* _lora, const uint8_t* command, const uint16_t command_length,
                                      const uint8_t* data, const uint16_t data_length )
{
	/* FIXME: use busy pin if allocated in remote and gateway node on board */
	llcc68_hal_status_t ret = LLCC68_HAL_STATUS_OK;

	/* copied constant buffers in temporary variable to avoid warnings */
	uint8_t* opcode = (uint8_t*) command;
	uint8_t* tx_buffer = (uint8_t*) data;
	uint16_t opcode_length = command_length;
	uint16_t tx_buffer_length = data_length;

	/* Enable SPI slave */
	HAL_GPIO_WritePin(_lora->CS_port, _lora->CS_pin, GPIO_PIN_RESET);

	/* Send command opcode*/
	HAL_SPI_Transmit(_lora->hSPIx, opcode, opcode_length, TRANSMIT_TIMEOUT);
	while (HAL_SPI_GetState(_lora->hSPIx) != HAL_SPI_STATE_READY);

//	if(data == 0 || data_length == 0)
//	{
//		/* Disable SPI slave */
//		HAL_GPIO_WritePin(_lora->CS_port, _lora->CS_pin, GPIO_PIN_SET);
//		HAL_Delay(1);
//		return 0;
//	}
//	else
//	{
//		HAL_Delay(1);
//	}
	HAL_Delay(1);

	/* send command option or message */
	HAL_SPI_Transmit(_lora->hSPIx, tx_buffer, tx_buffer_length, TRANSMIT_TIMEOUT);
	while (HAL_SPI_GetState(_lora->hSPIx) != HAL_SPI_STATE_READY);

	/* Disable SPI slave */
	HAL_GPIO_WritePin(_lora->CS_port, _lora->CS_pin, GPIO_PIN_SET);
	HAL_Delay(1);
	return ret;
}

/**
 * Radio data transfer - read
 *
 * @remark Shall be implemented by the user
 *
 * @param [in] _lora          Radio implementation parameters (object handler)
 * @param [in] command          Pointer to the buffer to be transmitted
 * @param [in] command_length   Buffer size to be transmitted
 * @param [in] data             Pointer to the buffer to be received
 * @param [in] data_length      Buffer size to be received
 *
 * @returns Operation status
 */
llcc68_hal_status_t llcc68_hal_read( const lora* _lora, const uint8_t* command, const uint16_t command_length,
                                     uint8_t* data, const uint16_t data_length )
{
	/* FIXME: use busy pin if allocated in remote and gateway node on board */
	llcc68_hal_status_t ret = LLCC68_HAL_STATUS_OK;

	/* copied constant buffers in temporary variable to avoid warnings */
	uint8_t* opcode = (uint8_t*)command;
	uint16_t opcode_length = command_length;

	memset(data, LLCC68_NOP, data_length); /* FIXME: check if required or not */

	/* Enable SPI slave */
	HAL_GPIO_WritePin(_lora->CS_port, _lora->CS_pin, GPIO_PIN_RESET);

	/* Send command opcode */
	HAL_SPI_Transmit(_lora->hSPIx, opcode, opcode_length, TRANSMIT_TIMEOUT);
	while (HAL_SPI_GetState(_lora->hSPIx) != HAL_SPI_STATE_READY);

	//HAL_Delay(1);

	/* read message or response */
	HAL_SPI_Receive(_lora->hSPIx, data, data_length, RECEIVE_TIMEOUT);
	while (HAL_SPI_GetState(_lora->hSPIx) != HAL_SPI_STATE_READY);

	/* Disable SPI slave */
	HAL_GPIO_WritePin(_lora->CS_port, _lora->CS_pin, GPIO_PIN_SET);

	/* FIXME: update return error status properly */
	//HAL_Delay(1);
	return ret;
}

/**
 * Reset the radio
 *
 * @remark Shall be implemented by the user
 *
 * @param [in] _lora Radio implementation parameters
 *
 * @returns Operation status
 */
llcc68_hal_status_t llcc68_hal_reset( const lora* _lora )
{
	llcc68_hal_status_t ret = LLCC68_HAL_STATUS_ERROR;

	HAL_GPIO_WritePin(_lora->reset_port, _lora->reset_pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(_lora->reset_port, _lora->reset_pin, GPIO_PIN_SET);
	HAL_Delay(100);
	ret = LLCC68_HAL_STATUS_OK;

	/* FIXME: use busy pin if allocated in remote and gateway node on board */
//	while(ret != LLCC68_HAL_STATUS_OK)
//	{
//		HAL_GPIO_WritePin(_lora->reset_port, _lora->reset_pin, GPIO_PIN_RESET);
//		ret = HAL_GPIO_ReadPin(_lora->reset_port, _lora->reset_pin);
//
//		HAL_Delay(1);
//
//		if(ret == LLCC68_HAL_STATUS_OK){
//			HAL_GPIO_WritePin(_lora->reset_port, _lora->reset_pin, GPIO_PIN_SET);
//			ret = HAL_GPIO_ReadPin(_lora->reset_port, _lora->reset_pin);
//			break;
//		}
//		HAL_Delay(100);
//	}
	return ret;
}

/**
 * Wake the radio up.
 *
 * @remark Shall be implemented by the user
 *
 * @param [in] _lora Radio implementation parameters
 *
 * @returns Operation status
 */
llcc68_hal_status_t llcc68_hal_wakeup( const lora* _lora )
{
	/* FIXME: update it when low power mode is added */
	/* FIXME: use busy pin if allocated in remote and gateway node on board */
	llcc68_hal_status_t ret = LLCC68_HAL_STATUS_OK;
	while(1); // not implemented yet

	return ret;
}


/**
 * set pin in initial preset state.
 *
 * @remark Shall be implemented by the user
 *
 * @param [in] No Parameter
 *
 * @returns Operation status
 */
llcc68_hal_status_t llcc68_hal_preset( const lora* _lora )
{
	llcc68_hal_status_t ret = LLCC68_HAL_STATUS_ERROR;

	/* set reset and cs pin high */
	HAL_GPIO_WritePin(_lora->CS_port, _lora->CS_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(_lora->reset_port, _lora->reset_pin, GPIO_PIN_SET);
	HAL_Delay(10);

	return ret;
}
