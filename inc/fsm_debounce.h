/*
 * fsm_debounce.h
 *
 *  Created on: Jun 28, 2020
 *      Author: felipe
 */

#ifndef MISINTENTOS_PT1_INC_FSM_DEBOUNCE_H_
#define MISINTENTOS_PT1_INC_FSM_DEBOUNCE_H_
extern void fsmButtonError( tLedTecla* config );
extern void fsmButtonInit( tLedTecla* config );
extern void fsmButtonUpdate( tLedTecla* config );
extern void buttonPressed( tLedTecla* config );
extern void buttonReleased( tLedTecla* config );




#endif /* MISINTENTOS_PT1_INC_FSM_DEBOUNCE_H_ */
