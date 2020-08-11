/*
 * DIO_Cfg.h
 *
 * Created: 1/19/2020 10:13:52 PM
 *  Author: lenovo
 */ 


#ifndef DIO_CFG_H_
#define DIO_CFG_H_
#include "D:\embedded new\Interfacing Drivers\STD_Types\STD_Types.h"
#define Last_Pin 32
typedef enum
{
	OUTPUT= 0,
	INPULLUP,
	INFREE
}DIO_Pin_State_t;
typedef enum{
	PA=0,
	PB,
	PC,
	PD
}DIO_Port_t;




#endif /* DIO_CFG_H_ */