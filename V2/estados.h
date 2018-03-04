/*
 * estados.h
 *
 *  Created on: 23 de feb. de 2018
 *      Author: alumno
 */

#ifndef ESTADOS_H_
#define ESTADOS_H_



#endif /* ESTADOS_H_ */

#include <stdlib.h> // para poder usar NULL
#include <stdio.h> // para poder usar printf
#include <time.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <softTone.h>
#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas
#include "piMusicBox_2.h"
#include "fsm.h" // para poder crear y ejecutar la máquina de estados


//Funciones de entrada
int compruebaPlayerStart(fsm_t* this);
int compruebaPlayerStop(fsm_t* this);
int compruebaNuevaNota(fsm_t* this);
int compruebaNotaTimeout(fsm_t* this);
int compruebaFinalMelodia(fsm_t* this);

//Funciones de salida
void inicializaPlayer(fsm_t* this);
void stopPlayer(fsm_t* this);
void comienzaNuevaNota(fsm_t* this);
void actualizaPlayer(fsm_t* this);
void finalMelodia(fsm_t* this);
