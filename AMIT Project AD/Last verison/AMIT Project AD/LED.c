/*
 * LED.c
 *
 * Created: 1/20/2020 3:39:35 AM
 *  Author: lenovo
 */ 
#include "STD_Types.h"
#include "LED.h"
#include "DIO.h"
void Led_Init(Led_Num_t Led_Num){
	DIO_SetDirPin(GetPort(Led_Num),GetPin(Led_Num),OUTPUT);
}
void Led_Handler(Led_Num_t Led_Num,uint8 Level){
	if(HIGH==Level){
		DIO_WritePin(GetPort(Led_Num),GetPin(Led_Num),HIGH);
	}else if(LOW==Level){
		DIO_WritePin(GetPort(Led_Num),GetPin(Led_Num),LOW);
	}else{}
}
void Led_Toggle(Led_Num_t Led_Num){
	DIO_TogglePin(GetPort(Led_Num),GetPin(Led_Num));	
}
