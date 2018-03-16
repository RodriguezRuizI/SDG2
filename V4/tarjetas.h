
/*
 * tarjetas.h
 *
 *  Created on: 16 de mar. de 2018
 *      Author: alumno
 */
#ifndef TARJETAS_H_
#define TARJETAS_H_

#endif /* TARJETAS_H_ */

#include <stdlib.h> // para poder usar NULL
#include <stdio.h> // para poder usar printf
#include <time.h> //para poder usar funciones del timer
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <softTone.h>
#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas
#include "piMusicBox_4.h" //para usar las funciones y estructuras definidas
#include "fsm.h" // para poder crear y ejecutar la máquina de estados
#include "tmr.h" // para poder usar el timer

#define FLAG_SYSTEM_START 0x01// Flag de la tarjeta de entrada
#define FLAG_CARD_IN 0x02 // Flag que hace empezar el sistema
#define FLAG_VALID_CARD 0x04// Flag que valida la tarjeta
#define FLAG_SYSTEM_END 0x08// Flag que finaliza el funcionamiento del sistema


//Funciones de entrada
compruebaComienzo(fsm_t* this);
tarjetaNoDisponible(fsm_t* this);
tarjetaDisponible(fsm_t* this);
tarjetaNoValida(fsm_t* this);
tarjetaValida(fsm_t* this);
compruebaFinalReproduccion(fsm_t* this);

//Funciones de salida
comienzaSistema(fsm_t* this);
esperoTarjeta(fsm_t* this);
leerTarjeta(fsm_t* this);
descartaTarjeta(fsm_t* this);
comienzaReproduccion(fsm_t* this);
cancelaReproduccion(fsm_t* this);
comprueboTarjeta(fsm_t* this);
finalizaReproduccion(fsm_t* this);
