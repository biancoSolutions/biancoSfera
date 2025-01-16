/* (C) 2018 Microchip Technology Inc. and its subsidiaries.
 */

#include "sam.h"
#include "../src/config/default/peripheral/sercom/spi_master/plib_sercom5_spi_master.h"
#include "lcd_handler.h"


uint8_t LCD_init(void)
{	
    uint8_t initFrequence[] = {0x38u, 0x38u, 0x38u, 0x38u, 0x08u, 0x01u, 0x06u, 0x0Fu};
    
    
}

void Send_Byte(uint8_t data)
{
	/*uint32_t spiTimer = GLOBAL_TMR_SET(GLOBAL_TMR_TO_10MS);
	
	while(GLOBAL_TMR_IS_EXPIRED(spiTimer) == 0)
	{
		
	}
	*/
	//GPIO_SS_LOW();
	SERCOM5_SPI_Write(data, sizeof(data));
	//GPIO_SS_HIGH();
}