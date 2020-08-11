/*
 * LM35.c
 *
 * Created: 4/4/2020 4:25:51 PM
 *  Author: lenovo
 */ 
#include "LM35.h"
#include "ADC.h"
void LM35_Init(LM35_Pins_t Vout_Pin){
	DIO_SetDirPin(GetPort(Vout_Pin),GetPin(Vout_Pin),INFREE);
}
uint16 LM35_Read(LM35_Pins_t Vout_Pin){
	return (uint16)(ADC_Read(Vout_Pin,Internal_Volt)*2.5/10.00);
}