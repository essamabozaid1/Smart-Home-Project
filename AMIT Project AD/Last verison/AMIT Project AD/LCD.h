/*
 * LCD.h
 *
 * Created: 2/11/2020 4:38:57 AM
 *  Author: lenovo
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "STD_Types.h"

//////////////////////////////////////////////////////
//////////////// Configuration //////////////////////
//////////////////////////////////////////////////// 
//if set in 4 pin Mode , don't care D0 - D3 Pins
#define LCD_Mode 4
#if LCD_Mode==4
#define D4_Pin	4
#define D5_Pin	5
#define D6_Pin	6
#define D7_Pin	7
#else
#define D0_Pin	0
#define D1_Pin	1
#define D2_Pin	2
#define D3_Pin	3
#define D4_Pin	4
#define D5_Pin	5
#define D6_Pin	6
#define D7_Pin	7
#endif


#define RS_Pin	9
#define RW_Pin	10
#define E_Pin	11


//////////////////////////////////////////////////////
//////////////// Prototypes /////////////////////////
////////////////////////////////////////////////////

void LCD_Init(void);
void LCD_WriteChar(uint8 ch);
void LCD_SendCommand(uint8 command);
void LCD_WriteString(uint8 * str);
void LCD_Clear(void);
void LCD_Goto(uint8 x,uint8 y);
void LCD_WriteNumber(sint16 num);


#endif /* LCD_H_ */