/*
 * LDR.c
 *
 * Created: 4/6/2020 1:32:24 AM
 *  Author: lenovo
 */ 
#include "LDR.h"
#include "ADC.h"


void LDR_Init(LDR_Pins_t Vout_Pin){
	DIO_SetDirPin(GetPort(Vout_Pin),GetPin(Vout_Pin),INFREE);
}
uint16 LDR_Read(LDR_Pins_t Vout_Pin){
	float FSR=5;
	float Resolution=FSR/1024;
	float TF_Sensor=15.1/1000;
	float Vout=(ADC_Read(Vout_Pin,AVCC_Pin)*(Resolution));
	return round((Vout/TF_Sensor));
}