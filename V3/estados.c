/*
 * estados.c
 *
 *  Created on: 23 de feb. de 2018
 *      Author: Isabel Rodr�guez Ruiz
 */
#include "kbhit.h"
#include <wiringPi.h>
#include <softTone.h>
#include "string.h"
#include "estados.h"
#include "piMusicBox_3.h"
#include "tmr.h"
#include <stdio.h>
#include <stdlib.h>

int flags=0;

extern void callback();

//TABLA DE TRANSICIONES
fsm_trans_t transition_table[] = {
		{WAIT_START, compruebaPlayerStart,WAIT_NEXT,inicializaPlayer},
		{WAIT_NEXT,compruebaNotaTimeout,WAIT_END,actualizaPlayer},
		{WAIT_NEXT,compruebaPlayerStop,WAIT_START,stopPlayer},
		{WAIT_END,compruebaNuevaNota,WAIT_NEXT,comienzaNuevaNota},
		{WAIT_END,compruebaFinalMelodia,WAIT_START,finalMelodia},
		{-1, NULL, -1, NULL }
};


//Funciones de entrada
int compruebaPlayerStart(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_START);
	piUnlock (FLAGS_KEY);

	return result;
}

int compruebaPlayerStop(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_STOP);
	piUnlock (FLAGS_KEY);
	return result;
}

int compruebaNuevaNota(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	return !result;
}

int compruebaNotaTimeout(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_TIMEOUT);
	piUnlock (FLAGS_KEY);
	return result;
}

int compruebaFinalMelodia(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	return result;
}

//Funciones de salida
void inicializaPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	piLock (FLAGS_KEY);
	printf("\n Sistema Iniciado \n");
	fflush(stdout);
	flags = 0;
	piUnlock (FLAGS_KEY);
	new->posicion_nota_actual = 0;
	new->frecuencia_nota_actual = new->melodia->frecuencias[0];
	new->duracion_nota_actual = new->melodia->duraciones[0];
	softToneWrite(GPIO_PIN, new->frecuencia_nota_actual);
	new->myTimer = tmr_new(callback);
	tmr_startms(new->myTimer, new->duracion_nota_actual);

}

void stopPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	softToneWrite (GPIO_PIN, 0);
	printf("\n Melodia detenida \n");
	fflush(stdout);
	piLock(FLAGS_KEY);
	flags &= ~FLAG_PLAYER_STOP;
	piUnlock(FLAGS_KEY);
	tmr_stop(new->myTimer);


}
void comienzaNuevaNota(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	softToneWrite(GPIO_PIN, new->frecuencia_nota_actual);
	new->myTimer = tmr_new(callback);
	tmr_startms(new->myTimer,new->duracion_nota_actual);

}

void actualizaPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	piLock(FLAGS_KEY);
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);
	tmr_stop(new->myTimer);
	printf("\n Nota actual: %i \n", new->posicion_nota_actual);
	printf("\n Duración de la nota actual: %i \n", new->duracion_nota_actual);
	printf("\n Frecuencia de la nota actual: %i \n", new->frecuencia_nota_actual);
	fflush(stdout);

	if(new->posicion_nota_actual != new->melodia->num_notas-1){
		new->posicion_nota_actual ++;
		new->frecuencia_nota_actual = new->melodia->frecuencias[new->posicion_nota_actual];
		new->duracion_nota_actual = new->melodia->duraciones[new->posicion_nota_actual];
	}else{
		piLock(FLAGS_KEY);
		flags |= FLAG_PLAYER_END;
		piUnlock(FLAGS_KEY);
	}
}

void finalMelodia(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	piLock(FLAGS_KEY);
	flags &=  ~FLAG_PLAYER_START;
	piUnlock(FLAGS_KEY);
	tmr_stop(new->myTimer);
	printf("\n Melodia acabada \n");
}


