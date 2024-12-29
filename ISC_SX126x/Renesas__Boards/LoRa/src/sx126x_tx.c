#include "sx126x.h"
#include "sx126x_context.h"
#include "sx126x_hal.h"
#include "sx126x_tx.h"
#include "hal_data.h"

uint8_t _bufferIndex = 0;
uint8_t _payloadTxRx = 0;
uint8_t sf = 8;      // LoRa spreading factor: 7
uint32_t bw = 31250; // Bandwidth: 125 kHz
uint8_t cr = 5;      // Coding rate: 4/5
bool ldro = true;
uint8_t headerType = SX126X_HEADER_EXPLICIT; // Explicit header mode
uint16_t preambleLength = 8;                 // Set preamble length to 12
uint8_t payloadLength = 7;                   // Initialize payloadLength to 15
bool crcType = true;                         // Set CRC enable
bool invertIq = false;
int _dio = SX126X_PIN_RF_IRQ;
volatile uint16_t _statusIrq = 0xFFFF;
uint8_t _statusWait;
uint8_t _transmitTime;
void setDio3TcxoCtrl(uint8_t tcxo_voltage, uint32_t timeout)
{
    sx126x_set_dio3_as_tcxo_ctrl(&context, tcxo_voltage, timeout);
    sx126x_set_standby(&context, SX126X_STANDBY_CFG_RC);    
    sx126x_cal(&context, 0xFF);
}

void write(char *data, uint8_t length)
{
    _bufferIndex = 0;
    _payloadTxRx = 0;
    // write multiple bytes of package to be transmitted for char type
    uint8_t *data_ = (uint8_t *)data;
    sx126x_writeBuffer(_bufferIndex, data_, length);
    _bufferIndex += length;
    _payloadTxRx += length;
}

void write_count(uint8_t data)
{
    // write single byte of package to be transmitted
    _bufferIndex = 0;
    sx126x_writeBuffer( _bufferIndex, &data, 1);
    _bufferIndex++;
    _payloadTxRx++;
}

uint8_t getMode()
{
    uint8_t mode;
    sx126x_get_status(&context, &mode);
    return mode & 0x70;
}

bool begin()
{
    sx126x_hal_reset(&context);
    sx126x_set_standby(&context, SX126X_STANDBY_CFG_RC);
    if (getMode() != SX126X_STATUS_MODE_STDBY_RC)
    {
        // return false;
    }
    sx126x_set_pkt_type(&context, SX126X_PKT_TYPE_LORA);
    sx126x_cfg_tx_clamp(&context);
    return true;
}

void setFrequency(uint32_t frequency)
{
    uint8_t calFreq[2];
    if (frequency < 446000000)
    { // 430 - 440 Mhz
        calFreq[0] = SX126X_CAL_IMG_430;
        calFreq[1] = SX126X_CAL_IMG_440;
    }
    else if (frequency < 734000000)
    { // 470 - 510 Mhz
        calFreq[0] = SX126X_CAL_IMG_470;
        calFreq[1] = SX126X_CAL_IMG_510;
    }
    else if (frequency < 828000000)
    { // 779 - 787 Mhz
        calFreq[0] = SX126X_CAL_IMG_779;
        calFreq[1] = SX126X_CAL_IMG_787;
    }
    else if (frequency < 877000000)
    { // 863 - 870 Mhz
        calFreq[0] = SX126X_CAL_IMG_863;
        calFreq[1] = SX126X_CAL_IMG_870;
    }
    else if (frequency < 1100000000)
    { // 902 - 928 Mhz
        calFreq[0] = SX126X_CAL_IMG_902;
        calFreq[1] = SX126X_CAL_IMG_928;
    }
    // calculate frequency for setting configuration
    uint32_t rfFreq = ((uint64_t)frequency << SX126X_RF_FREQUENCY_SHIFT) / SX126X_RF_FREQUENCY_XTAL;
    // perform image calibration before set frequency
    sx126x_cal_img(&context, calFreq[0], calFreq[1]);
    sx126x_set_rf_freq(&context, 915000000);
}

