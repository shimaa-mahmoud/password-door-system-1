#include "lcd.h"
#include "keypad.h"

uint8 correct_pass[]= {1,2,3,4};
uint8 my_pass[4];

void get_password();
uint8 compare_pass(uint8* a, uint8* b);
void open_door();
void close_door();

int main (void)
{
	LCD_init();
	uint8 match;

	DDRC |= (1<<PC0) | (1<<PC1);
	PORTC &= ~ 0X03;
	while(1)
	{
		LCD_clearScreen();
		LCD_displayString("ENTER PASSWORD");
		get_password();
		match = compare_pass(correct_pass,my_pass);
		if (match)
		{
			LCD_clearScreen();
			LCD_displayString("DOOR OPENING");
			open_door();
			LCD_clearScreen();
			LCD_displayString("DOOR CLOSING");
			close_door();
		}
		else
		{
			LCD_clearScreen();
			LCD_displayString("WRONG PASSWORD");
			_delay_ms(2000);
		}
	}
}

void get_password()
{
	LCD_goToRowColumn(1,4);
	for (uint8 i=0; i<4; i++)
	{
		my_pass[i] = KeyPad_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
	}
}

uint8 compare_pass(uint8* a, uint8* b)
{
	if ( b[1]==a[1] && b[2]==a[2] && b[3]==a[3] && b[0]==a[0])
		return 1;
	else
		return 0;
}

void open_door()
{
	PORTC &= (~(1<<PC0));
	PORTC |= (1<<PC1);
	_delay_ms(5000);
}
void close_door()
{
	PORTC |= (1<<PC0);
	PORTC &= (~(1<<PC1));
	_delay_ms(5000);
	PORTC &= ~ 0X03;
}
