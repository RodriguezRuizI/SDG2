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
volatile int flags = 0;

//TABLA DE TRANSICIONES
fsm_trans_t transition_table[] = {
		{WAIT_START, CompruebaPlayerStart,WAIT_NEXT,InicializaPlayer},
		{WAIT_NEXT,CompruebaNuevaNota,WAIT_END,ActualizaPlayer},
		{WAIT_NEXT,CompruebaPlayerStop,WAIT_START,StopPlayer},
		{WAIT_END,CompruebaNuevaNota,WAIT_NEXT,ComienzaNuevaNota},
		{WAIT_END,CompruebaFinalMelodia,WAIT_START,FinalMelodia},
		{-1, NULL, -1, NULL }
};

//Funciones de entrada
int CompruebaPlayerStart(fsm_t* this){
	if(flags & FLAG_PLAYER_START){
	return 0;
	}
	return 1;
}

int CompruebaPlayerStop(fsm_t* this){
	if(flags & FLAG_PLAYER_STOP){
		return 0;
	}
	return 1;
}

int CompruebaNuevaNota(fsm_t* this){
	if(flags& FLAG_PLAYER_END){
		return 0;
	}
	return 1;
}

int CompruebaNotaTimeout(fsm_t* this){
	if(flags & FLAG_NOTA_TIMEOUT){
			return 0;
		}
	return 1;
}

int CompruebaFinalMelodia(fsm_t* this){
	if(flags & FLAG_PLAYER_END){
		return 0;
	}
	return 1;
}

//Funciones de salida
void InicializaPlayer(fsm_t* this){
TipoSistema* new = this->user_data;
new->player.posicion_nota_actual = 0;
new->player.frecuencia_nota_actual = new->player.melodia->frecuencias[0];
new->player.duracion_nota_actual = new->player.melodia->duraciones[0];
printf("\n Sistema Iniciado \n");
softToneWrite(GPIO_PIN, new->player.frecuencia_nota_actual);
}

void StopPlayer(fsm_t* this){
	softToneWrite (GPIO_PIN, 0);
}
void ComienzaNuevaNota(fsm_t* this){
	TipoSistema* new = this->user_data;
	softToneWrite(GPIO_PIN, new->player.duracion_nota_actual);
}
void ActualizaPlayer(fsm_t* this){
	TipoSistema* new = this->user_data;
	new->player.posicion_nota_actual ++;
	new->player.frecuencia_nota_actual = new->player.melodia->frecuencias[new->player.posicion_nota_actual];
	new->player.duracion_nota_actual = new->player.melodia->duraciones[new->player.posicion_nota_actual];
}

void FinalMelodia(fsm_t* this){
	TipoSistema* new = this->user_data;
	flags = 0xFF;
		if(new->player.posicion_nota_actual	==	new->player.melodia->num_notas-1){
			flags = FLAG_PLAYER_END;
		}
}
