/*
 * tipos.h
 *
 *  Created on: 12 mar. 2018
 *      Author: USUARIO
 */

#ifndef TIPOS_H_
#define TIPOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <softTone.h>
#include <time.h>
#include <stdint.h>
#include <signal.h>



typedef struct fsm_t fsm_t;

typedef int (*fsm_input_func_t) (fsm_t*);
typedef void (*fsm_output_func_t) (fsm_t*);

typedef struct fsm_trans_t {
  int orig_state;
  fsm_input_func_t in;
  int dest_state;
  fsm_output_func_t out;
} fsm_trans_t;

struct fsm_t {
  int current_state;
  fsm_trans_t* tt;
  void* user_data;
};

fsm_t* fsm_new (int state, fsm_trans_t* tt, void* user_data);
void fsm_init (fsm_t* this, int state, fsm_trans_t* tt, void* user_data);
void fsm_fire (fsm_t* this);
void fsm_destroy (fsm_t* this);

// AHORA EL .H DE KBHIT


int kbhit(void);
int kbread(void);

//AHORA EL .H DE TMR



struct tmr_t {
    timer_t timerid;
    struct itimerspec spec;
    struct sigevent se;
};
typedef struct tmr_t tmr_t;

typedef void (*notify_func_t) (union sigval);

tmr_t* tmr_new (notify_func_t isr);
void tmr_init (tmr_t* this, notify_func_t isr);
void tmr_destroy(tmr_t* this);
void tmr_startms(tmr_t* this, int ms);
void tmr_stop (tmr_t* this);
//del detector de tarjetas

int TarjetaNoDisponible (fsm_t* this);
int TarjetaDisponible (fsm_t* this);
int TarjetaNoValida (fsm_t* this);
int TarjetaValida(fsm_t* this);
int CompruebaComienzo (fsm_t* this);
int CompruebaFinalReproduccion (fsm_t* this);

void ComienzaSistema(fsm_t* this);
void EsperoTarjeta(fsm_t* this);
void DescartaTarjeta(fsm_t* this);
void LeerTarjeta(fsm_t* this);
void ComienzaReproduccion(fsm_t* this);
void CancelaReproduccion(fsm_t* this);
void ComprueboTarjeta(fsm_t* this);
void FinalizaReproduccion(fsm_t* this);



typedef enum {
	WAIT_STARTT= 3,
	WAIT_CARD = 4,
	WAIT_CHECK= 5,
	WAIT_PLAY= 6} TipoEstadosSistema2;

//AHORA EL .H DE PIMUSICBOX



#define FLAGS_KEY 1
#define STD_IO_BUFFER_KEY 2
#define TECLAS_KEY 3
#define FLAGS_TARJ 4


#define FLAG_PLAYER_START 0x01
#define FLAG_PLAYER_STOP 0x02
#define FLAG_PLAYER_END 0x04
#define FLAG_NOTA_TIMEOUT 0x08

extern int frecuenciaDespacito[];
extern int tiempoDespacito[];
extern int frecuenciaGOT[];
extern int tiempoGOT[];
extern int frecuenciaTetris[];
extern int tiempoTetris[];
extern int frecuenciaStarwars[];
extern int tiempoStarwars[];



extern volatile int flags;

int CompruebaPlayerStart (fsm_t* this);
int CompruebaPlayerStop (fsm_t* this);
int CompruebaFinalMelodia (fsm_t* this);
int CompruebaNuevaNota (fsm_t* this);
int CompruebaNotaTimeout(fsm_t* this);



void InicializaPlayer(fsm_t* this);
void ActualizaPlayer(fsm_t* this);
void StopPlayer(fsm_t* this);
void FinalMelodia(fsm_t* this);
void ComienzaNuevaNota(fsm_t* this);

typedef enum {
	WAIT_START= 0,
	WAIT_PUSH = 1,
	WAIT_END= 2} TipoEstadosSistema;

#define MAX_NUM_TARJETAS	5
#define MAX_NUM_NOTAS 		600
#define MAX_NUM_CHAR_NOMBRE	100
#define MAX_NUM_CHAR_UID	100


extern volatile int flagsTarj;

#define FLAG_CARD_IN 0x01
#define FLAG_SYSTEM_START 0x02
#define FLAG_VALID_CARD 0x04
#define FLAG_SYSTEM_END 0x08




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

	TipoMelodia* melodia;
	//sistema.player.melodia=&(cancion[nombre].melodia); esto no es para ahora
	//rellenar en un futuro
	tmr_t* miTimer;

} TipoPlayer;

typedef uint8_t byte;
// A struct used for passing the UID of a PICC.
typedef struct {
	int		size;			// Number of bytes in the UID. 4, 7 or 10.
	int	uidByte[10];
} Uid;

typedef struct {
	Uid uid;  // Identificador correspondiente a la tarjeta (tipo de datos complejo definido en liberia control RFID)
	TipoMelodia melodia;
} TipoTarjeta;

typedef struct {
	TipoPlayer player; // Reproductor de melodias

	int num_tarjetas_activas; // Numero de tarjetas validas

	TipoTarjeta tarjetas_activas[MAX_NUM_TARJETAS]; // Array con todas las tarjetas validas

	Uid uid_tarjeta_actual; // Identificador de la tarjeta actual (tipo de datos complejo definido en liberia control RFID)

	int pos_tarjeta_actual; // Posicion de la tarjeta actual en el array de tarjetas validas

	char uid_tarjeta_actual_string[MAX_NUM_CHAR_UID]; // Identificador de la tarjeta actual a modo de string de caracteres

	TipoEstadosSistema estado; // Variable que almacena el estado actual del sistema

	char teclaPulsada; // Variable que almacena la ultima tecla pulsada

	int debug; // Variable que habilita o deshabilita la impresion de mensajes por salida estandar
} TipoSistema;



int systemSetup (void);
int InicializaMelodia(TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas);


void softToneWrite (int pin, int freq);
int softToneCreate (int pin);

TipoMelodia mi_melodia;

#endif /* TIPOS_H_ */