void setTxPower(uint8_t txPower, uint8_t version)
{
    // maximum TX power is 22 dBm and 15 dBm for SX1261
    if (txPower > 22)
        txPower = 22;
    else if (txPower > 15 && version == SX126X_TX_POWER_SX1261)
        txPower = 15;

    uint8_t paDutyCycle = 0x00;
    uint8_t hpMax = 0x00;
    uint8_t deviceSel = version == SX126X_TX_POWER_SX1261 ? 0x01 : 0x00;
    uint8_t power = 0x0E;
    // set parameters for PA config and TX params configuration
    if (txPower == 22)
    {
        paDutyCycle = 0x04;
        hpMax = 0x07;
        power = 0x16;
    }
    else if (txPower >= 20)
    {
        paDutyCycle = 0x03;
        hpMax = 0x05;
        power = 0x16;
    }
    else if (txPower >= 17)
    {
        paDutyCycle = 0x02;
        hpMax = 0x03;
        power = 0x16;
    }
    else if (txPower >= 14 && version == SX126X_TX_POWER_SX1261)
    {
        paDutyCycle = 0x04;
        hpMax = 0x00;
        power = 0x0E;
    }
    else if (txPower >= 14 && version == SX126X_TX_POWER_SX1262)
    {
        paDutyCycle = 0x02;
        hpMax = 0x02;
        power = 0x16;
    }
    else if (txPower >= 14 && version == SX126X_TX_POWER_SX1268)
    {
        paDutyCycle = 0x04;
        hpMax = 0x06;
        power = 0x0F;
    }
    else if (txPower >= 10 && version == SX126X_TX_POWER_SX1261)
    {
        paDutyCycle = 0x01;
        hpMax = 0x00;
        power = 0x0D;
    }
    else if (txPower >= 10 && version == SX126X_TX_POWER_SX1268)
    {
        paDutyCycle = 0x00;
        hpMax = 0x03;
        power = 0x0F;
    }
    else
    {
        return;
    }
    const sx126x_pa_cfg_params_t pa_cfg = {
        .pa_duty_cycle = paDutyCycle,
        .hp_max = hpMax,
        .device_sel = deviceSel,
        .pa_lut = 0x01,
    };
    // set power amplifier and TX power configuration
    sx126x_set_pa_cfg(&context, &pa_cfg);
    sx126x_set_tx_params(&context, power, SX126X_PA_RAMP_800U);
}

void setLoRaModulation(uint8_t sf, uint32_t bw, uint8_t cr, bool ldro)
{

    // valid spreading factor is between 5 and 12
    if (sf > 12)
        sf = 12;
    else if (sf < 5)
        sf = 5;
    // select bandwidth options
    if (bw < 9100)
        bw = SX126X_BW_7800; // 7.8 kHz
    else if (bw < 13000)
        bw = SX126X_BW_10400; // 10.4 kHz
    else if (bw < 18200)
        bw = SX126X_BW_15600; // 15.6 kHz
    else if (bw < 26000)
        bw = SX126X_BW_20800; // 20.8 kHz
    else if (bw < 36500)
        bw = SX126X_BW_31250; // 31.25 kHz
    else if (bw < 52100)
        bw = SX126X_BW_41700; // 41.7 kHz
    else if (bw < 93800)
        bw = SX126X_BW_62500; // 62.5 kHz
    else if (bw < 187500)
        bw = SX126X_BW_125000; // 125 kHz
    else if (bw < 375000)
        bw = SX126X_BW_250000; // 250 kHz
    else
        bw = SX126X_BW_500000; // 500 kHz
    // valid code rate denominator is between 4 and 8
    cr -= 4;
    if (cr > 4)
        cr = 0;
    const sx126x_mod_params_lora_t mod_param = {
        .bw = bw,
        .cr = cr,
        .sf = sf,
        .ldro = ldro,
    };
    sx126x_set_lora_mod_params(&context, &mod_param);
}

void sx126x_fixInvertedIq(uint8_t invertIq)
{
    uint8_t value;
    sx126x_read_register(&context, SX126X_REG_IQ_POLARITY_SETUP, &value, 1);
    if (invertIq)
        value |= 0x04;
    else
        value &= 0xFB;
    sx126x_write_register(&context, SX126X_REG_IQ_POLARITY_SETUP, &value, 1);
}

void setLoRaPacket(uint8_t headerType, uint16_t preambleLength, uint8_t payloadLength, bool crcType, bool invertIq)
{

    // filter valid header type config
    if (headerType != SX126X_HEADER_IMPLICIT)
        headerType = SX126X_HEADER_EXPLICIT;
    const sx126x_pkt_params_lora_t val = {
        .header_type = headerType,              // Explicit header mode
        .preamble_len_in_symb = preambleLength, // Set preamble length to 12
        .pld_len_in_bytes = payloadLength,      // Initialize payloadLength to 15
        .crc_is_on = crcType,                   // Set CRC enable
    };
    sx126x_set_lora_pkt_params(&context, &val);
    // sx126x_fixInvertedIq((uint8_t)invertIq);
}

void setSyncWord(uint16_t syncWord)
{
    uint8_t buf[2];
    buf[0] = syncWord >> 8;
    buf[1] = syncWord & 0xFF;
    if (syncWord <= 0xFF)
    {
        buf[0] = (syncWord & 0xF0) | 0x04;
        buf[1] = (syncWord << 4) | 0x04;
    }
    sx126x_write_register(&context, SX126X_REG_LORA_SYNC_WORD_MSB, buf, 2);
}

