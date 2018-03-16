/*
 * piMusicBox_2.h
 *
 *  Created on: 11 de sep. de 2017
 *      Author: FFM
 */

#ifndef PIMUSICBOX_3_H_
#define PIMUSICBOX_3_H_

#include <stdio.h> //para usar printf
#include <stdlib.h> //para poder usar null
#include "kbhit.h" // Para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas
#include "estados.h" //para usar las funciones y estructuras definidas

#define GPIO_PIN 18 // Pin de salida de la raspi
#define CLK_FMS 100 //Reloj usado en el delay

extern int frecuenciaDespacito[];
extern int tiempoDespacito[];
extern int frecuenciaGOT[];
extern int tiempoGOT[];
extern int frecuenciaTetris[];
extern int tiempoTetris[];
extern int frecuenciaStarwars[];
extern int tiempoStarwars[];

//Posibles estados de la máquina de estados

typedef enum{
	WAIT_START,
	WAIT_NEXT,
	WAIT_END
}TipoEstadosSistema;

#define MAX_NUM_TARJETAS	5 //Maximo número de tarjetas del sistema
#define MAX_NUM_NOTAS 		600 //Maximo número de notas de la cancion
#define MAX_NUM_CHAR_NOMBRE	100 //Máximo número de caracteres del nombre
#define MAX_NUM_CHAR_UID	100

#define FLAG_CARD_IN // Flag de la tarjeta de entrada
#define FLAG_SYSTEM_START // Flag que hace empezar el sistema
#define FLAG_VALID_CARD // Flag que valida la tarjeta
#define FLAG_SYSTEM_END // Flag que finaliza el funcionamiento del sistema

typedef struct {
	char nombre[MAX_NUM_CHAR_NOMBRE]; // String con el nombre de la melodia
	int frecuencias[MAX_NUM_NOTAS]; // Array con las frecuencias de las notas de la melodia
	int duraciones[MAX_NUM_NOTAS]; // Array con las duraciones de las notas de la melodia
	int num_notas; // Numero de notas de que consta la melodia
} TipoMelodia;

typedef struct {
	int posicion_nota_actual;	// Valor correspondiente a la posicion de la nota actual en los arrays de frecuencias y duraciones
	int frecuencia_nota_actual; // Valor correspondiente a la frecuencia de la nota actual
	int duracion_nota_actual; // Valor correspondiente a la duracion de la nota actual

	TipoMelodia* melodia; // Puntero que nos deja acceder a TipoMelodia y sus parámetros
	tmr_t* myTimer; //Puntero que nos deja acceder al struct timer y a sus parámetros

} TipoPlayer;

typedef struct {
	//Uid uid;  // Identificador correspondiente a la tarjeta (tipo de datos complejo definido en liberia control RFID)
	TipoMelodia melodia;
} TipoTarjeta;

typedef struct {
	TipoPlayer player; // Reproductor de melodias

	int num_tarjetas_activas; // Numero de tarjetas validas

	TipoTarjeta tarjetas_activas[MAX_NUM_TARJETAS]; // Array con todas las tarjetas validas

	//Uid uid_tarjeta_actual; // Identificador de la tarjeta actual (tipo de datos complejo definido en liberia control RFID)

	int pos_tarjeta_actual; // Posicion de la tarjeta actual en el array de tarjetas validas

	char uid_tarjeta_actual_string[MAX_NUM_CHAR_UID]; // Identificador de la tarjeta actual a modo de string de caracteres

	TipoEstadosSistema estado; // Variable que almacena el estado actual del sistema

	char teclaPulsada; // Variable que almacena la ultima tecla pulsada

	int debug; // Variable que habilita o deshabilita la impresion de mensajes por salida estandar

} TipoSistema;

//Funciones para inicializar el sistema y meterle un delay
void fsm_setup(fsm_t*);
int systemSetup (void);
void delay_until (unsigned int next);

#endif /* PIMUSICBOX_3_H_ */
