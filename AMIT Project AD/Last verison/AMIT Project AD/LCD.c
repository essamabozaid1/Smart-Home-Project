/*
 * LCD.c
 *
 * Created: 2/11/2020 4:38:48 AM
 *  Author: lenovo
 */ 

#include "D:\embedded new\Interfacing Drivers\DIO\DIO.h"
#include "LCD.h"

void LCD_SendCommand(uint8 command){
	DIO_WritePin(GetPort(RS_Pin),GetPin(RS_Pin),LOW);
	DIO_WritePin(GetPort(RW_Pin),GetPin(RW_Pin),LOW);
	DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),LOW);
	
	DIO_WritePin(GetPort(D7_Pin),GetPin(D7_Pin),Read_Bit(command,7));
	DIO_WritePin(GetPort(D6_Pin),GetPin(D6_Pin),Read_Bit(command,6));	
	DIO_WritePin(GetPort(D5_Pin),GetPin(D5_Pin),Read_Bit(command,5));
	DIO_WritePin(GetPort(D4_Pin),GetPin(D4_Pin),Read_Bit(command,4));
	
	DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),HIGH);
	_delay_us(5);
	DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),LOW);
	
	_delay_us(100); 
	
	DIO_WritePin(GetPort(D7_Pin),GetPin(D7_Pin),Read_Bit(command,3));
	DIO_WritePin(GetPort(D6_Pin),GetPin(D6_Pin),Read_Bit(command,2));	
	DIO_WritePin(GetPort(D5_Pin),GetPin(D5_Pin),Read_Bit(command,1));
	DIO_WritePin(GetPort(D4_Pin),GetPin(D4_Pin),Read_Bit(command,0));
	
	DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),HIGH);
	_delay_us(5);
	DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),LOW);

	_delay_us(100); 
	if(command==0x01||command==0x02||command==0x03){
		_delay_ms(2);	//this exception instruction it 2 ms 
						//other instruction it take 100 microSecond
	}
}

void LCD_WriteNumber(sint16 num){
	uint16 n=1;
	if (num==0)
	{
		LCD_WriteChar(((num/n)%10)+48);
		
	}else{
		if(Read_Bit(num,15)==0x01){
			num=num*-1;
			LCD_WriteChar('-');
		}
		for(n=10000;n>=1;n/=10){
			if(num>=n){
				LCD_WriteChar(((num/n)%10)+48);
			}
		}
	}
	
}
void LCD_WriteString(uint8 * str)
{
	while(*str)
	{
		LCD_WriteChar(* str);
		str++;
	}
}


void LCD_WriteChar(uint8 ch){
		DIO_WritePin(GetPort(RS_Pin),GetPin(RS_Pin),HIGH);
		DIO_WritePin(GetPort(RW_Pin),GetPin(RW_Pin),LOW);
		DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),LOW);
		
		DIO_WritePin(GetPort(D7_Pin),GetPin(D7_Pin),Read_Bit(ch,7));
		DIO_WritePin(GetPort(D6_Pin),GetPin(D6_Pin),Read_Bit(ch,6));
		DIO_WritePin(GetPort(D5_Pin),GetPin(D5_Pin),Read_Bit(ch,5));
		DIO_WritePin(GetPort(D4_Pin),GetPin(D4_Pin),Read_Bit(ch,4));
		
		DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),HIGH);
		_delay_us(5);
		DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),LOW);
		
		_delay_us(100);
		
		DIO_WritePin(GetPort(D7_Pin),GetPin(D7_Pin),Read_Bit(ch,3));
		DIO_WritePin(GetPort(D6_Pin),GetPin(D6_Pin),Read_Bit(ch,2));
		DIO_WritePin(GetPort(D5_Pin),GetPin(D5_Pin),Read_Bit(ch,1));
		DIO_WritePin(GetPort(D4_Pin),GetPin(D4_Pin),Read_Bit(ch,0));
		
		DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),HIGH);
		_delay_us(5);
		DIO_WritePin(GetPort(E_Pin),GetPin(E_Pin),LOW);

		_delay_us(100);
}


void LCD_Init(void){
	if (LCD_Mode==4)
	{
		_delay_ms(15);
		LCD_SendCommand(0x33); // go to 4 bit mode
		LCD_SendCommand(0x32); // go to 4 bit mode
					// two command 0x30  then 0x20
		
		
		LCD_SendCommand(0b00101000); //if 4 bit 2 line init important 0  |  0  |  1  |  DL |  N  |  F  |  0  |  0
		// DL = Interfacing Data Length (0 = 4-bit  / 1 = 8-bit)
		// N  =	Number of display line  (0 = 1 Line / 1 = 2 Line)
		// F  = character Font  (0 = 5*8 dots / 1= 5*10 dots)
		
		LCD_SendCommand(0b00001110); // display on cursor on          0  |  0  |  0  |  0 |  1  |  D  |  C  |  B
		// D  = Display ON/OFF			(0 = Off      / 1 = ON         )
		// C  =	Cursor is displayed	    (0 = not display cursor / 1 = display cursor)
		// B  = Blinking Cursor			(0 = not Blinking / 1= Blinking)
		
		LCD_SendCommand(0x01); // clear lcd					0  |  0  |  0  |  0 |  0  |  0  |  0  |  1
		

		LCD_SendCommand(0x06); // increament el cursor m3 el ktaba
		
	}else if (LCD_Mode==8)
	{
		_delay_ms(15);
	
		LCD_SendCommand(0b00111000); //if 8 bit 2 line init important 0  |  0  |  1  |  DL |  N  |  F  |  0  |  0
		// DL = Interfacing Data Length (0 = 4-bit  / 1 = 8-bit)
		// N  =	Number of display line  (0 = 1 Line / 1 = 2 Line)
		// F  = character Font  (0 = 5*8 dots / 1= 5*10 dots)
		
		LCD_SendCommand(0b00001110); // display on cursor on          0  |  0  |  0  |  0 |  1  |  D  |  C  |  B
		// D  = Display ON/OFF			(0 = Off      / 1 = ON         )
		// C  =	Cursor is displayed	    (0 = not display cursor / 1 = display cursor)
		// B  = Blinking Cursor			(0 = not Blinking / 1= Blinking)
		
		LCD_SendCommand(0x01); // clear lcd					0  |  0  |  0  |  0 |  0  |  0  |  0  |  1
		

		LCD_SendCommand(0x06); // increament el cursor m3 el ktaba
	}else{ }	
}
void LCD_Clear(void){
	LCD_SendCommand(0x01);
}
void LCD_Goto(uint8 x,uint8 y){
	uint8 firstLinesArr[]={0x80,0xc0,0x94,0xd4};
	LCD_SendCommand(firstLinesArr[y-1]+x-1);
	_delay_us(100);
}
