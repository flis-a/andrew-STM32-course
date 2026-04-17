/*
 * 003led_button_ext.c
 *
 *  Created on: Mar 10, 2026
 *      Author: Andrew Flis
 */

#include "stm32f407xx.h"
#include <string.h>

#define HIGH 	1
#define LOW 	0

void delay(void)
{
	// ~200ms delay with SYS CLK at 16MHz
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

int main(void)
{

	GPIO_Handle_t GpioLed, GpioBtn;
	memset(&GpioLed,0,sizeof(GpioLed));
	memset(&GpioBtn,0,sizeof(GpioBtn));

	// Configure GPIO Pin
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	// Enable CLK
	GPIO_PeriClockControl(GPIOD, ENABLE);
	// Init Pin
	GPIO_Init(&GpioLed);

	// Configure GPIO Button
	GpioBtn.pGPIOx = GPIOD;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	// Enable CLK
	GPIO_PeriClockControl(GPIOD, ENABLE);
	// Init Pin
	GPIO_Init(&GpioBtn);

	// IRQ Config
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);

	while(1);
}

void EXTI9_5_IRQHandler(void)
{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_5); // Clear pending event
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}
