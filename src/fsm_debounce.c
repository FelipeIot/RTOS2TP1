/* Copyright 2018, Eric Pernia.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "sapi.h"

#include "tipos.h"
#include "FreeRTOS.h"
#include "fsm_debounce.h"
#include "pt1.h"



void fsmButtonError( tLedTecla* config );
void fsmButtonInit( tLedTecla* config );
void fsmButtonUpdate( tLedTecla* config );
void buttonPressed( tLedTecla* config );
void buttonReleased( tLedTecla* config );

/* accion de el evento de tecla pulsada */
void buttonPressed( tLedTecla* config )
{
	config->tiempo_down = xTaskGetTickCount();
}

/* accion de el evento de tecla liberada */
void buttonReleased( tLedTecla* config )
{
	config->tiempo_up = xTaskGetTickCount();
	config->tiempo_medido = config->tiempo_up - config->tiempo_down;
	char snum[4];
	uint32_t tiempo;
	tiempo=config->tiempo_medido/portTICK_RATE_MS;// obtengo diferencia en ms
	if(tiempo>=9999)
	{
		tiempo=9999;//saturo la diferencia

	}
	itoa(tiempo, snum, 10);
	if(tiempo<=999 && tiempo>99)
	{
		snum[3]='\n';
	}
	else if(tiempo<=99 && tiempo>9)
	{
		snum[2]='\n';

	}
	else if(tiempo<=9)
	{
		snum[1]='\n';
	}




	if (config->tiempo_medido > 0)
	{
		char vec[10];
		vec[0]='T';
		vec[1]='E';
		vec[2]='C';
		vec[3]=config->identificador;
		vec[4]=' ';
		vec[5]='T';
		vec[6]=snum[0];
		vec[7]=snum[1];
		vec[8]=snum[2];
		vec[9]=snum[3];
		vec[10]='\n';

		xQueueSend( cola1 , &vec[0],  portMAX_DELAY  );//envio tiempor en cola
	}

}

void fsmButtonError( tLedTecla* config )
{
	config->fsmButtonState = BUTTON_UP;
}

void fsmButtonInit( tLedTecla* config )
{
	config->contFalling = 0;
	config->contRising = 0;
	config->fsmButtonState = BUTTON_UP;  // Set initial state
}

#define DEBOUNCE_TIME 40

// FSM Update Sate Function
void fsmButtonUpdate( tLedTecla* config )
{
   // static bool_t flagFalling = FALSE;
    //static bool_t flagRising = FALSE;

    switch( config->fsmButtonState )
    {
        case STATE_BUTTON_UP:
            /* CHECK TRANSITION CONDITIONS */
            if( !gpioRead( config->tecla ) )
            {
            	config->fsmButtonState = STATE_BUTTON_FALLING;
            }
            break;

        case STATE_BUTTON_FALLING:
            /* ENTRY */

            /* CHECK TRANSITION CONDITIONS */
            if( config->contFalling >= DEBOUNCE_TIME )
            {
                if( !gpioRead( config->tecla ) )
                {
                	config->fsmButtonState = STATE_BUTTON_DOWN;

                    /* ACCION DEL EVENTO !*/
                    buttonPressed(config);
                }
                else
                {
                	config->fsmButtonState = STATE_BUTTON_UP;
                }

                config->contFalling = 0;
            }

            config->contFalling++;

            /* LEAVE */
            break;

        case STATE_BUTTON_DOWN:
			/* CHECK TRANSITION CONDITIONS */
			if( gpioRead( config->tecla ) )
			{
				config->fsmButtonState = STATE_BUTTON_RISING;
			}
			break;

        case STATE_BUTTON_RISING:
            /* ENTRY */

            /* CHECK TRANSITION CONDITIONS */

            if( config->contRising >= DEBOUNCE_TIME )
            {
                if( gpioRead( config->tecla ) )
                {
                	config->fsmButtonState = STATE_BUTTON_UP;

                    /* ACCION DEL EVENTO ! */
                    buttonReleased(config);
                }
                else
                {
                	config->fsmButtonState = STATE_BUTTON_DOWN;
                }
                config->contRising = 0;
            }
            config->contRising++;

            /* LEAVE */
            break;

        default:
            fsmButtonError(config);
            break;
    }
}
