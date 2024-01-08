/*************************************************************************/
// Author        : Sherif Ashraf Khadr									 
// Project       : Atmega32_Drivers                                    	 
// File          : lcd_config.h                                  	     
// Date          : 12 Aug 2023	                                                                                                 */
// GitHub        : https://github.com/sherifkhadr             		     
/*************************************************************************/
#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

#include "../../MCAL/gpio/gpio_interface.h"

#define CLEAR_COMMAND	0x01

#define TWO_LINE_LCD_EIGHT_BIT_MODE		0x38
#define TWO_LINE_LCD_FOUR_BIT_MODE		0x2C

#define CURSOR_ON	0x0E
#define CURSOR_OFF 	0x0C
#define SET_CURSOR_LOCATION		0x80
#define SET_CGRAM_LOCATION		0x40

#define MAX_NUMBER_OF_COLUMNS		16
#define ROW_ZERO					0
#define ROW_ONE					1

#define RIGHT  0x1C
#define LEFT   0x18

#define FUNCTION_SET	0b00101000
#define DISPLAY_ON_OFF	0b00001111
#define DISPLAY_CLR		0b00000001
#define ENTRY_MODE		0b00000110



typedef enum
{
	HLCD_OK = 0,
	HLCD_NOK,
	HLCD_PTR_NULL,
	HLCD_INVALID_DATA_BIT_MODE,
	HLCD_INVALID_PARAMTERS
}EN_HLCD_systemState_t;

typedef enum
{
	HLCD_4_BIT_MODE = 0,
	HLCD_8_BIT_MODE
}EN_HLCD_dataPinsMode_t;


typedef struct
{
	EN_HLCD_dataPinsMode_t  dataPinsMode;
	EN_GPIO_mcuPorts_t   controlPort;
	EN_GPIO_mcuPorts_t	 dataPort;
	EN_GPIO_mcuPins_t	 rsPin;
	EN_GPIO_mcuPins_t	 rwPin;
	EN_GPIO_mcuPins_t	 enPin;
	EN_GPIO_mcuPins_t	 d0Pin;
	EN_GPIO_mcuPins_t	 d1Pin;
	EN_GPIO_mcuPins_t	 d2Pin;
	EN_GPIO_mcuPins_t	 d3Pin;
	EN_GPIO_mcuPins_t	 d4Pin;
	EN_GPIO_mcuPins_t	 d5Pin;
	EN_GPIO_mcuPins_t	 d6Pin;
	EN_GPIO_mcuPins_t	 d7Pin;

}ST_HLCD_cfg_t;



#endif /* HAL_LCD_LCD_CONFIG_H_ */
