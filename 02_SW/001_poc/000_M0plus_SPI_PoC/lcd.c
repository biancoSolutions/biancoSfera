/*
 * lcd.c
 *
 * Created: 14.03.2023 21:39:12
 *  Author: Jan.WEISS
 */ 

#include "gpio.h"
#include "tmr.h"
#include "spi_master.h"
#include "lcd.h"

void LCD_Init(void)
{

	SPI_init();
	TMR_Init();
	GPIO_Init();
	GPIO_RS_LOW();

	//Start unlocking the EEProm
	uint8_t initFrequence[] = {0x38u, 0x38u, 0x38u, 0x38u, 0x08u, 0x01u, 0x06u, 0x0Fu};
	
	for (uint8_t i; i < sizeof(initFrequence); i++)
	{
		Send_Byte(initFrequence[i]);
	}
}

void Write_Something(void)
{
	SPI_init();
	TMR_Init();
	GPIO_Init();

	while (1)
	{
		// GPIO_SS_LOW();

		Send_Byte(0x56);		
		Send_Byte(0x65);
		Send_Byte(0x6E);
		Send_Byte(0x69);
		Send_Byte(0x73);
		
		GPIO_SS_HIGH();

	}
	
}

void Demo_Mode(void)
{
	GPIO_RS_HIGH();
	
	for (uint8_t i; i < 0xFFu; i++)
	{
		GPIO_SS_LOW();
		Send_Byte(i);
	}
	
}

void Send_Byte(uint8_t data)
{
	uint32_t spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	spiSend(data);
}
