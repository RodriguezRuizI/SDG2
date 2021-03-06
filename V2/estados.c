/*
 * estados.c
 *
 *  Created on: 23 de feb. de 2018
 *      Author: Isabel Rodríguez Ruiz
 */

#include <wiringPi.h>
#include <softTone.h>
#include "string.h"
#include "estados.h"
#include "piMusicBox_2.h"

//TABLA DE TRANSICIONES
fsm_trans_t transition_table[] = {
		{WAIT_START, compruebaPlayerStart,WAIT_NEXT,inicializaPlayer},
		{WAIT_NEXT,compruebaNuevaNota,WAIT_END,actualizaPlayer},
		{WAIT_NEXT,compruebaPlayerStop,WAIT_START,stopPlayer},
		{WAIT_END,compruebaNuevaNota,WAIT_NEXT,comienzaNuevaNota},
		{WAIT_END,compruebaFinalMelodia,WAIT_START,finalMelodia},
		{-1, NULL, -1, NULL }
};

//Funciones de entrada
int compruebaPlayerStart(fsm_t* this){
	if(flags & FLAG_PLAYER_START){
	return 0;
	}
	return 1;
}

int compruebaPlayerStop(fsm_t* this){
	if(flags & FLAG_PLAYER_STOP){
		return 0;
	}
	return 1;
}

int compruebaNuevaNota(fsm_t* this){
	if(flags & FLAG_PLAYER_END){
		return 0;
	}
	return 1;
}

int compruebaNotaTimeout(fsm_t* this){
	if(flags & FLAG_NOTA_TIMEOUT){
			return 0;
		}
	return 1;
}

int compruebaFinalMelodia(fsm_t* this){
	if(flags & FLAG_PLAYER_END){
		return 0;
	}
	return 1;
}

//Funciones de salida
void inicializaPlayer(fsm_t* this){
TipoSistema* new = this->user_data;
new->player.posicion_nota_actual = 0;
new->player.frecuencia_nota_actual = new->player.melodia->frecuencias[0];
new->player.duracion_nota_actual = new->player.melodia->duraciones[0];
printf("\n Sistema Iniciado \n");
softToneWrite(GPIO_PIN, new->player.frecuencia_nota_actual);
}

void stopPlayer(fsm_t* this){
	softToneWrite (GPIO_PIN, 0);
}
void comienzaNuevaNota(fsm_t* this){
	TipoSistema* new = this->user_data;
	softToneWrite(GPIO_PIN, new->player.duracion_nota_actual);
}
void actualizaPlayer(fsm_t* this){
	TipoSistema* new = this->user_data;
	new->player.posicion_nota_actual ++;
	new->player.frecuencia_nota_actual = new->player.melodia->frecuencias[new->player.posicion_nota_actual];
	new->player.duracion_nota_actual = new->player.melodia->duraciones[new->player.posicion_nota_actual];
}

void finalMelodia(fsm_t* this){
	TipoSistema* new = this->user_data;
	flags = 0xFF;
		if(new->player.posicion_nota_actual	==	new->player.melodia->num_notas-1){
			flags = FLAG_PLAYER_END;
		}
}
