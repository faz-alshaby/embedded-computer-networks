// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"
#include "random_numbers.h"

// map the led to GPIO
// button
gpio_pin_t button = {PB_4, GPIOB, GPIO_PIN_4};
// mid leds
gpio_pin_t mid_led1 = {PI_0, GPIOI, GPIO_PIN_0};
// center led
gpio_pin_t center_led2 = {PI_1, GPIOI, GPIO_PIN_1};
// bottom left, top right
gpio_pin_t botlftrt_led3 = {PI_2, GPIOI, GPIO_PIN_2};
// bottom right, top left
gpio_pin_t botrtlt_led4 = {PI_3, GPIOI, GPIO_PIN_3};

int buttonState;
// this is the main method
int main()
{
	// we need to initialise the hal library and set up the SystemCoreClock
	// properly
	HAL_Init();
	init_sysclk_216MHz();
	init_random();

	// initialise the gpio pins
	init_gpio(button, INPUT);
	init_gpio(mid_led1, OUTPUT);
	init_gpio(center_led2, OUTPUT);
	init_gpio(botlftrt_led3, OUTPUT);
	init_gpio(botrtlt_led4, OUTPUT);

	// loop forever ...
	while(1)
	{
		buttonState = (read_gpio(button));

		if(buttonState)
		{
			uint32_t rnd = (get_random_int() % 6) + 1;
			if(rnd == 1)
			{
				write_gpio(center_led2, HIGH);
				HAL_Delay(1000);
			}
			if(rnd == 2)
			{
				write_gpio(botlftrt_led3, HIGH);
				HAL_Delay(1000);
			}
			if(rnd == 3)
			{
				write_gpio(center_led2, HIGH);
				write_gpio(botlftrt_led3, HIGH);
				HAL_Delay(1000);
			}
			if(rnd == 4)
			{
				write_gpio(botrtlt_led4, HIGH);
				write_gpio(botlftrt_led3, HIGH);
				HAL_Delay(1000);
			}
			if(rnd == 5)
			{
				write_gpio(botrtlt_led4, HIGH);
				write_gpio(botlftrt_led3, HIGH);
				write_gpio(center_led2, HIGH);

				HAL_Delay(1000);
			}
			if(rnd == 6)
			{
				write_gpio(botrtlt_led4, HIGH);
				write_gpio(botlftrt_led3, HIGH);
				write_gpio(mid_led1, HIGH);
				HAL_Delay(1000);
			}
			// turn off LED
			write_gpio(mid_led1, LOW);
			write_gpio(center_led2, LOW);
			write_gpio(botlftrt_led3, LOW);
			write_gpio(botrtlt_led4, LOW);
		}
	}
}