void sx126x_fixLoRaBw500(uint32_t bw)
{
    uint8_t packetType;
    sx126x_get_pkt_type(&context, &packetType);
    uint8_t value;
    sx126x_read_register(&context, SX126X_REG_TX_MODULATION, &value, 1);
    if ((packetType == SX126X_PKT_TYPE_LORA) && (bw == 500000))
        value &= 0xFB;
    else
        value |= 0x04;
    sx126x_write_register(&context, SX126X_REG_TX_MODULATION, &value, 1);
}

void beginPacket()
{
    // reset payload length and buffer index
    _payloadTxRx = 0;
    _bufferIndex = 0;
    sx126x_set_buffer_base_address(&context, _bufferIndex, _bufferIndex + 0xFF);
    int8_t _pinToLow = -1;

    // set txen pin to low and rxen pin to high
    if ((MISO != -1) && (MOSI != -1))
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, MISO, BSP_IO_LEVEL_LOW);
        R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_HIGH);
        _pinToLow = MOSI;
    }
    uint32_t _bw = 31250;
    sx126x_fixLoRaBw500(_bw);
}

void sx126x_writeBuffer(uint8_t offset, uint8_t *data, uint8_t nData)
{
    uint8_t nBuf = nData + 1;
    uint8_t buf[nBuf];
    buf[0] = 0X0E;
    for (uint8_t i = 0; i < nData; i++)
        buf[i + 1] = data[i];
    sx126x_hal_write(&context, buf, nBuf,NULL,0);
}
// void _irqSetup(uint16_t irqMask)
// {
//     // clear IRQ status of previous transmit or receive operation
//     sx126x_clear_irq_status(&context, 0x03FF);

//     // set selected interrupt source
//     uint16_t dio1Mask = 0x0000;
//     uint16_t dio2Mask = 0x0000;
//     uint16_t dio3Mask = 0x0000;
//     if (_dio == 2)
//         dio2Mask = irqMask;
//     else if (_dio == 3)
//         dio3Mask = irqMask;
//     else
//         dio1Mask = irqMask;
//     sx126x_set_dio_irq_params(&context, irqMask, dio1Mask, dio2Mask, dio3Mask);
// }

// unsigned long millis()
//{
//     unsigned long m;
//     uint8_t oldSREG = SREG;
//
//     // disable interrupts while we read timer0_millis or we might get an
//     // inconsistent value (e.g. in the middle of a write to timer0_millis)
//     cli();
//     m = timer0_millis;
//     // uint8_t SREG = oldSREG;
//
//     return m;
// }

bool endPacket(uint32_t timeout)
{
    // skip to enter TX mode when previous TX operation incomplete
    if (getMode() == SX126X_STATUS_MODE_TX)
    {
        return false;
    }
    // clear previous interrupt and set TX done, and TX timeout as interrupt source
    // _irqSetup(SX126X_IRQ_TX_DONE | SX126X_IRQ_TIMEOUT);
    // set packet payload length
    setLoRaPacket(headerType, preambleLength, payloadLength, crcType, invertIq);

    // set status to TX wait
    _statusWait = LORA_STATUS_TX_WAIT;
    volatile static uint16_t _statusIrq = 0x0000;
    // calculate TX timeout config
    uint32_t txTimeout = timeout << 6;
    if (txTimeout > 0x00FFFFFF)
    {
        txTimeout = SX126X_TX_SINGLE;
    }

    // set device to transmit mode with configured timeout or single operation
    sx126x_set_tx(&context, timeout);
    // _transmitTime = millis();

    // set operation status to wait and attach TX interrupt handler
    /*== if (_irq != -1)
    {
        attachInterrupt(_irqStatic, SX126x::_interruptTx, RISING);
    }
    return true;*/
}
void sx126x_fixRxTimeout()
{
    uint8_t value = 0x00;
    sx126x_write_register(&context, SX126X_REG_RTC_CONTROL, &value, 1);
    sx126x_read_register(&context, SX126X_REG_EVENT_MASK, &value, 1);
    value = value | 0x02;
    sx126x_write_register(&context, SX126X_REG_EVENT_MASK, &value, 1);
}
void yield(void);
/* bool wait(uint32_t timeout)
{
    // immediately return when currently not waiting transmit or receive process
    if (_statusIrq)
        return true;

    // wait transmit or receive process finish by checking interrupt status or IRQ status
    uint16_t irqStat = 0x0000;
    uint32_t t = millis();
    while (irqStat == 0x0000 && _statusIrq == 0x0000)
    {
        // only check IRQ status register for non interrupt operation
        // if (_irq == -1) sx126x_getIrqStatus(&irqStat);
        // return when timeout reached
        if (millis() - t > timeout && timeout != 0)
            return false;
        yield();
    }

    if (_statusIrq)
    {
        // immediately return when interrupt signal hit
        return true;
    }
    else if (_statusWait == LORA_STATUS_TX_WAIT)
    {
        // for transmit, calculate transmit time and set back txen pin to low
        _transmitTime = millis() - _transmitTime;
        if (MOSI != -1)
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_LOW);
        }
    }
    else if (_statusWait == LORA_STATUS_RX_WAIT)
    {
        const sx126x_rx_buffer_status_t buf = {
            .pld_len_in_bytes = _payloadTxRx,
            .buffer_start_pointer = _bufferIndex,
        };
        // for receive, get received payload length and buffer index and set back rxen pin to low
        sx126x_get_rx_buffer_status(&context, &buf);
        if (MISO != -1)
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, MOSI, BSP_IO_LEVEL_HIGH);
        }
        sx126x_fixRxTimeout();
    }
    else if (_statusWait == LORA_STATUS_RX_CONTINUOUS)
    {
        // for receive continuous, get received payload length and buffer index and clear IRQ status
        const sx126x_rx_buffer_status_t buf = {
            .pld_len_in_bytes = _payloadTxRx,
            .buffer_start_pointer = _bufferIndex,
        };
        sx126x_get_rx_buffer_status(&context, &buf);
        sx126x_clear_irq_status(&context, 0x03FF);
    }

    // store IRQ status
    _statusIrq = irqStat;
    return true;
}    */

