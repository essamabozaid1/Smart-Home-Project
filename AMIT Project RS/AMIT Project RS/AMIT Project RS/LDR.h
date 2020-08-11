/*
 * LDR.h
 *
 * Created: 4/6/2020 1:32:37 AM
 *  Author: lenovo
 */ 


#ifndef LDR_H_
#define LDR_H_


#include "STD_Types.h"
#include "DIO.h"

typedef enum{
	LDR_Sensor1=3,
	LDR_Sensor2,
	LDR_Sensor3,
}LDR_Pins_t;

void	LDR_Init(LDR_Pins_t Vout_Pin);
uint16	LDR_Read(LDR_Pins_t Vout_Pin);




#endif /* LDR_H_ */