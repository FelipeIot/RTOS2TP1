/*
 * tipos.h
 *
 *  Created on: Jun 28, 2020
 *      Author: felipe
 */

#ifndef MISINTENTOS_PT1_INC_TIPOS_H_
#define MISINTENTOS_PT1_INC_TIPOS_H_


#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "sapi.h"
#include "semphr.h"

#define CANT	2



typedef enum
{
    STATE_BUTTON_UP,
    STATE_BUTTON_DOWN,
    STATE_BUTTON_FALLING,
    STATE_BUTTON_RISING
} fsmButtonState_t;

typedef struct
{
	char identificador;

	gpioMap_t tecla;			//config


	TickType_t tiempo_medido;	//variables
	fsmButtonState_t fsmButtonState;//variables
	TickType_t tiempo_down;		//variables
	TickType_t tiempo_up;		//variables

	uint8_t contFalling  ;		//variables
	uint8_t contRising  ;		//variables

	QueueHandle_t queue_tec_pulsada;
	SemaphoreHandle_t mutex;
} tLedTecla;


#endif /* MISINTENTOS_PT1_INC_TIPOS_H_ */
