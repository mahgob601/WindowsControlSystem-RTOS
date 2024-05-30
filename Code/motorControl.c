#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "DIO.h"
#include "bitwise_operation.h"
#include "types.h"

void motorUP(){
//DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
//DIO_WritePin(&GPIO_PORTA_DATA_R,3,1);

DIO_WritePort(&GPIO_PORTA_DATA_R,0xc);
	
}
void motorDOWN(){
	//DIO_WritePort(&GPIO_PORTA_DATA_R,0xc);
	DIO_WritePort(&GPIO_PORTA_DATA_R,0x14);
}

void motorOFF(){
	DIO_WritePort(&GPIO_PORTA_DATA_R,0x0);
}


