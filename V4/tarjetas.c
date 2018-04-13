/*
 * tarjetas.c
 *
 *  Created on: 16 de mar. de 2018
 *      Author: alumno
 */


#include <wiringPi.h> //para poder usar librerías winringPi
#include <softTone.h> //para poder crear un tono en los GPIOS de la raspi
#include "estados.h" //para usar las funciones y estructuras definidas
#include "tmr.h" //para poder usar las funciones de los timers
#include <stdio.h> //para poder usar printf
#include <stdlib.h> //para poder usar null
#include "piMusicBox_4.h" //para usar las funciones y estructuras definidas
#include "tarjetas.h"
//TABLA DE TRANSICIONES DEL AUTÓMATA
fsm_trans_t transition_table_tarjeta[] = {
		{WAIT_START2, compruebaComienzo,WAIT_CARD,comienzaSistema},
		{WAIT_CARD,tarjetaDisponible,WAIT_CHECK,leerTarjeta},
		{WAIT_CARD,tarjetaNoDisponible,WAIT_CARD,esperoTarjeta},
		{WAIT_CHECK,tarjetaNoValida,WAIT_CARD,descartaTarjeta},
		{WAIT_CHECK,tarjetaValida,WAIT_PLAY,comienzaReproduccion},
		{WAIT_PLAY,tarjetaDisponible,WAIT_PLAY,comprueboTarjeta},
		{WAIT_PLAY,tarjetaNoDisponible,WAIT_START2,cancelaReproduccion},
		{WAIT_PLAY,compruebaFinalReproduccion,WAIT_START2,finalizaReproduccion},
		{-1, NULL, -1, NULL }
};

//Funciones de entrada
int compruebaComienzo(fsm_t* this){
 return 0;
}
int tarjetaNoDisponible(fsm_t* this){
return 0;
}
int tarjetaDisponible(fsm_t* this){
	return 0;
}
int tarjetaNoValida(fsm_t* this){
	return 0;
}
int tarjetaValida(fsm_t* this){
	return 0;
}
int compruebaFinalReproduccion(fsm_t* this){
	return 0;
}

//Funciones de salida
void comienzaSistema(fsm_t* this){

}
void esperoTarjeta(fsm_t* this){

}
void leerTarjeta(fsm_t* this){

}
void descartaTarjeta(fsm_t* this){

}
void comienzaReproduccion(fsm_t* this){

}
void cancelaReproduccion(fsm_t* this){

}
void comprueboTarjeta(fsm_t* this){

}
void finalizaReproduccion(fsm_t* this){

}
