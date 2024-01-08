/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : main.c
// Date          : Jan 5, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "stm32f103x6.h"
#include "GPIO.h"

void vCLOCK_init(void);
void vGPIO_init(void);
void vWaitMs(uint32 itr);
GPIO_uddtPinConfig_t  pinCfg;
int main(void)
{

	vCLOCK_init();
	vGPIO_init();
	while(1)
	{
		MGPIO_uddtPinLogic_t   uddtLogicVal;
		MGPIO_uddtGetPin(GPIOA,MGPIO_PIN1,&uddtLogicVal);
		if(uddtLogicVal == MGPIO_LOGIC_LOW)
		{
			MGPIO_uddtTogPin(GPIOB,MGPIO_PIN1);
			while(uddtLogicVal == MGPIO_LOGIC_LOW)
			{
			   MGPIO_uddtGetPin(GPIOA,MGPIO_PIN1,&uddtLogicVal);
			}
		}

		MGPIO_uddtGetPin(GPIOA,MGPIO_PIN13,&uddtLogicVal);
		if(uddtLogicVal == MGPIO_LOGIC_HIGH)
		{
			MGPIO_uddtTogPin(GPIOB,MGPIO_PIN13);
		}
		vWaitMs(1);
	}

	return 0;
}

void vCLOCK_init(void)
{
		RCC_GPIOA_CLK_EN();
		RCC_GPIOB_CLK_EN();
}

void vGPIO_init(void)
{
	pinCfg.GPIOx = GPIOA;
	pinCfg.uddtPinNumber = MGPIO_PIN1;
	pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
	MGPIO_uddtInitPin(&pinCfg);

	pinCfg.GPIOx = GPIOB;
	pinCfg.uddtPinNumber = MGPIO_PIN1;
	pinCfg.uddtPinMode = MGPIO_OUTPUT_PP_MODE;
	pinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
	MGPIO_uddtInitPin(&pinCfg);

	pinCfg.GPIOx = GPIOA;
	pinCfg.uddtPinNumber = MGPIO_PIN13;
	pinCfg.uddtPinMode = MGPIO_INPUT_FL_MODE;
	MGPIO_uddtInitPin(&pinCfg);

	pinCfg.GPIOx = GPIOB;
	pinCfg.uddtPinNumber = MGPIO_PIN13;
	pinCfg.uddtPinMode = MGPIO_OUTPUT_PP_MODE;
	pinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
	MGPIO_uddtInitPin(&pinCfg);

}

void vWaitMs(uint32 itr)
{
	uint32 i,j;
	for(i =0;i<itr;i++)
	{
		for(j=0;j<255;j++);
	}
}
