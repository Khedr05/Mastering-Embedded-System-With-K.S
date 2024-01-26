/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : main.c
// Date          : Jan 5, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#include "stm32f103x6.h"
#include "GPIO.h"
#include "RCC.h"
#include "UART.h"
#include "SPI.h"

#define SPI_ACT_AS_MASTER		0
#define SPI_ACT_AS_SLAVE		1
#define SPI_DEVICE_MODE			SPI_ACT_AS_MASTER

MUSART_uddtCfg_t uart;
MSPI_uddtCfg_t spi;
uint16 ch;

void sherif(void)
{
#if SPI_DEVICE_MODE == SPI_ACT_AS_MASTER

	MUSART_uddtReceiveData(&uart,&ch);
	MUSART_uddtSendData(&uart,&ch);
	MGPIO_uddtSetPin(GPIOA,MGPIO_PIN4,MGPIO_LOGIC_LOW);
	MSPI_uddtTxRxData(&spi, &ch);
	MGPIO_uddtSetPin(GPIOA,MGPIO_PIN4,MGPIO_LOGIC_HIGH);
#elif SPI_DEVICE_MODE == SPI_ACT_AS_SLAVE


#endif
}

void SPI1_IRQ_Callback(MSPI_IRQ_SRC irqSrc)
{
#if SPI_DEVICE_MODE == SPI_ACT_AS_MASTER

#elif SPI_DEVICE_MODE == SPI_ACT_AS_SLAVE
	if(irqSrc.RXNE)
	{
		ch = 0xF;
		MSPI_uddtTxRxData(&spi, &ch);
		MUSART_uddtSendData(&uart, &ch);
	}

#endif
}

int main(void)
{
	// Clock Init
	MRCC_uddtInitClk(MRCC_HSI, MRCC_APB_PRESCALER_0, MRCC_APB_PRESCALER_0, MRCC_AHB_PRESCALER_0);
	MRCC_uddtEnablePeripheral(MRCC_IOPA);
	MRCC_uddtEnablePeripheral(MRCC_IOPB);
	MRCC_uddtEnablePeripheral(MRCC_AFIO);
	// NVIC Configuration
	MNVIC_uddtSetIRQGroup(MNVIC_GP_04_SP_04);
	MNVIC_uddtSetIRQPriority(MNVIC_USART1_IRQ , MNVIC_GP_04_SP_04 , 1,1);

	//USART1 Init
	uart.UARTx = USART1;
	uart.u32BaudRate = MUSART_BAUDRATE_115200;
	uart.u8HwFlowCtl = MUSART_HWFLOW_NONE;
	uart.u8IRQStatus = MUSART_IRQ_UNMASK_RXNEIE;
	uart.pIRQCallback = sherif;
	uart.u8Parity = MUSART_PARITY_NONE;
	uart.u8PayloadLength = MUSART_PAYLOAD_LEN_8B;
	uart.u8TransferCtl = MUSART_TX_RX;
	MUSART_uddtInit(&uart);
	MUSART_uddtGpioSetPins(&uart);

	//SPI1 Init
	spi.SPIx = SPI1;
	spi.u16ClkPhase = MSPI_CLKPHASE_EDGE2;
	spi.u16ClkPolarity = MSPI_CLKPOLARITY_IDLE_HIGH;
	spi.u16DataSize = MSPI_DATA_SIZE_8B;
	spi.u16FrameFormat = MSPI_FRAME_FORMAT_MSB;
	spi.u16Prescaler = MSPI_PRESCALER_BY_8;
	spi.u16BusMode = MSPI_BUS_MODE_2LINES;

#if SPI_DEVICE_MODE == SPI_ACT_AS_MASTER
	spi.u16DeviceMode = MSPI_DEVICE_MODE_MASTER;
	spi.P_IRQ_Callback = NULL_PTR;
	spi.u16IRQStatus = MSPI_IRQ_MASKED;
	spi.u16NSS = MSPI_NSS_SW_SET;

	MGPIO_uddtPinConfig_t pinA4;
	pinA4.GPIOx = GPIOA;
	pinA4.uddtPinNumber = MGPIO_PIN4;
	pinA4.uddtPinMode = MGPIO_OUTPUT_PP_MODE;
	pinA4.uddtPinSpeed = MGPIO_10MHZ_SPEED;
	pinA4.uddtPinLogic = MGPIO_LOGIC_HIGH;
	MGPIO_uddtInitPin(&pinA4);

#elif SPI_DEVICE_MODE == SPI_ACT_AS_SLAVE

	spi.u16DeviceMode = MSPI_DEVICE_MODE_SLAVE;
	spi.P_IRQ_Callback = SPI1_IRQ_Callback;
	spi.u16IRQStatus = MSPI_IRQ_RXNEIE;
	spi.u16NSS = MSPI_NSS_HW_SLAVE;

#endif

	MSPI_uddtInit(&spi);
	MSPI_uddtGpioSetPins(&spi);



	while(1)
	{

	}
	return 0;
}




