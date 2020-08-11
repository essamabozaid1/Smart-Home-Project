/*
 * TWI_driver.c
 *
 * Created: 4/1/2020 9:02:27 PM
 *  Author: lenovo
 */ 
#include "TWI_driver.h"
volatile uint8 _Data;
volatile Ret_t _ret=NOK;
void TWI_MasterInit(uint8 bitrate, Prescaler_t PS ){
	TWBR = ((F_CPU/(bitrate*1000))-16)/(2*pow(4,PS));
	//TWSR = (TWSR & 0xF8) | PS;
	(Read_Bit(PS,0)) ? Set_Bit(TWSR,TWPS0) : Clear_Bit(TWSR,TWPS0);
	(Read_Bit(PS,1)) ? Set_Bit(TWSR,TWPS1) : Clear_Bit(TWSR,TWPS1);
}
Ret_t TWI_MasterStart(uint8 slave_add, RW_t dir){
	uint8 status;
	/* ====================== Start condition ===========================*/
	Set_Bit(TWCR,TWEN);		// Enable the TWI
	Set_Bit(TWCR,TWSTA);	//Enable Start bit
	Set_Bit(TWCR,TWINT);	//Start the job
	while(!Read_Bit(TWCR,TWINT));	//Wait The Job finished
	status = TWSR & 0xF8;			// Get the status ... andding with 0xf8 to put first 3 bits =0;
	if(status!= START_COND_TRANSMITTED && status != RESTART_COND_TRANSMITTED){
		return NOK;
	}
	/* ====================== SLA Address and RW bit ===================*/
	TWDR = (slave_add<<1) | dir;
	Set_Bit(TWCR,TWEN);				// Enable the TWI
	Set_Bit(TWCR,TWINT);			//Start the job
	while(!Read_Bit(TWCR,TWINT));	//Wait The Job finished
	status = TWSR & 0xF8;			// Get the status ... andding with 0xf8 to put first 3 bits =0;
	if(status!= SLA_W_SENT_ACK_RECEIVED && status != SLA_R_SENT_ACK_RECEIVED){
		return NOK;
	}
	return OK;
} 
void TWI_MasterStop(void){
	Set_Bit(TWCR,TWSTO);			// Enable the Stop bit
	Set_Bit(TWCR,TWEN);				// Enable the TWI
	Set_Bit(TWCR,TWINT);			//Start the job
	while(Read_Bit(TWCR,TWSTO));	// Wait STOP bit to be 0 as indication of stop condition executed
}
Ret_t TWI_Write(uint8 data){
	uint8 status;
	TWDR=data;
	Set_Bit(TWCR,TWEN);				// Enable the TWI
	Set_Bit(TWCR,TWINT);			//Start the job
	while(!Read_Bit(TWCR,TWINT));	//Wait The Job finished
	status = TWSR & 0xF8;			// Get the status ... andding with 0xf8 to put first 3 bits =0;
	if(status!= MASTER_DATA_SENT_ACK_RECEIVED && status != SLAVE_DATA_SENT_ACK_RECEIVED){
		return NOK;
	}
	return OK;
}
Ret_t TWI_Read(uint8 * outdataptr){
	uint8 status;
	Set_Bit(TWCR,TWEA);				// Enable the Ack
	Set_Bit(TWCR,TWEN);				// Enable the TWI
	Set_Bit(TWCR,TWINT);			//Start the job
	while(!Read_Bit(TWCR,TWINT));	//Wait The Job finished
	/* Put the data register value to the output parameter */
	*outdataptr = TWDR;
	/* Read the status of the I2C device*/
	status = TWSR & 0xF8;
	/* Check that the status is Data is received and ACK transmitted */
	if (status != MASTER_DATA_RECEIVED_ACK_SENT && status != SLAVE_DATA_RECEIVED_ACK_SENT)
	{
		return NOK;
	}
	return OK;
}
void TWI_SlaveInit(uint8 own_address)
{
	TWAR = (own_address<<1);
	cli();
	TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWIE) | (1<<TWINT) ;
	sei();
}

ISR(TWI_vect){
	Toggle_Bit(PORTC,7);
	if((TWSR & 0xF8)==SLAVE_DATA_RECEIVED_ACK_SENT){
		_Data=TWDR; // datasheet Said "so all accesses to (TWAR),(TWSR), and	(TWDR) must be complete before clearing this flag"
		TWCR |= (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
		_ret = OK;
	}
	TWCR |= (1<<TWINT) | (1<<TWEN);// datasheet said "this flag is not automatically cleared by hardware when executing the interrupt routine"
}