#ifndef LORA_DEFS_H
#define LORA_DEFS_H

// LoRa Bandwidth
#define LORA_BW_0200 0x00
#define LORA_BW_0400 0x01
#define LORA_BW_0800 0x02
#define LORA_BW_1600 0x03
#define LORA_BW_1600K LORA_BW_1600 // optional alias

// LoRa Spreading Factors
#define LORA_SF5  0x05
#define LORA_SF6  0x06
#define LORA_SF7  0x07
#define LORA_SF8  0x08
#define LORA_SF9  0x09
#define LORA_SF10 0x0A
#define LORA_SF11 0x0B
#define LORA_SF12 0x0C

// LoRa Coding Rates
#define LORA_CR_4_5       0x01
#define LORA_CR_4_6       0x02
#define LORA_CR_4_7       0x03
#define LORA_CR_4_8       0x04
#define LORA_CR_LI_4_5    0x05
#define LORA_CR_LI_4_6    0x06
#define LORA_CR_LI_4_7    0x07

#endif // LORA_DEFS_H