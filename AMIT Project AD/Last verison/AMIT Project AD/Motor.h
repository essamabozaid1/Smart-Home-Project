/*
 * Motor.h
 *
 * Created: 4/12/2020 11:45:41 AM
 *  Author: lenovo
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include "STD_Types.h"
typedef enum{
	AC_Motor0=13,
	AC_Motor1,
	AC_Motor2,
	
	Door_LED0=24,
	Door_LED1,
	Door_LED2,
	Door_LED3,
	Door_LED4,
	}Motor_Num_t;
typedef enum{
	Stop,
	Medium_Speed,
	High_Speed,
	}Motor_State_t;
void Motor_Init(Motor_Num_t Motor_Num);
void Motor_Handler(Motor_Num_t Motor_Num,Motor_State_t Motor_State);



#endif /* MOTOR_H_ */