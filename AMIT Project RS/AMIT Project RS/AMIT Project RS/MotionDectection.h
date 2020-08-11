/*
 * MotionDectection.h
 *
 * Created: 4/6/2020 4:03:03 AM
 *  Author: lenovo
 */ 


#ifndef MOTIONDECTECTION_H_
#define MOTIONDECTECTION_H_
#include "STD_Types.h"
typedef enum{
	MotionDetection_Sensor1=8,
	MotionDetection_Sensor2,
	MotionDetection_Sensor3,
	MotionDetection_Sensor4,
	MotionDetection_Sensor5,
	}MotionDetection_Pin_t;


void MotionDetection_Init(MotionDetection_Pin_t Vout_Pin);
uint8 MotionDetection_Read(MotionDetection_Pin_t Vout_Pin);

#endif /* MOTIONDECTECTION_H_ */