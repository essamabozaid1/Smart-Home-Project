/*
 * EEPROM_Internal.c
 *
 * Created: 4/6/2020 4:41:45 AM
 *  Author: lenovo
 */ 
#include "EEPROM_Internal.h"
void EEPROM_Write(uint16 Address,uint8 Data){
	while(Read_Bit(EECR,EEWE)); /* Wait for completion of previous write */
	EEAR=Address;				// Set up address register
	EEDR=Data;					// Set up  data registers
	Set_Bit(EECR,EEMWE);		/* Write logical one to EEMWE */
	Set_Bit(EECR,EEWE);			/* Start eeprom write by setting EEWE */
}
uint8 EEPROM_Read(uint16 Address){
	while(Read_Bit(EECR,EEWE)); /* Wait for completion of previous write */
	EEAR=Address;				/* Set up address register */
	Set_Bit(EECR,EERE);			/* Start eeprom read by writing EERE */
	return EEDR;
}