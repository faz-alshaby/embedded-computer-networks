/*
 * a_traffic_lights.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to GPIO PA8
gpio_pin_t red_led = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t amber_led = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t green_led = {PB_15, GPIOB, GPIO_PIN_15};

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
  init_gpio(red_led, OUTPUT);
	init_gpio(amber_led, OUTPUT);
	init_gpio(green_led, OUTPUT);
  
  // loop forever ...
  while(1)
  {
    // turn green on LED		
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		// wait for 3 seconds
    HAL_Delay(5000);
    // turn green off LED
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		
		// turn amber on LED		
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		// wait for 3 seconds
    HAL_Delay(1000);
    // turn amber off LED
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		
		// turn red on LED		
		HAL_GPIO_WritePin ( GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
		// wait for 3 seconds
    HAL_Delay(5000);
			// turn amber on LED		
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(500);
		// turn amber off LED
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    // turn red off LED
		HAL_GPIO_WritePin ( GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);
		
		// turn amber on LED		
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		// wait for 3 seconds
    HAL_Delay(500);
    // turn amber off LED
		HAL_GPIO_WritePin ( GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		
		
  }
}

