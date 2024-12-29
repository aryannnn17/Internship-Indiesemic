#include "sx126x.h"
#include "sx126x_hal.h"
#include "sx126x_regs.h"
#include "sx126x_rx_driver.h"
#define SX126X_STATUS_MODE_STDBY_RC 0x20 // current chip mode: STDBY_RC

void setDio3TcxoCtrl(uint8_t tcxo_voltage, uint32_t timeout);
void tx_setup();
void tx_loop();
void write(char* data, uint8_t length);
uint8_t getMode();
bool begin();