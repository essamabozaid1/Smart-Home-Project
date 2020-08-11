/*
 * EEPROM_Internal.h
 *
 * Created: 4/6/2020 4:42:02 AM
 *  Author: lenovo
 */ 


#ifndef EEPROM_INTERNAL_H_
#define EEPROM_INTERNAL_H_
#include "STD_Types.h"

#define	Address_AC_Motor0	0x01
#define	Address_AC_Motor1	0x02
#define	Address_AC_Motor2	0x03

#define	Address_LED0		0x11
#define	Address_LED1		0x12
#define	Address_LED2		0x13

#define	Address_Door_LED0		0x21
#define	Address_Door_LED1		0x22
#define	Address_Door_LED2		0x23
#define	Address_Door_LED3		0x24
#define	Address_Door_LED4		0x25

void EEPROM_Write(uint16 Address,uint8 Data);
uint8 EEPROM_Read(uint16 Address);



#endif /* EEPROM_INTERNAL_H_ */