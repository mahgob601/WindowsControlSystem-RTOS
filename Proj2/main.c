#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "DIO.h"
#include "bitwise_operation.h"
#include "types.h"
#include "functions.h"
#include <semphr.h>


xQueueHandle xQueuePD;
xTaskHandle openCloseDriverHandler;
xTaskHandle openCloseDriverAutoHandler;
xTaskHandle openClosePassengerHandler;
xTaskHandle controlHandler;
xSemaphoreHandle xBinarySemaphore1;
xSemaphoreHandle xBinarySemaphore2;
xSemaphoreHandle xBinarySemaphoreDriverAuto;
xSemaphoreHandle xBinarySemaphorePassengerAuto;
void vApplicationIdleHook(){
}


int main(){
	DIO_init();
	//while(((*(&GPIO_PORTB_DATA_R) & (1<<3))>>3) != 1);
	//while(1);
	
	xBinarySemaphore1 = xSemaphoreCreateBinary();
	xBinarySemaphore2 = xSemaphoreCreateBinary();
	xBinarySemaphoreDriverAuto = xSemaphoreCreateBinary();
	xTaskCreate(openCloseDriver,"openCloseDriver",240,NULL,2,&openCloseDriverHandler);
	xTaskCreate(openCloseDriverAuto,"openCloseDriverAuto",240,NULL,2,&openCloseDriverAutoHandler);
	xTaskCreate(openClosePassenger,"openClosePassenger",240,NULL,2,&openClosePassengerHandler);
	xTaskCreate(control,"control",240,NULL,1,&controlHandler);
	//xTaskCreate(&fun2,"fun2",240,NULL,2,NULL);
	vTaskStartScheduler();
	for(;;);
	
return 0;
}