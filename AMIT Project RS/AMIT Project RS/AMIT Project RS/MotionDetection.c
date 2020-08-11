/*
 * MotionDetection.c
 *
 * Created: 4/6/2020 4:03:28 AM
 *  Author: lenovo
 */ 
#include "MotionDectection.h"
#include "DIO.h"

void MotionDetection_Init(MotionDetection_Pin_t Vout_Pin){
	DIO_SetDirPin(GetPort(Vout_Pin),GetPin(Vout_Pin),INFREE);
}
uint8 MotionDetection_Read(MotionDetection_Pin_t Vout_Pin){
	return DIO_ReadPin(GetPort(Vout_Pin),GetPin(Vout_Pin));
}
