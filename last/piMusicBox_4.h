/*
 * piMusicBox_2.h
 *
 *  Created on: 11 de sep. de 2017
 *      Author: FFM
 */

#ifndef PIMUSICBOX_4_H_
#define PIMUSICBOX_4_H_

#include <stdio.h> //para usar printf
#include <stdlib.h> //para poder usar null
#include "estados.h" //para usar las funciones y estructuras definidas

#define GPIO_PIN 18 // Pin de salida de la raspi
#define CLK_FMS 1 //Reloj usado en el delay
#define PIN_ENT 5 //optoacoplador
#define PLAY 6 //boton play
#define PAUSE 12 //boton pause
#define STOP 13 //boton stop
#define VERDE 00 //salida del play
#define BLANCO 01 //salida del pause
#define ROJO 02 //salida del stop
#define DEBOUNCE_TIME 100;
#define DEBOUNCE_TIME_PUL 200;

extern int frecuenciaDespacito[];
extern int tiempoDespacito[];
extern int frecuenciaGOT[];
extern int tiempoGOT[];
extern int frecuenciaTetris[];
extern int tiempoTetris[];
extern int frecuenciaStarwars[];
extern int tiempoStarwars[];

//Posibles estados de la m�quina de estados

typedef enum{
	WAIT_START,
	WAIT_NEXT,
	WAIT_END
}TipoEstadosSistema;

typedef enum{
	WAIT_START2,
	WAIT_CARD,
	WAIT_CHECK,
	WAIT_PLAY
}TipoTarjetasSistema;

#define MAX_NUM_TARJETAS	5 //Maximo n�mero de tarjetas del sistema
#define MAX_NUM_NOTAS 		600 //Maximo n�mero de notas de la cancion
#define MAX_NUM_CHAR_NOMBRE	100 //M�ximo n�mero de caracteres del nombre
#define MAX_NUM_CHAR_UID	100

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

	TipoMelodia* melodia; // Puntero que nos deja acceder a TipoMelodia y sus par�metros
	tmr_t* myTimer; //Puntero que nos deja acceder al struct timer y a sus par�metros

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

#endif /* PIMUSICBOX_4_H_ */
