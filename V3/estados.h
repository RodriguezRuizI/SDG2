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
#include "piMusicBox_3.h"
#include "fsm.h" // para poder crear y ejecutar la máquina de estados
#include "tmr.h"
#define FLAGS_KEY 1
#define STD_IO_BUFFER_KEY 2


// FLAGS DEL SISTEMA
#define FLAG_PLAYER_START 0x01
#define FLAG_PLAYER_STOP 0x02
#define FLAG_PLAYER_END 0x03
#define FLAG_NOTA_TIMEOUT 0x04



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
