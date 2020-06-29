/*=============================================================================
 * Copyright (c) 2020, felipesarche <sarche_2004@hotmail.com>
 * All rights reserved.
 * License:  (see LICENSE.txt)
 * Date: 2020/06/28
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"
#include "pt1.h"
#include "tipos.h"
#include "fsm_debounce.h"
 
/*=====[Inclusions of private function dependencies]=========================*/
 DEBUG_PRINT_ENABLE;
/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

// Task implementation
void TareaA( void* taskParmPtr )
{
    // ---------- CONFIGURACIONES ------------------------------





    gpioWrite( LED1, ON );
    vTaskDelay( 1000 / portTICK_RATE_MS );	 					// Envia la tarea al estado bloqueado durante 1 s (delay)
    gpioWrite( LED1, OFF );


    TickType_t xPeriodicity =  1000 / portTICK_RATE_MS;		// Tarea periodica cada 1000 ms

    TickType_t xLastWakeTime = xTaskGetTickCount();

    // ---------- REPETIR POR SIEMPRE --------------------------
    while( TRUE )
    {

    	char texto[6];
		texto[0]='L';
		texto[1]='E';
		texto[2]='D';
		texto[3]='O';
		texto[4]='N';
		texto[5]='\n';


		xQueueSend( cola1 ,&texto[0] , portMAX_DELAY );//envio mensaje a cola


    	//xQueueSend( cola1 ,&h ,  3000 / portTICK_RATE_MS  );//envio mensaje a cola
    	gpioWrite( LEDB ,1 );
        vTaskDelay( 500 / portTICK_RATE_MS );
        gpioWrite( LEDB ,0 );

        //vTaskDelay( 500 / portTICK_RATE_MS ); //NO USAR!!

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
    }
}
void TareaB( void* taskParmPtr )
{

	tLedTecla* config = (tLedTecla*) taskParmPtr;

	fsmButtonInit( config );

	while( 1 )
	{
		fsmButtonUpdate( config );
	 	vTaskDelay( 1 / portTICK_RATE_MS );
	}
}
void TareaC( void* taskParmPtr )
{
	//struct Mensaje rec;

    debugPrintConfigUart( UART_USB, 9600 );
    debugPrintlnString( "Ejercicio printf.\n" );


    //TickType_t xPeriodicity =  1000 / portTICK_RATE_MS;		// Tarea periodica cada 1000 ms

    //TickType_t xLastWakeTime = xTaskGetTickCount();

    // ---------- REPETIR POR SIEMPRE --------------------------
    while( TRUE )
    {
    	char vec[6];
    	int indicetareac;
    	xQueueReceive( cola1 , &vec[0],  portMAX_DELAY );//recibo los datos de la cola
    	xSemaphoreTake(mutex , portMAX_DELAY );
    	//gpioToggle( LED1 );
    	for(indicetareac=0;indicetareac<11;indicetareac++)
    	{
    		debugPrintChar(vec[indicetareac]);
    		if(vec[indicetareac]=='\n')
    		{
    			break;
    		}
    		xSemaphoreGive( mutex);

    	}



    }
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

