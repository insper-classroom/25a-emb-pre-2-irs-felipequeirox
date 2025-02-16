#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

const int LED_PIN_R = 4;
const int LED_PIN_G = 6;

volatile int btn_flag_red = 0;
volatile int btn_flag_green = 0;

void btn_callback(uint gpio, uint32_t events) {
  
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R) {
      btn_flag_red = !btn_flag_red;
    } 
  }
  
  else if (events == 0x8) { // rise edge
    if (gpio == BTN_PIN_G){
      btn_flag_green = !btn_flag_green; 
    }
  } 

}


int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);


  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

  while (true) {
    gpio_put(LED_PIN_R, btn_flag_red);
    gpio_put(LED_PIN_G, btn_flag_green);
    sleep_ms(50);
  }
}
