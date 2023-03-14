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

	//Start unlocking the EEProm
	uint32_t spiTimer = 0;

	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x38);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x38);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x38);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x38);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x08);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x01);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x06);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	
	if(GLOBAL_TMR_IS_EXPIRED(spiTimer))
	{
		GPIO_SS_LOW();
		spiSend(0x0F);
		GPIO_SS_HIGH();
	}
	
	spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_100MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
}
