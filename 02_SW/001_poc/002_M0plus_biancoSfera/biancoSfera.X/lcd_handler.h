/* 
 * File:   lcd_handler.h
 * Author: Jan.WEISS
 *
 * Created on 22. Mai 2024, 09:11
 */

#ifndef LCD_HANDLER_H
#define	LCD_HANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

uint8_t LCD_init(void);
void Send_Byte(uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_HANDLER_H */

