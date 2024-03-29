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
	GPIO_RS_HIGH();

	while (1)
	{
		uint8_t i= 0;
		while (i < 80)
		{
			Send_Byte(0xFC);
			i++;
		}
		uint8_t j= 0;
		while (j < 80)
		{
			Send_Byte(0xFEu);
			j++;
		}
	
	}
	
	GPIO_RS_LOW();
}

void Demo_Mode(void)
{
	GPIO_RS_HIGH();
	
	for (uint8_t i; i < 0xFFu; i++)
	{
		Send_Byte(i);
	}
	
	GPIO_RS_LOW();
}

void Send_Byte(uint8_t data)
{
	uint32_t spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_10MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	GPIO_SS_LOW();
	spiSend(data);
	GPIO_SS_HIGH();
}
