/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : Atmega32_Drivers
// File          : gpio_config.h
// Date          : 31 Jul 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/
#ifndef MCAL_GPIO_GPIO_CONFIG_H_
#define MCAL_GPIO_GPIO_CONFIG_H_

typedef enum { GPIO_OK = 0, GPIO_NOK, GPIO_NULL_PTR } EN_GPIO_systemState_t;

typedef enum {
  GPIO_PIN0 = 0,
  GPIO_PIN1,
  GPIO_PIN2,
  GPIO_PIN3,
  GPIO_PIN4,
  GPIO_PIN5,
  GPIO_PIN6,
  GPIO_PIN7
} EN_GPIO_mcuPins_t;

typedef enum {
  GPIO_PORTA = 0,
  GPIO_PORTB,
  GPIO_PORTC,
  GPIO_PORTD
} EN_GPIO_mcuPorts_t;

typedef enum {
  GPIO_INPUT = 0,
  GPIO_OUTPUT,
} EN_GPIO_pinDir_t;

typedef enum { GPIO_LOW = 0, GPIO_HIGH } EN_GPIO_pinLogic_t;

typedef struct {

  EN_GPIO_mcuPorts_t portName;
  EN_GPIO_mcuPins_t pinNumber;
  EN_GPIO_pinDir_t pinDirection;
  EN_GPIO_pinLogic_t logicOnPin;
} ST_GPIO_cfg_t;

#endif /* MCAL_GPIO_GPIO_CONFIG_H_ */
