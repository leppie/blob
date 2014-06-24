#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "app_gpiote.h"
#include "nrf_error.h"
#include "boards.h"

#define OUT_PIN 0
#define IN_PIN 1

static app_gpiote_user_id_t           m_gpiote_user_id;            /**< GPIOTE user id for buttons module. */

void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    nrf_gpio_pin_clear(LED_RED);

    // This call can be used for debug purposes during application development.
    // @note CAUTION: Activating this code will write the stack to flash on an error.
    //                This function should NOT be used in a final product.
    //                It is intended STRICTLY for development/debugging purposes.
    //                The flash write will happen EVEN if the radio is active, thus interrupting
    //                any communication.
    //                Use with care. Un-comment the line below to use.
    //ble_debug_assert_handler(error_code, line_num, p_file_name);

    // On assert, the system can only recover on reset.
    NVIC_SystemReset();
}

/**@brief Function for handling the GPIOTE event.
 *
 * @details Saves the current status of the button pins, and starts a timer. If the timer is already
 *          running, it will be restarted.
 *
 * @param[in]  event_pins_low_to_high   Mask telling which pin(s) had a low to high transition.
 * @param[in]  event_pins_high_to_low   Mask telling which pin(s) had a high to low transition.
 */
static void gpiote_event_handler(uint32_t event_pins_low_to_high, uint32_t event_pins_high_to_low)
{
	if (event_pins_high_to_low)
	{
		nrf_gpio_pin_set(OUT_PIN);
		nrf_gpio_pin_set(LED_BLUE);
	}
	else
	{
		nrf_gpio_pin_clear(OUT_PIN);
		nrf_gpio_pin_clear(LED_BLUE);
	}
}

/**@brief Function for the Power manager.
 */
static void power_manage(void)
{
    //uint32_t err_code = sd_app_evt_wait();
    //APP_ERROR_CHECK(err_code);

}

int main(void)
{
  // flash LED_0 and LED_1 alternately
  nrf_gpio_cfg_output(LED_RED);
  nrf_gpio_cfg_output(LED_GREEN);
  nrf_gpio_cfg_output(LED_BLUE);

  nrf_gpio_cfg_output(OUT_PIN);
  nrf_gpio_cfg_input(IN_PIN, NRF_GPIO_PIN_NOPULL);


  APP_GPIOTE_INIT(1);
  app_gpiote_user_register(&m_gpiote_user_id, 1 << IN_PIN, 1 << IN_PIN, gpiote_event_handler);
  app_gpiote_user_enable(m_gpiote_user_id);

  
  while(true)
  {
	power_manage();
/*
    nrf_gpio_pin_clear(LED_RED);
    nrf_gpio_pin_set(LED_GREEN);
    nrf_delay_us(1000000);
    nrf_gpio_pin_clear(LED_GREEN);
    nrf_gpio_pin_set(LED_RED);
    nrf_delay_us(1000000);
*/
	  nrf_delay_ms(1000);
  }
}
