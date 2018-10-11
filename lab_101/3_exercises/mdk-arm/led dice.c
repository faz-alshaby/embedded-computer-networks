// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"
#include "random_numbers.h"

// map the led to GPIO PA8
gpio_pin_t button = {PI_2, GPIOI, GPIO_PIN_2};
gpio_pin_t red_led = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t red_led2 = {PB_8, GPIOB, GPIO_PIN_8};
gpio_pin_t red_led3 = {PB_9, GPIOB, GPIO_PIN_9};
gpio_pin_t red_led4 = {PB_4, GPIOB, GPIO_PIN_4};
gpio_pin_t red_led5 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t red_led6 = {PB_15, GPIOB, GPIO_PIN_15};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
	// Now contained in a separate "clock" library to avoid repetition
	
	// Now contained in a separate "gpio" library to avoid repetition
  init_sysclk_216MHz();
  
  // initialise the gpio pins
	init_gpio(button, INPUT);
  init_gpio(red_led, OUTPUT);
	init_gpio(red_led2, OUTPUT);
	init_gpio(red_led3, OUTPUT);
	init_gpio(red_led4, OUTPUT);
	init_gpio(red_led5, OUTPUT);
	init_gpio(red_led6, OUTPUT);
  
  // loop forever ...
  while(1)
  {
		uint32_t rnd = (get_random_int() % 6) + 1;
    
						
  }
}

