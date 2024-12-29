#include "sx126x.h"
#include "sx126x_context.h"
#include "sx126x_hal.h"
#include "sx126x_regs.h"
#include "hal_data.h"
#define SX126X_POWER_SAVING_GAIN 0x94 // power saving gain register value
#define SX126X_BOOSTED_GAIN 0x96      // boosted gain register value
#define HEX 16
#define RISING 3
// Pin setting
int8_t nssPin = 10, resetPin = 9, busyPin = 4, irqPin = 2, rxenPin = 7, txenPin = 8;

// Clock reference setting. RF module using either TCXO or XTAL as clock reference
// uncomment code below to use XTAL
// #define SX126X_XTAL
// uint8_t xtalCap[2] = {0x12, 0x12};
// uncomment code below to use TCXO
#define SX126X_TCXO
uint8_t tcxo_voltage = SX126X_TCXO_CTRL_1_8V;
uint32_t timeout = SX126X_TCXO_DELAY_10;

// Configure DIO2 as RF switch control or using TXEN and RXEN pin
#define SX126X_USING_TXEN_RXEN
// RF frequency setting
uint32_t rfFrequency = 915000000UL;
// RX gain setting
uint8_t gain = SX126X_POWER_SAVING_GAIN;

// Define modulation parameters setting
const sx126x_mod_params_lora_t param = {
    .sf = SX126X_LORA_SF7,    // LoRa spreading factor: 7
    .bw = SX126X_LORA_BW_125, // Bandwidth: 125 kHz
    .cr = SX126X_LORA_CR_4_5, // Coding rate: 4/5
    .ldro = 0x00,             // low data rate optimize off
};

// Define packet parameters setting
const sx126x_pkt_params_lora_t val = {
    .header_type = SX126X_LORA_PKT_EXPLICIT, // Explicit header mode
    .preamble_len_in_symb = 12,              // Set preamble length to 12
    .pld_len_in_bytes = 64,                  // Initialize payloadLength to 15
    .crc_is_on = true,                       // Set CRC enable
    .invert_iq_is_on = true,
};

// SyncWord setting
uint8_t sw[2] = {0x34, 0x44};

volatile bool received = false;

void checkReceiveDone()
{
    received = true;
}

void settingFunction()
{
    printk("-- SETTING FUNCTION --\n\r");

    // Set to standby mode
    sx126x_set_standby(&context, SX126X_STANDBY_CFG_RC);

    // Optionally configure TCXO or XTAL used in RF module
    printk("Set RF module to use TCXO as clock reference\n");
    sx126x_set_dio3_as_tcxo_ctrl(&context, tcxo_voltage, timeout);

    // Set packet type to LoRa
    printk("Set packet type to LoRa\n");
    sx126x_set_pkt_type(&context, SX126X_PKT_TYPE_LORA);

    // Set frequency to selected frequency (rfFrequency = rfFreq * 32000000 / 2 ^ 25)
    printk("Set frequency to \n");
    printk(rfFrequency / 1000000, "\n");
    printk(" Mhz\n");
    uint32_t rfFreq = ((uint64_t)rfFrequency * 33554432UL) / 32000000UL;
    sx126x_set_rf_freq(&context, rfFreq);

    // Set rx gain to selected gain
    printk("Set RX gain to \n");
    if (gain == SX126X_POWER_SAVING_GAIN)
        printk("power saving gain\n");
    else if (gain == SX126X_BOOSTED_GAIN)
        printk("boosted gain\n");
    sx126x_write_register(&context, SX126X_REG_RXGAIN, &gain, 1);

    // Configure modulation parameter with predefined spreading factor, bandwidth, coding rate, and low data rate optimize setting
    printk("Set modulation with predefined parameters\n");
    sx126x_set_lora_mod_params(&context, &param);

    // Configure packet parameter with predefined preamble length, header mode type, payload length, crc type, and invert iq option
    printk("Set packet with predefined parameters\n");
    sx126x_set_lora_pkt_params(&context, &val);

    // Set predefined syncronize word
    printk("Set syncWord to 0x\n");
    printk((sw[0] << 8) + sw[1], HEX);
    sx126x_write_register(&context, SX126X_REG_LR_SYNCWORD, sw, 2);
}

