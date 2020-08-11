/*
 * EEPROM_Internal.h
 *
 * Created: 4/6/2020 4:42:02 AM
 *  Author: lenovo
 */ 


#ifndef EEPROM_INTERNAL_H_
#define EEPROM_INTERNAL_H_

#define	Address_LM35_Sensor1	0x01
#define	Address_LM35_Sensor2	0x02
#define	Address_LM35_Sensor3	0x03

#define	Address_LDR_Sensor1		0x11
#define	Address_LDR_Sensor2		0x12
#define	Address_LDR_Sensor3		0x13

#define	Address_MD_Sensor1		0x21
#define	Address_MD_Sensor2		0x22
#define	Address_MD_Sensor3		0x23
#define	Address_MD_Sensor4		0x24
#define	Address_MD_Sensor5		0x25

 


#include "STD_Types.h"
void EEPROM_Write(uint16 Address,uint8 Data);
uint8 EEPROM_Read(uint16 Address);



#endif /* EEPROM_INTERNAL_H_ */