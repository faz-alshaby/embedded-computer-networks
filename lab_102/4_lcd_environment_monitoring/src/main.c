// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"
#include "gpio.h"

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
gpio_pin_t calibration_led = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led = {PI_2, GPIOI, GPIO_PIN_2};

// calibration values for LDR
int sensorMin = 4095;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value

// this is the main method
int main()
{
	// turn on LED to signal the start of the calibration period:
	init_gpio(calibration_led, OUTPUT);
	init_gpio(led, OUTPUT);
	
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

	//// delay a little ...
	//HAL_Delay(5000);
	
	// calibrate ... 
  write_gpio(calibration_led, HIGH);
	long prev_time = HAL_GetTick();
	while(HAL_GetTick() - prev_time < 5000)
	{		
		// read the adc
		uint16_t reading = read_adc(LDR);
		
		// check against min and max
		if(reading > sensorMax)
		{
			sensorMax = reading;
		}
		if(reading < sensorMin)
		{
			sensorMin = reading;
		}		
	}
  write_gpio(calibration_led, LOW);
	
	// main loop
	while(1)
	{	
		// UPTIME
		
		// format a string based around the uptime counter
		char str[25];
		sprintf(str, "Current uptime = %u", (HAL_GetTick() / 1000));
		BSP_LCD_ClearStringLine(5);
		BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str);
		
		// TEMPERATURE
		
		// read and convert
		uint16_t adc_val = read_adc(temp_sensor);
		float voltage = (3.3 * (adc_val / 4095.0)) * 1000;
		float temperature = (voltage  - 500) / 10.0;
		
		// display
		char strtmp[25];
		sprintf(strtmp, "Temperature = %3.2f", temperature);
		BSP_LCD_ClearStringLine(6);
		BSP_LCD_DisplayStringAtLine(6, (uint8_t *)strtmp);

		// LIGHT
		
		// read and remap to a percentage
		uint16_t LDR_val = read_adc(LDR);
		float ldr_percent = ((LDR_val - sensorMin) / (float)(sensorMax - sensorMin)) * 100;
		// float LDR_voltage = (3.3 * (LDR_val / 4095.0)) * 1000;
		
		// constrain to between 0 and 100 ...
		// 
		if ((ldr_percent) < 0)
			{
			ldr_percent = 0;
		}
			else if ((ldr_percent) > 100)
			{
				ldr_percent = 100;
			}
			else if ((ldr_percent) >0 & (ldr_percent)  <50)
			{
				write_gpio(led, HIGH);
			}
			else if ((ldr_percent) >50 & (ldr_percent)  <=100)
			{
				write_gpio(led, LOW);
			}
			else
			{
				;
			}
			
		
		// display
		char strldr[25];
		sprintf(strldr, "LDR         = %3.2f %%", ldr_percent);
		BSP_LCD_ClearStringLine(8);
		BSP_LCD_DisplayStringAtLine(8, (uint8_t *)strldr);
		
		HAL_Delay(100);


	}
}

