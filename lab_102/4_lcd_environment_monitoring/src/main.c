// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"
// LCD DEFINES

// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] =
{
	"*     Hello LCD World!     *",
	"*      Welcome to SHU      *"
};

// Initil pin for LDR
gpio_pin_t temp_sensor = {PF_6, GPIOF, GPIO_PIN_6};
gpio_pin_t LDR = {PA_0, GPIOA, GPIO_PIN_0};

// this is the main method
int main()
{
	// we need to initialise the hal library and set up the SystemCoreClock
	// properly
	HAL_Init();
	init_sysclk_216MHz();

	// init the adc here
	init_adc(temp_sensor);
	init_adc(LDR);
	
	// initialise the lcd
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	// set the background colour to black and clear the lcd
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	// set the font to use
	BSP_LCD_SetFont(&Font24);

	// print the welcome message ...
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
	BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
	BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
	BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER);

	// delay a little ...
	HAL_Delay(5000);
	
	while(1)
	{
		uint16_t adc_val = read_adc(temp_sensor);
		float voltage = (3.3 * (adc_val / 4095.0)) * 1000;
		float temperature = (voltage  - 500) / 10.0;

		// format a string based around the uptime counter
		char str[25];
		sprintf(str, "Current uptime = %u", (HAL_GetTick() / 1000));
		BSP_LCD_ClearStringLine(5);
		BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str);
		char stradc[25];
		sprintf(stradc, "Temperature = %3.2f", temperature);
		BSP_LCD_ClearStringLine(6);
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)stradc);

		uint16_t LDR_val = read_adc(LDR);
		float LDR_voltage = (3.3 * (LDR_val / 4095.0)) * 1000;
		char stradc2[25];
		sprintf(stradc2, "LDR volts = %3.2f", LDR_voltage);
		BSP_LCD_ClearStringLine(8);
		BSP_LCD_DisplayStringAtLine(8, (uint8_t *)stradc2);
		
		HAL_Delay(1000);


	}
}

