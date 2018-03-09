/*
 * estados.c
 *
 *  Created on: 23 de feb. de 2018
 *      Author: Isabel Rodríguez Ruiz
 */
#include "kbhit.h"
#include <wiringPi.h>
#include <softTone.h>
#include "string.h"
#include "estados.h"
#include "piMusicBox_3.h"
#include "tmr.h"
#include "tmr.c"
#include <stdlib.h>

volatile int flags=0;


//TABLA DE TRANSICIONES
fsm_trans_t transition_table[] = {
		{WAIT_START, compruebaPlayerStart,WAIT_NEXT,inicializaPlayer},
		{WAIT_NEXT,compruebaNuevaNota,WAIT_END,actualizaPlayer},
		{WAIT_NEXT,compruebaPlayerStop,WAIT_START,stopPlayer},
		{WAIT_END,compruebaNuevaNota,WAIT_NEXT,comienzaNuevaNota},
		{WAIT_END,compruebaFinalMelodia,WAIT_START,finalMelodia},
		{-1, NULL, -1, NULL }
};

int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) {
	int i=0;

	strcpy(melodia->nombre, nombre);

	for(i=0; i< MAX_NUM_NOTAS ; i++){

			melodia->frecuencias[i]=array_frecuencias[i];
	}
	for(i=0; i< MAX_NUM_NOTAS ; i++){
			melodia->duraciones[i]=array_duraciones[i];
		}
	melodia->num_notas=num_notas;

	return melodia->num_notas;
}

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
		return !result; //
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
	InicializaMelodia(new->melodia, "GOT", frecuenciaGOT, tiempoGOT, 518);
	printf("\n Sistema Iniciado \n");
	new->posicion_nota_actual = 0;
	new->frecuencia_nota_actual = new->melodia->frecuencias[0];
	new->duracion_nota_actual = new->melodia->duraciones[0];
	//timer = tmr_new();
	softToneWrite(GPIO_PIN, new->frecuencia_nota_actual);
	tmr_startms(new->myTimer, new->duracion_nota_actual);

}

void stopPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	softToneWrite (GPIO_PIN, 0);
	flags |= FLAG_PLAYER_STOP;
	tmr_stop(new->myTimer);
	printf("\n Melodia detenida \n");

}
void comienzaNuevaNota(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	softToneWrite(GPIO_PIN, new->frecuencia_nota_actual);
	printf("\n Nota actual: %i \n", new->posicion_nota_actual);
	printf("\n DuraciÃ³n de la nota actual: %i \n", new->duracion_nota_actual);
	printf("\n Frecuencia de la nota actual: %i \n", new->frecuencia_nota_actual);
	tmr_startms(new->myTimer,new->duracion_nota_actual);
}
void actualizaPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	new->posicion_nota_actual ++;
	new->frecuencia_nota_actual = new->melodia->frecuencias[new->posicion_nota_actual];
	new->duracion_nota_actual = new->melodia->duraciones[new->posicion_nota_actual];
	tmr_stop(new->myTimer);
	flags = FLAG_PLAYER_END;
}

void finalMelodia(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	if(new->posicion_nota_actual ==	new->melodia->num_notas-1){
		flags |= FLAG_PLAYER_END;
		tmr_stop(new->myTimer);
		printf("\n Melodia acabada \n");
	}
}
