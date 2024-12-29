#ifndef LORA_INC_LORA_H_
#define LORA_INC_LORA_H_

#include "main.h"

#define TRANSMIT_TIMEOUT	2000
#define RECEIVE_TIMEOUT		2000
//
////--------- MODES ---------//
//#define SLEEP_MODE				0
//#define	STNBY_MODE				1
//#define TRANSMIT_MODE			3
//#define RXCONTIN_MODE			5
//#define RXSINGLE_MODE			6
//
////------- BANDWIDTH -------//
//#define BW_7_8KHz				0
//#define BW_10_4KHz				1
//#define BW_15_6KHz				2
//#define BW_20_8KHz				3
//#define BW_31_25KHz				4
//#define BW_41_7KHz				5
//#define BW_62_5KHz				6
//#define BW_125KHz				7
//#define BW_250KHz				8
//#define BW_500KHz				9
//
////------ CODING RATE ------//
//#define CR_4_5					1
//#define CR_4_6					2
//#define CR_4_7					3
//#define CR_4_8					4
//
////--- SPREADING FACTORS ---//
//#define SF_7					7
//#define SF_8					8
//#define SF_9					9
//#define SF_10					10
//#define SF_11  					11
//#define SF_12					12
//
////------ POWER GAIN ------//
//#define POWER_11db				0xF6
//#define POWER_14db				0xF9
//#define POWER_17db				0xFC
//#define POWER_20db				0xFF
//
////------- REGISTERS -------//
//#define RegFiFo						0x00
//#define RegOpMode					0x01
//#define RegFrMsb					0x06
//#define RegFrMid					0x07
//#define RegFrLsb					0x08
//#define RegPaConfig					0x09
//#define RegOcp						0x0B
//#define RegLna						0x0C
//#define RegFiFoAddPtr				0x0D
//#define RegFiFoTxBaseAddr			0x0E
//#define RegFiFoRxBaseAddr			0x0F
//#define RegFiFoRxCurrentAddr		0x10
//#define RegIrqFlags					0x12
//#define RegRxNbBytes				0x13
//#define RegPktRssiValue				0x1A
//#define	RegModemConfig1				0x1D
//#define RegModemConfig2				0x1E
//#define RegSymbTimeoutL				0x1F
//#define RegPreambleMsb				0x20
//#define RegPreambleLsb				0x21
//#define RegPayloadLength			0x22
//#define RegDioMapping1				0x40
//#define RegDioMapping2				0x41
//#define RegVersion					0x42
//
//------ LORA STATUS ------//
#define LORA_OK						200
#define LORA_NOT_FOUND				404
#define LORA_LARGE_PAYLOAD			413
#define LORA_UNAVAILABLE			503

typedef struct lora_setting{

	// Hardware setings:
	GPIO_TypeDef*      CS_port;
	uint16_t		   CS_pin;
	GPIO_TypeDef*      reset_port;
	uint16_t		   reset_pin;
	GPIO_TypeDef*      DIO0_port;
	uint16_t		   DIO0_pin;
	SPI_HandleTypeDef* hSPIx;

	// Module settings:
	int				current_mode;
	int 			frequency;
	uint8_t			spredingFactor;
	uint8_t			bandWidth;
	uint8_t			crcRate;
	uint16_t		preamble;
	uint8_t			power;
	uint8_t			overCurrentProtection;

} lora;

lora new_lora(void);
void lora_initial_state(lora* _lora);
void lora_reset(lora* _lora);
void lora_read_reg(lora* _lora, uint8_t* address, uint16_t r_length, uint8_t* output, uint16_t w_length);
void lora_write_reg(lora* _lora, uint8_t* address, uint16_t r_length, uint8_t* values, uint16_t w_length);
void lora_go_to_mode(lora* _lora, int mode);
uint8_t lora_read(lora* _lora, uint8_t address);
void lora_write(lora* _lora, uint8_t address, uint8_t value);
void lora_burst_write(lora* _lora, uint8_t address, uint8_t *value, uint8_t length);
uint8_t lora_is_valid(lora* _lora);

void lora_set_frequency(lora* _lora, int freq);
void lora_set_spreading_factor(lora* _lora, int SP);
void lora_set_power(lora* _lora, uint8_t power);
void lora_set_ocp(lora* _lora, uint8_t current);
void lora_set_to_msb_set_crc_on(lora* _lora);
uint8_t lora_transmit(lora* _lora, uint8_t* data, uint8_t length, uint16_t timeout);
void lora_start_receiving(lora* _lora);
uint8_t lora_receive(lora* _lora, uint8_t* data, uint8_t length);
void lora_receive_IT(lora* _lora, uint8_t* data, uint8_t length);
int lora_get_rssi(lora* _lora);

uint16_t lora_init(lora* _lora);
uint16_t lora_tx_mode_init(lora *_lora);
uint8_t lora_read_test(lora *_lora);

