/*
 * LM35.h
 *
 * Created: 4/4/2020 4:26:06 PM
 *  Author: lenovo
 */ 


#ifndef LM35_H_
#define LM35_H_
#include "STD_Types.h"
#include "DIO.h"

typedef enum{
	LM35_Sensor1=0,
	LM35_Sensor2,
	LM35_Sensor3,
}LM35_Pins_t;

void LM35_Init(LM35_Pins_t Vout_Pin);
uint16 LM35_Read(LM35_Pins_t Vout_Pin);



#endif /* LM35_H_ */