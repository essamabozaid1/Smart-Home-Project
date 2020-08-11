/*
 * DIO_Cfg.c
 *
 * Created: 1/19/2020 10:14:27 PM
 *  Author: lenovo
 */ 

#include "DIO_Cfg.h"
//ana ast3mlt el enum m3 elarray 3shan awfar memory? tb ma a3ml el type of array uint8 bdl ma hwa 128 hyb2a 32
const DIO_Pin_State_t Pin_State[]=
{
	INFREE, // PA0 
	INFREE, // PA1
	INFREE, // PA2  Relay
	INFREE, // PA3	Buzzer
	OUTPUT, // PA4	LCD-D4
	OUTPUT, // PA5	LCD-D5
	OUTPUT, // PA6	LCD-D6
	OUTPUT,	// PA7	LCD-D7
	
	INFREE, // PB0	Button-0
	OUTPUT,	// PB1	LCD-RS
	OUTPUT, // PB2	LCD-RW
	OUTPUT, // PB3	LCD_E
	INFREE, // PB4	Button-1
	INFREE, // PB5	
	INFREE, // PB6
	INFREE, // PB7
	
	INFREE,	// PC0	
	INFREE, // PC1
	OUTPUT, // PC2	LED-0
	INFREE, // PC3	H-Bridge-Input-0
	INFREE, // PC4	H-Bridge-Input-1
	INFREE, // PC5	H-Bridge-Input-2
	INFREE, // PC6	H-Bridge-Input-3
	OUTPUT, // PC7	LED-1
	INFREE, // PD0
	INFREE, // PD1
	INFREE, // PD2	Button-2
	OUTPUT, // PD3	LED-2
	INFREE, // PD4	H-Bridge-Enable-1
	INFREE, // PD5	H-Bridge-Enable-2
	INFREE, // PD6
	INFREE, // PD7	SERVO
};