/*
 * Motor.c
 *
 * Created: 4/12/2020 11:45:24 AM
 *  Author: lenovo
 */ 
#include "Motor.h"
#include "DIO.h"
#include "Timer0.h"


uint8 Motor0_Flag=0;
uint8 Motor1_Flag=0;
uint8 Motor2_Flag=0;


//uint8 cycle=0;
void Motor_Init(Motor_Num_t Motor_Num){
	TIMER0_Init(F_PWM);
	TIMER0_SetOutputMode(DISCONNECT);
	DIO_SetDirPin(GetPort(Motor_Num),GetPin(Motor_Num),OUTPUT);
}
void Motor_Handler(Motor_Num_t Motor_Num, Motor_State_t Motor_State){ 
	switch(Motor_Num){// to Initiate the state of motor (when it was Medium speed and will change high speed should clear flag
		case AC_Motor0	:    Motor0_Flag=0;		  break;
		case AC_Motor1	:    Motor1_Flag=0;		  break;
		case AC_Motor2	:    Motor2_Flag=0;		  break;
		default:break;
	}
	if(Motor_State==Stop){
		DIO_WritePin(GetPort(Motor_Num),GetPin(Motor_Num),LOW);
	}else if(Motor_State==Medium_Speed){
		switch(Motor_Num){// to Initiate the state of motor
			case AC_Motor0	:	 Motor0_Flag=1;		  break;
			case AC_Motor1	:	 Motor1_Flag=1;		  break;
			case AC_Motor2	:	 Motor2_Flag=1;		  break;
			default: break;
		}
		TIMER0_SetDutyCycle(50);
		TIMER0_Start(PRESC_64);
	}else if(Motor_State==High_Speed){
		DIO_WritePin(GetPort(Motor_Num),GetPin(Motor_Num),HIGH);
	}
}
ISR(TIMER0_OVF_vect){
	if(Motor0_Flag==1){
		DIO_WritePin(GetPort(AC_Motor0),GetPin(AC_Motor0),HIGH);
	}
	if(Motor1_Flag==1){
		DIO_WritePin(GetPort(AC_Motor1),GetPin(AC_Motor1),HIGH);
	}
	if(Motor2_Flag==1){
		DIO_WritePin(GetPort(AC_Motor2),GetPin(AC_Motor2),HIGH);
	}
}
ISR(TIMER0_COMP_vect){
	if(Motor0_Flag){
		DIO_WritePin(GetPort(AC_Motor0),GetPin(AC_Motor0),LOW);
	}	
	if(Motor1_Flag){
		DIO_WritePin(GetPort(AC_Motor1),GetPin(AC_Motor1),LOW);
	}
	if(Motor2_Flag){
		DIO_WritePin(GetPort(AC_Motor2),GetPin(AC_Motor2),LOW);
	}
}