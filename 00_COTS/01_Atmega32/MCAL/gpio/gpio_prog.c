/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : Atmega32_Drivers
// File          : gpio_prog.c
// Date          : 31 Jul 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "gpio_interface.h"

static volatile uint8_t *ddr_registers[] = {&DDRA_REG, &DDRB_REG, &DDRC_REG,
		&DDRD_REG};
static volatile uint8_t *port_registers[] = {&PORTA_REG, &PORTB_REG, &PORTC_REG,
		&PORTD_REG};
static volatile uint8_t *pin_registers[] = {&PINA_REG, &PINB_REG, &PINC_REG,
		&PIND_REG};

EN_GPIO_systemState_t GPIO_initPin(ST_GPIO_cfg_t const *ST_ptrPinInstance) {
	EN_GPIO_systemState_t ret = GPIO_NOK;
	if (PTR_NULL != ST_ptrPinInstance) {
		ret = GPIO_changePinDir(ST_ptrPinInstance, ST_ptrPinInstance->pinDirection);
		if (GPIO_OK == ret) {
			ret =
					GPIO_writePinLogic(ST_ptrPinInstance, ST_ptrPinInstance->logicOnPin);
		} else {
			/*Do Nothin*/
		}
	} else {
		ret = GPIO_NULL_PTR;
	}
	return ret;
}

EN_GPIO_systemState_t GPIO_changePinDir(ST_GPIO_cfg_t const *ST_ptrPinInstance,
		EN_GPIO_pinDir_t copyNewPinDir) {
	EN_GPIO_systemState_t ret = GPIO_NOK;
	if (PTR_NULL != ST_ptrPinInstance) {
		switch (copyNewPinDir) {
		case GPIO_INPUT: {
			CLR_BIT(*ddr_registers[ST_ptrPinInstance->portName],
					ST_ptrPinInstance->pinNumber);
			ret = GPIO_OK;
			break;
		}
		case GPIO_OUTPUT: {
			SET_BIT(*ddr_registers[ST_ptrPinInstance->portName],
					ST_ptrPinInstance->pinNumber);
			ret = GPIO_OK;
			break;
		}
		}
	} else {
		ret = GPIO_NULL_PTR;
	}
	return ret;
}

EN_GPIO_systemState_t GPIO_writePinLogic(ST_GPIO_cfg_t const *ST_ptrPinInstance,
		EN_GPIO_pinLogic_t copyNewPinLogic) {
	EN_GPIO_systemState_t ret = GPIO_NOK;
	if (PTR_NULL != ST_ptrPinInstance) {
		switch (copyNewPinLogic) {
		case GPIO_LOW: {
			CLR_BIT(*port_registers[ST_ptrPinInstance->portName],
					ST_ptrPinInstance->pinNumber);
			ret = GPIO_OK;
			break;
		}
		case GPIO_HIGH: {
			SET_BIT(*port_registers[ST_ptrPinInstance->portName],
					ST_ptrPinInstance->pinNumber);
			ret = GPIO_OK;
			break;
		}
		}
	} else {
		ret = GPIO_NULL_PTR;
	}
	return ret;
}

EN_GPIO_systemState_t
GPIO_readPinLogic(ST_GPIO_cfg_t const *ST_ptrPinInstance,
		EN_GPIO_pinLogic_t *retCurrentPinLogic) {
	EN_GPIO_systemState_t ret = GPIO_NOK;
	if (PTR_NULL != ST_ptrPinInstance) {
		*retCurrentPinLogic = GET_BIT(*pin_registers[ST_ptrPinInstance->portName],
				ST_ptrPinInstance->pinNumber);
		ret = GPIO_OK;
	} else {
		ret = GPIO_NULL_PTR;
	}
	return ret;
}

