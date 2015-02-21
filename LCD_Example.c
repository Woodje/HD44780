/*
 * LCD_Example.c
 *
 * Created: 15-02-2015 16:28:53
 *  Author: Woodje
 */

#include "LCD.h"

int main(void)
{
	// Initializing the LCD with the necessary commands before being able to use the LCD.
	InitializeLCD();

	while(1)
	{	
		// Create a custom character.
		CreateCustomCharacter(0, customCharacter);
		
		// Set the cursor to the second line, and move it 8 places.
		SendCommandToLCD(LCDsSetCursor | LCDsLineTwo + 8);
		
		// Write the custom character to the LCD.
		WriteCharacterToLCD(0);
		
		// Give it a delay of one second.
		_delay_ms(1000);
	}
}