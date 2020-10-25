#include "adc.h"

void ADC_init() {
    // AIN4, channel select
    ADC1_CSR |= 4;
    //right data align
    ADC1_CR2 |= (1 << ADC1_CR2_ALIGN);
    //Wake ADC from power down
    ADC1_CR1 |= 1 << ADC1_CR1_ADON;
}
uint16_t ADC_read() {
  uint8_t adcH, adcL;
  ADC1_CR1 |= (1 << ADC1_CR1_ADON);
  while (!(ADC1_CSR & (1 << ADC1_CSR_EOC)));
  adcL = ADC1_DRL;
  adcH = ADC1_DRH;
  ADC1_CSR &= ~(1 << ADC1_CSR_EOC); // Clear EOC flag
  return (adcL | (adcH << 8));
}
