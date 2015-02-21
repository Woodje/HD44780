/*
 * LCD.c
 *
 * Created: 15-02-2015 16:29:19
 *  Author: Woodje
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "LCD.h"

// Array of a character that is filling one character address.
uint8_t customCharacter[8] = { 0b10001, 0b01110, 0b01110, 0b01010, 0b01010, 0b01110, 0b01110, 0b10001 };

// Initializing the LCD with the necessary commands before being able to use the LCD.
void InitializeLCD()
{
	// For the selected DDR, set the first 4 ports to output including the other specific ports also. "Enable pin & RS pin".
	LCDsControlDatabusDDR |= 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << LCDsEnable | 1 << LCDsRS;
	
	// For the selected DDR, set specific ports to output. "Enable pin & RS pin".
	LCDsControlDatabusDDR |= 1 << LCDsEnable | 1 << LCDsRS;
	
	// Give the LCD some time to initialize.
	_delay_ms(15);
	
	// Initialize the 4-bit operation.
	WriteBitsToLCDsDataLines(0, LCDsFunctionSet4bit);
	
	// Function set, 4 bit, and lines (Layout).
	SendCommandToLCD(LCDsFunctionSet4bit);
	_delay_us(40);							// 40 us delay (minimum).
	
	// Display ON, Cursor On, Cursor Blinking
	SendCommandToLCD(LCDsDisplayOnCursor);
	_delay_us(40);							// 40 us delay (minimum).
	
	// Entry Mode, Increment cursor position, No display shift
	SendCommandToLCD(LCDsEntryMode);
	_delay_us(40);							// 40 us delay (minimum).	
	
	// Clear displays RAM.
	SendCommandToLCD(LCDsClear);
	_delay_us(40);							// 40 us delay (minimum).
}

// Writes 8 bits (byte) to the LCDs/MCUs data lines.
void WriteBitsToLCDsDataLines(uint8_t LCDsRSsState, uint8_t byte)
{
	// Write the four low bits to the data lines while having E as high and RS as provided.
	LCDsControlDatabusPORT = (LCDsRSsState<<LCDsRS) | byte | (1<<LCDsEnable);
	_delay_ms(1);
	
	// Set E to low.
	LCDsControlDatabusPORT = (LCDsRSsState<<LCDsRS) | byte;
	_delay_ms(1);	
}

// Sends a command (Instruction) to the LCD.
void SendCommandToLCD(uint8_t command)
{
	// Write the four high bits to the data lines.
	WriteBitsToLCDsDataLines(0, command >> 4);
	
	// Write the four low bits to the data lines.
	WriteBitsToLCDsDataLines(0, command & 0xF);
}

// Writes a character to the LCD.
void WriteCharacterToLCD(uint8_t character)
{
	// Write the four high bits to the data lines.
	WriteBitsToLCDsDataLines(1, character >> 4);
	
	// Write the four low bits to the data lines.
	WriteBitsToLCDsDataLines(1, character & 0xF);
}

// Writes a string of characters to the LCD.
void WriteStringToLCD(uint8_t string[])
{
	// Character counter.
	volatile int i = 0;
	
	while (string[i] != 0)
	{
		// Write the current character to the LCD and increment the counter.
		WriteCharacterToLCD(string[i++]);
		
		// 40 us delay (minimum).
		_delay_us(40);
	}
}

// Writes an integer to the LCD.
void WriteIntegerToLCD(uint8_t integer)
{
	char numberAsString[2];

	// Convert the integer to a string of character using base10-format.
	itoa(integer, numberAsString, 10);
	
	// Write the number to the LCD.
	WriteStringToLCD(numberAsString);
}

// Create a custom character.
void CreateCustomCharacter(int characterAddress, uint8_t character[])
{
	// Select the address for the custom character.
	SendCommandToLCD(0x40 + characterAddress);
	
	// Go through the provided array of bytes.
	for (int i = 0; i < 8; i++)
	{
		// Write the byte to the character address. (Only the 5 lowest bits are used)
		WriteCharacterToLCD(character[i]);
	}
}