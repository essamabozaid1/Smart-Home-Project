/*
 * TWI_driver.h
 *
 * Created: 4/1/2020 9:03:18 PM
 *  Author: lenovo
 */ 


#ifndef TWI_DRIVER_H_
#define TWI_DRIVER_H_
#include "STD_Types.h"

#define START_COND_TRANSMITTED          0x08
#define RESTART_COND_TRANSMITTED        0x10
#define SLA_W_SENT_ACK_RECEIVED         0x18
#define SLA_R_SENT_ACK_RECEIVED         0x40
#define MASTER_DATA_SENT_ACK_RECEIVED   0x28
#define SLAVE_DATA_SENT_ACK_RECEIVED    0xB8
#define MASTER_DATA_RECEIVED_ACK_SENT   0x50
#define MASTER_DATA_RECEIVED_N_ACK_SENT 0x58
#define SLAVE_DATA_RECEIVED_ACK_SENT    0x80
#define SLAVE_DATA_RECEIVED_N_ACK_SENT  0x88

typedef enum
{
	TWI_PRESC_1,
	TWI_PRESC_4,
	TWI_PRESC_16,
	TWI_PRESC_64
}Prescaler_t;
typedef enum
{
	WRITE,
	READ
}RW_t;
typedef enum
{
	NOK,
	OK
}Ret_t;

void TWI_MasterInit(uint8 bitrate, Prescaler_t PS );
Ret_t TWI_MasterStart(uint8 slave_add, RW_t dir);
void TWI_MasterStop(void);
Ret_t TWI_Write(uint8 data);
Ret_t TWI_Read(uint8 * outdataptr);
void TWI_SlaveInit(uint8 own_address);

#endif /* TWI_DRIVER_H_ */