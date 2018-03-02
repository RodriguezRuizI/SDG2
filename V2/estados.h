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
int CompruebaPlayerStart(fsm_t* this);
int CompruebaPlayerStop(fsm_t* this);
int CompruebaNuevaNota(fsm_t* this);
int CompruebaNotaTimeout(fsm_t* this);
int CompruebaFinalMelodia(fsm_t* this);

//Funciones de salida
void InicializaPlayer(fsm_t* this);
void StopPlayer(fsm_t* this);
void ComienzaNuevaNota(fsm_t* this);
void ActulizaPlayer(fsm_t* this);
void FinalMelodia(fsm_t* this);