EN_GPIO_systemState_t
GPIO_togglePinLogic(ST_GPIO_cfg_t const *ST_ptrPinInstance) {
	EN_GPIO_systemState_t ret = GPIO_NOK;
	if (PTR_NULL != ST_ptrPinInstance) {
		TOG_BIT(*port_registers[ST_ptrPinInstance->portName],
				ST_ptrPinInstance->pinNumber);
		ret = GPIO_OK;
	} else {
		ret = GPIO_NULL_PTR;
	}

	return ret;
}

EN_GPIO_systemState_t GPIO_initPort(EN_GPIO_mcuPorts_t copyPortName,
		EN_GPIO_pinDir_t copyPortDir,
		EN_GPIO_pinLogic_t copyPortLogic) {
	EN_GPIO_systemState_t ret = GPIO_NOK;

	switch (copyPortDir) {
	case GPIO_INPUT: {
		*ddr_registers[copyPortName] = 0x00;
		ret = GPIO_OK;
		break;
	}
	case GPIO_OUTPUT: {
		*ddr_registers[copyPortName] = 0xFF;
		ret = GPIO_OK;
		break;
	}
	}
	switch (copyPortLogic) {
	case GPIO_LOW: {
		*port_registers[copyPortName] = 0x00;
		ret = GPIO_OK;
		break;
	}
	case GPIO_HIGH: {
		*port_registers[copyPortName] = 0xFF;
		ret = GPIO_OK;
		break;
	}
	}
	return ret;
}

EN_GPIO_systemState_t GPIO_changePortDir(EN_GPIO_mcuPorts_t copyPortName,
		EN_GPIO_pinDir_t copyNewPortDir) {
	EN_GPIO_systemState_t ret = GPIO_NOK;

	switch (copyNewPortDir) {
	case GPIO_INPUT: {
		*ddr_registers[copyPortName] = 0x00;
		ret = GPIO_OK;
		break;
	}
	case GPIO_OUTPUT: {
		*ddr_registers[copyPortName] = 0xFF;
		ret = GPIO_OK;
		break;
	}
	}
	return ret;
}

EN_GPIO_systemState_t GPIO_writePortLogic(EN_GPIO_mcuPorts_t copyPortName,
		EN_GPIO_pinLogic_t copyNewPortLogic) {
	EN_GPIO_systemState_t ret = GPIO_NOK;
	switch (copyNewPortLogic) {
	case GPIO_LOW: {
		*port_registers[copyPortName] = 0x00;
		ret = GPIO_OK;
		break;
	}
	case GPIO_HIGH: {
		*port_registers[copyPortName] = 0xFF;
		ret = GPIO_OK;
		break;
	}
	}
	return ret;
}

EN_GPIO_systemState_t
GPIO_readPortLogic(EN_GPIO_mcuPorts_t copyPortName,
		EN_GPIO_pinLogic_t *retCurrentPortLogic) {
	EN_GPIO_systemState_t ret = GPIO_NOK;

	*retCurrentPortLogic = *pin_registers[copyPortName];
	ret = GPIO_OK;
	return ret;
}

EN_GPIO_systemState_t GPIO_togglePortLogic(EN_GPIO_mcuPorts_t copyPortName) {
	EN_GPIO_systemState_t ret = GPIO_NOK;
	*ddr_registers[copyPortName] ^= *ddr_registers[copyPortName];
	ret = GPIO_OK;
	return ret;
}


EN_GPIO_systemState_t GPIO_set4msbValue(EN_GPIO_mcuPorts_t copyPortName,uint8_t value)
{
	EN_GPIO_systemState_t gpioRet = GPIO_NOK;

	*port_registers[copyPortName] &= 0x0F;
	*port_registers[copyPortName] |= value<<4;

	gpioRet = GPIO_OK;

	return gpioRet;
}

EN_GPIO_systemState_t GPIO_SetPortValue(EN_GPIO_mcuPorts_t copyPortName , uint32_t value)
{
	EN_GPIO_systemState_t gpioRet = GPIO_NOK;

	*port_registers[copyPortName] &= 0;
	*port_registers[copyPortName] |= value;
	gpioRet = GPIO_OK;
	return gpioRet;
}
