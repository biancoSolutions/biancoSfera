/*
 * lcd.h
 *
 * Created: 14.03.2023 21:39:25
 *  Author: Jan.WEISS
 */ 

#define LCD_ARROW_RIGHT     0x7E
#define LCD_ARROW_LEFT      0x7F
#define LCD_UNFILLED_SQUARE 0xDB
#define LCD_ALPHA           0xE0
#define LCD_AE              0xE1
#define LCD_BETA            0xE2
#define LCD_ETA             0xE3
#define LCD_MY              0xE4
#define LCD_DELTA           0xE5
#define LCD_OE              0xEF
#define LCD_SIGMA           0xF2
#define LCD_INFINITY        0xF3
#define LCD_OMEGA           0xF4
#define LCD_UE              0xF5
#define LCD_PI              0xF7
#define LCD_SPACE_INVADER   0xFC
#define LCD_BLANK_SQUARE    0xFE
#define LCD_FILLED_SQUARE   0xFF

void LCD_Init(void);


