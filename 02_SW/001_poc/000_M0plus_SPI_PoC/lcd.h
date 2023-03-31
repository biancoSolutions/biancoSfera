/*
 * lcd.h
 *
 * Created: 14.03.2023 21:39:25
 *  Author: Jan.WEISS
 */ 

// NON-ASCII CHARACTERS (only valid with RS == 1)
typedef enum 
{
    LCD_ARROW_RIGHT =     (0x7Eu),
    LCD_ARROW_LEFT =      (0x7Fu),
    LCD_UNFILLED_SQUARE = (0xDBu),
    LCD_ALPHA =           (0xE0u),
    LCD_AE =              (0xE1u),
    LCD_BETA =            (0xE2u),
    LCD_ETA =             (0xE3u),
    LCD_MY =              (0xE4u),
    LCD_DELTA =           (0xE5u),
    LCD_OE =              (0xEFu),
    LCD_SIGMA =           (0xF2u),
    LCD_INFINITY =        (0xF3u),
    LCD_OMEGA =           (0xF4u),
    LCD_UE =              (0xF5u),
    LCD_PI =              (0xF7u),
    LCD_SPACE_INVADER =   (0xFCu),
    LCD_BLANK_SQUARE =    (0xFEu),
    LCD_FILLED_SQUARE =   (0xFFu),
} LCD_NonAsciiChars_t;

// LCD CONTROL CHARACTERS (only valid with RS == 0)
typedef enum 
{
    LCD_CLEAR_DISPLAY =   (0x01u),
    LCD_RETURN_HOME =     (0x02u),
    LCD_SHIFT_CURSOR =    (0x14u),
    LCD_SHIFT_DISPLAY =   (0x1Cu),
} LCD_DisplayControlChars_t;

/*!
 * @brief Initialize the LCD display via SPI
 *
 * @param void
 * @return void
 */
void LCD_Init( void );


