/*
 * Copyright (c) 2024 Indiesemic Pvt Ltd.
 */

#include "ble_data_process.h"
#include "custom_service.h"
#include <zephyr/logging/log.h>
#include "glob_var.h"

int ble_process_received_data(const uint8_t *const req_data, uint16_t len, uint8_t *resp_data)
{
	switch (req_data[COMMAND_POS])
	{
	case SEND_CRED:
		resp_data[RESP_COMMAND_POS] = RESP_COMMAND_MUL | req_data[COMMAND_POS];
		resp_data[RESP_DATA_POS] = req_data[RESP_DATA_POS];
		return 3;
		break;
	case SEND_QNA:
		resp_data[RESP_COMMAND_POS] = RESP_COMMAND_MUL | req_data[COMMAND_POS];
		resp_data[RESP_COMMAND_POS] = req_data[RESP_DATA_POS];
		return 3;
	default:
		break;
	}
	return 1;
}