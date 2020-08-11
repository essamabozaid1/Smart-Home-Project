/*
 * DIO.h
 *
 * Created: 1/19/2020 10:15:58 PM
 *  Author: lenovo
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "D:\embedded new\Interfacing Drivers\STD_Types\STD_Types.h"
#include "DIO_Cfg.h"

void DIO_WritePin(DIO_Port_t Port_Num,uint8 Pin_Num,uint8 Level);
uint8 DIO_ReadPin(DIO_Port_t Port_Num,uint8 Pin_Num);
void DIO_TogglePin(DIO_Port_t Port_Num,uint8 Pin_Num);
void DIO_SetDirPin(DIO_Port_t Port_Num,uint8 Pin_Num,DIO_Pin_State_t value);
void DIO_Init(void);


#endif /* DIO_H_ */

