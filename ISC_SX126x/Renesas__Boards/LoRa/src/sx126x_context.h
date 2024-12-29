#ifndef LORA_INC_LORA_H_
#define LORA_INC_LORA_H_


#define LORA_OK                     200
#define LORA_NOT_FOUND              404
#define LORA_LARGE_PAYLOAD          413
#define LORA_UNAVAILABLE            503



typedef struct lora_setting
{
    // Hardware setings:
    uint16_t CS_port;
    uint16_t CS_pin;
    uint16_t reset_port;
    uint16_t reset_pin;
    uint16_t DIO0_port;
    uint16_t DIO0_pin;
    uint16_t hSPIx;

    // Module settings:
    int current_mode;
    int frequency;
    int spredingFactor;
    int bandWidth;
    uint8_t crcRate;
    uint16_t preamble;
    uint8_t power;
    uint8_t overCurrentProtection;
}lora;

extern lora context;


#endif /*LORA_INC_LORA_H_*/
