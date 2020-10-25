#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "stm8s003.h"
#include "uart.h"
#include "stm8_utility.h"
#include "adc.h"

int putchar(int c) {
    uart_write(c);
    return 0;
}

//PWM -> PA3 -> TIM2_CH3
//MODE_SELECT -> PC4
//PC5 -> STATUS
//PC6 -> OFF
//PC7 -> ON
//PD3 -> POT

void timer_init() {
  PA_DDR |= _BV(3);//PA3 output
  PA_CR1 |= _BV(3);

  TIM2_PSCR = 4; // 2^8=256 -> 16MHz / 256 = 62.5Khz -> 62.5Khz / 1024 = 61Hz

  TIM2_ARRH = 16000 >> 8;
  TIM2_ARRL = 16000 & 0xff; //Max / Top

  TIM2_CCR3H = 1000 >> 8;
  TIM2_CCR3L = 1000 & 0xff; //LOW

  TIM2_CR1 |= _BV(TIM2_CR1_CEN);

  TIM2_CCMR3 |= _BV(5) | _BV(6); //pwm mode 1 //bita 0 in 1 moreta bit na nic ce ces met izhod
  TIM2_CCER2 |= _BV(0);
}
void set_timer(uint16_t val) {
  val = 1000 + val;

  TIM2_CCR3H = val >> 8;
  TIM2_CCR3L = val & 0xff;
}


int main () {
    CLK_CKDIVR = 0;//16mhz
    //enable_interrupts();

    ADC_init();
    timer_init();


    //Main loop
    while(1) {
      static uint16_t last_pot_value;
      uint16_t pot_value = ADC_read();
      if(pot_value != last_pot_value) {
        last_pot_value = pot_value;
        set_timer(pot_value); //ADC ma 10b resolucijo -> max vrednost 1023
      }
    }
}
