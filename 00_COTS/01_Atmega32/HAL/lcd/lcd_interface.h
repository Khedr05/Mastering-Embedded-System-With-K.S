/*************************************************************************/
// Author        : Sherif Ashraf Khadr									 
// Project       : Atmega32_Drivers                                    	 
// File          : lcd_interface.h                                  	     
// Date          : 12 Aug 2023	                                                                                                 */
// GitHub        : https://github.com/sherifkhadr             		     
/*************************************************************************/
#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

#include <util/delay.h>
#include "../../COMMON/std_types.h"
#include "lcd_config.h"


EN_HLCD_systemState_t HLCD_init(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance);

EN_HLCD_systemState_t HLCD_sendCmd(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance , uint8_t Copy_u8Command);

EN_HLCD_systemState_t HLCD_displayChar(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance , uint8_t Copy_u8Char);

EN_HLCD_systemState_t HLCD_displayString(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance ,uint8_t *Copy_u8String);

EN_HLCD_systemState_t HLCD_displayNumber(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance , uint32_t Copy_u8Number);

EN_HLCD_systemState_t HLCD_changeCursorPosation(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance , uint8_t Copy_u8Row,uint8_t Copy_u8Column);

EN_HLCD_systemState_t HLCD_shiftDisplay(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance ,uint8_t Copy_u8ShiftItirations,uint8_t Copy_u8ShiftDirection);

EN_HLCD_systemState_t HLCD_createNewCustomChar(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance , uint8_t *Copy_u8ArrayOfChar , uint8_t Copy_u8CgramPosition);

EN_HLCD_systemState_t HLCD_Clr(ST_HLCD_cfg_t const *ST_ptrLcdCfgInstance);



#endif /* HAL_LCD_LCD_INTERFACE_H_ */