void tx_setup()
{
    // printk("Begin LoRa radio\n\r");
    //    R_IOPORT_PinCfg(&g_ioport_ctrl, MOSI,BSP_IO_DIRECTION_OUTPUT);
    //    R_IOPORT_PinCfg(&g_ioport_ctrl, MISO,BSP_IO_DIRECTION_OUTPUT);
    if (!begin())
    {
        // printk("Something wrong, can't begin LoRa radio\n\r");
        //        while (1);
    }
    // Optionally configure TCXO or XTAL used in RF module
    // Different RF module can have different clock, so make sure clock source is configured correctly
    // uncomment code below to use TCXO
    // printk("Set RF module to use TCXO as clock reference\n\r");
    uint8_t tcxo_voltage = SX126X_TCXO_CTRL_1_8V;
    uint32_t timeout = SX126X_TCXO_DELAY_10;
    setDio3TcxoCtrl(tcxo_voltage, timeout);
    // uncomment code below to use XTAL
    // uint8_t xtalA = 0x12;
    // uint8_t xtalB = 0x12;
    // Serial.println("Set RF module to use XTAL as clock reference");
    // LoRa.setXtalCap(xtalA, xtalB);

    // Optionally configure DIO2 as RF switch control
    // This is usually used for a LoRa module without TXEN and RXEN pins
    // LoRa.setDio2RfSwitch(true);

    // Set frequency to 915 Mhz
    // printk("Set frequency to 915 Mhz\n\r");

    setFrequency(868000000);

    // Set TX power, default power for SX1262 and SX1268 are +22 dBm and for SX1261 is +14 dBm
    // This function will set PA config with optimal setting for requested TX power
    // printk("Set TX power to +17 dBm\n\r");
    setTxPower(22, SX126X_TX_POWER_SX1262);
    // Configure modulation parameter including spreading factor (SF), bandwidth (BW), and coding rate (CR)
    // Receiver must have same SF and BW setting with transmitter to be able to receive LoRa packet
    // printk("Set modulation parameters:\n\tSpreading factor = 7\n\tBandwidth = 125 kHz\n\tCoding rate = 4/5");

    setLoRaModulation(sf, bw, cr, ldro);

    // Configure packet parameter including header type, preamble length, payload length, and CRC type
    // The explicit packet includes header contain CR, number of byte, and CRC type
    // Receiver can receive packet with different CR and packet parameters in explicit header mode
    // printk("Set packet parameters:\n\tExplicit header type\n\tPreamble length = 12\n\tPayload Length = 15\n\tCRC on");

    setLoRaPacket(headerType, preambleLength, payloadLength, crcType, invertIq);

    // Set syncronize word for public network (0x3444)
    // printk("Set syncronize word to 0x3444\n\r");
    setSyncWord(0x3444);

    // printk("\n-- LORA TRANSMITTER --\n");
}
char message[] = "HeLoRa World!";
uint8_t nBytes = sizeof(message);
uint8_t counter = 0;

void tx_loop()
{

    // Transmit message and counter
    // write() method must be placed between beginPacket() and endPacket()
    beginPacket();
    write(message, nBytes);
    write_count(counter);
    endPacket(0x000000);

    // Don't load RF module with continous transmit
    R_BSP_SoftwareDelay(2000, BSP_DELAY_UNITS_MILLISECONDS);
}
