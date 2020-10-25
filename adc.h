#ifndef STM8_ADC_H
#define STM8_ADC_H

#include "stm8s003.h"
#include <stdint.h>

void ADC_init();
uint16_t ADC_read();

#endif