uint16_t receiveFunction(char *message, uint8_t *len, uint32_t timeout)
{
    printk("\n-- RECEIVE FUNCTION --\n");
    // Activate interrupt when receive done on DIO1
    printk("Set RX done, timeout, and CRC error IRQ on DIO1\n");
    uint16_t mask = SX126X_IRQ_RX_DONE | SX126X_IRQ_TIMEOUT | SX126X_IRQ_CRC_ERROR;
    sx126x_set_dio_irq_params(&context, mask, mask, SX126X_IRQ_NONE, SX126X_IRQ_NONE);
    // Attach irqPin to DIO1
    printk("Attach interrupt on IRQ pin\n");
    attachInterrupt(digitalPinToInterrupt(irqPin), checkReceiveDone, RISING);
// Set txen and rxen pin state for receiving packet
#ifdef SX126X_USING_TXEN_RXEN
    R_IOPORT_PinWrite(&g_ioport_ctrl, txenPin, BSP_IO_LEVEL_LOW);
    R_IOPORT_PinWrite(&g_ioport_ctrl, rxenPin, BSP_IO_LEVEL_HIGH);
#endif

    // Calculate timeout (timeout duration = timeout * 15.625 us)
    uint32_t tOut = timeout * 64;
    if (timeout == SX126X_RX_CONTINUOUS)
    {
        tOut = SX126X_RX_CONTINUOUS;
    }
    // Set RF module to RX mode to receive message
    printk("Receiving LoRa packet within predefined timeout\n");
    sx126x_set_rx(&context, tOut);

    // Wait for RX done interrupt
    printk("Wait for RX done interrupt\n");
    while (!received)
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    // Clear transmit interrupt flag
    received = false;

    // Clear the interrupt status
    uint16_t irqStat;
    sx126x_get_irq_status(&context, &irqStat);
    printk("Clear IRQ status\n");
    sx126x_get_and_clear_irq_status(&context, &irqStat);
#ifdef SX126X_USING_TXEN_RXEN
    R_IOPORT_PinWrite(&g_ioport_ctrl, rxenPin, BSP_IO_LEVEL_LOW);
#endif

    // Exit function if timeout reached
    if (irqStat & SX126X_IRQ_TIMEOUT)
        return irqStat;
    printk("Packet received!\n");

    // Get last received length and buffer base address
    printk("Get received length and buffer base address\n");
    uint8_t payloadLengthRx, rxStartBufferPointer;
    sx126x_get_rx_buffer_status(&context, &rxStartBufferPointer);
    uint8_t msgUint8[payloadLengthRx];

    // Get and display packet status
    printk("Get received packet status\n");
    sx126x_pkt_status_lora_t pkt;
    sx126x_get_lora_pkt_status(&context, &pkt);
    uint8_t rssiPkt, snrPkt, signalRssiPkt;
    float rssi = rssiPkt / -2;
    float snr = snrPkt / 4;
    float signalRssi = signalRssiPkt / -2;
    printk("Packet status: RSSI = ");
    printk(rssi, "\n");
    printk(" | SNR = ");
    printk(snr, "\n");
    printk(" | signalRSSI = ");
    printk(signalRssi, "\n");

    // Read message from buffer
    printk("Read message from buffer\n");
    printk("Message in bytes : [ ");
    sx126x_read_buffer(&context, rxStartBufferPointer, msgUint8, payloadLengthRx);
    len = payloadLengthRx;
    for (uint8_t i = 0; i < len; i++)
    {
        message[i] = (char)msgUint8[i];
        printk(msgUint8[i]);
        printk("  ");
    }
    printk("]\n");

    // return interrupt status
    return irqStat;
}

void rx_setup()
{
    // Settings for LoRa communication
    settingFunction();
}

void rx_loop()
{
    // Receive message
    char message[13];
    uint8_t length;
    uint32_t timeout = 5000; // 5000 ms timeout
    uint16_t status = receiveFunction(message, length, timeout);
    // Display message if receive success or display status if error
    if (status & SX126X_IRQ_RX_DONE)
    {
        printk("Message: \'");
        for (uint8_t i = 0; i < length; i++)
        {
            printk(message[i]);
        }
        printk("\'\n");
    }
    else if (status & SX126X_IRQ_TIMEOUT)
    {
        printk("Receive timeout\n");
    }
    else if (status & SX126X_IRQ_CRC_ERROR)
    {
        printk("CRC error\n");
    }
}
