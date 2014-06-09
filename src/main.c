#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"

int main(void)
{
  // flash LED_0 and LED_1 alternately
  nrf_gpio_cfg_output(LED_RED);
  nrf_gpio_cfg_output(LED_GREEN);
  
  while(true)
  {

    nrf_gpio_pin_clear(LED_RED);
    nrf_gpio_pin_set(LED_GREEN);
    nrf_delay_us(1000000);
    nrf_gpio_pin_clear(LED_GREEN);
    nrf_gpio_pin_set(LED_RED);
    nrf_delay_us(1000000);
  }
}
