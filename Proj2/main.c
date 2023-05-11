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
xTaskHandle openClosePassengerHandler;
xTaskHandle controlHandler;
xSemaphoreHandle xBinarySemaphore1;
xSemaphoreHandle xBinarySemaphore2;

void vApplicationIdleHook(){
}


int main(){
	DIO_init();
	xBinarySemaphore1 = xSemaphoreCreateBinary();
	xBinarySemaphore2 = xSemaphoreCreateBinary();
	xTaskCreate(openCloseDriver,"openCloseDriver",240,NULL,2,&openCloseDriverHandler);
	xTaskCreate(openClosePassenger,"openClosePassenger",240,NULL,2,&openClosePassengerHandler);
	xTaskCreate(control,"control",240,NULL,1,&controlHandler);
	//xTaskCreate(&fun2,"fun2",240,NULL,2,NULL);
	vTaskStartScheduler();
	for(;;);
	
return 0;
}