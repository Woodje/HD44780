/*
 * LCD.h
 *
 * Created: 15-02-2015 16:29:08
 *  Author: Woodje
 */

#ifndef LCD_H_
#define LCD_H_

#define LCDsControlDatabusPORT		PORTC		// MCUs PORTC pins / LCDs D4-D7 pins & LCDs E and RS pins.
#define LCDsControlDatabusDDR		DDRC		// MCUs Data Direction Register 'C'.
#define LCDsRS				4                   // LCDs Register Select pin.
#define LCDsEnable			5                   // LCDs Enable pin.

#define LCDsLineOne			0x00				// LCDs Start of line 1.
#define LCDsLineTwo			0x40				// LCDs Start of line 2.

#define LCDsClear           0b00000001          // Replace all characters with ASCII 'space'.
#define LCDsHome            0b00000010          // Return cursor to first position on first line.
#define LCDsDisplayOff      0b00001000          // Turn display off.
#define LCDsDisplayOn       0b00001100          // Display on, cursor off, don't blink character.
#define LCDsSetCursor       0b10000000          // Set cursor position.
#define LCDsFunctionSet4bit 0b00000010			// 4-bit operation, 2-line display, 5 x 8 font.
#define LCDsDisplayOnCursor 0b00001111			// Display on, cursor on, character blinking.
#define LCDsEntryMode       0b00000110          // Shift cursor from left to right on read/write.

// Array of a symbol that is filling four character addresses.
uint8_t customCharacter[8];

// Initializing the LCD with the necessary commands before being able to use the LCD.
void InitializeLCD();

// Sends a command (Instruction) to the LCD.
void SendCommandToLCD(uint8_t command);

// Writes a character to the LCD.
void WriteCharacterToLCD(uint8_t character);

// Writes a string of characters to the LCD.
void WriteStringToLCD(uint8_t string[]);

// Writes an integer to the LCD.
void WriteIntegerToLCD(uint8_t integer);

// Create a custom character.
void CreateCustomCharacter(int characterAddress, uint8_t character[]);

#endif /* LCD_H_ */