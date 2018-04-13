/*
 * estados.c
 *
 *  Created on: 23 de feb. de 2018
 *      Author: Isabel Rodríguez Ruiz
 */

#include <wiringPi.h> //para poder usar librerías winringPi
#include <softTone.h> //para poder crear un tono en los GPIOS de la raspi
#include "estados.h" //para usar las funciones y estructuras definidas
#include "tmr.h" //para poder usar las funciones de los timers
#include <stdio.h> //para poder usar printf
#include <stdlib.h> //para poder usar null
#include "piMusicBox_4.h" //para usar las funciones y estructuras definidas

//Variables global de los flags
int flags=0;

//Llamada a la función de callback implementada en otra clase
extern void callback();
extern void up_ISR();
extern void down_ISR();

//TABLA DE TRANSICIONES DEL AUTÓMATA
fsm_trans_t transition_table[] = {
		{WAIT_START, compruebaPlayerStart,WAIT_NEXT,inicializaPlayer},
		{WAIT_NEXT,compruebaNotaTimeout,WAIT_END,actualizaPlayer},
		{WAIT_NEXT,compruebaPlayerStop,WAIT_START,stopPlayer},
		{WAIT_END,compruebaNuevaNota,WAIT_NEXT,comienzaNuevaNota},
		{WAIT_END,compruebaFinalMelodia,WAIT_START,finalMelodia},
		{-1, NULL, -1, NULL }
};


//FUNCIONES DE ENTRADA

/**
 * Comprueba si el valor de flags y de FLAG_PLAYER_START tienen el mismo valor
 * Si esto ocurre devuelve un 1 y salta al siguiente estado si no, devuelve 0.
 * Si salta al siguiente estado el sistema quedará iniciado.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

int compruebaPlayerStart(fsm_t* this){
	int result = 0;
	int pin =digitalRead(PIN_ENT);
	if(pin == 0){
		down_ISR();
	}
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_START);
	piUnlock (FLAGS_KEY);

	return result;
}

/**
 * Comprueba si el valor de flags y de FLAG_PLAYER_STOP tienen el mismo valor
 * Si esto ocurre devuelve un 1 y salta al siguiente estado si no, devuelve 0.
 * Si salta al siguiente estado el sistema quedará parado.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

int compruebaPlayerStop(fsm_t* this){
	int result = 0;
	int pin =digitalRead(PIN_ENT);
	if(pin == 1){
		up_ISR();
	}
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_STOP);
	piUnlock (FLAGS_KEY);
	return result;
}

/**
 * Comprueba si el valor de flags y de FLAG_PLAYER_END tienen el mismo valor
 * Devuelve un 1 cuando la condición sea un 0 ya que implicará que FLAG_PLAYER_END
 * está a 0 y por tanto comprobará siguiente nota. Si devuelve un 0 la canción estará acabada.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

int compruebaNuevaNota(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	return !result;
}

/**
 * Comprueba si el valor de flags y de FLAG_NOTA_TIMEOUT tienen el mismo valor
 * Si esto ocurre devuelve un 1 y salta al siguiente estado si no, devuelve 0.
 * Si salta al siguiente estado significa que la nota actual habrá acabado.
 *
 *@param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

int compruebaNotaTimeout(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_TIMEOUT);
	piUnlock (FLAGS_KEY);
	return result;
}

/**
 * Comprueba si el valor de flags y de FLAG_PLAYER_STOP tienen el mismo valor
 * Si esto ocurre devuelve un 1 y salta al siguiente estado si no, devuelve 0
 * Si salta al siguiente estado significa que la melodía estará acabada.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

int compruebaFinalMelodia(fsm_t* this){
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	return result;
}

//FUNCIONES DE SALIDA

/**
 * Esta función marca el inicio del sistema cuando se pulsa la tecla s.
 * Cuando eso ocurre flags se pone a cero y se pone todos los parámetros
 * de la melodía a cero o en la posición cero.
 * Además activamos el flags nota time out con la duración del timer
 * que tendrá la duración de la nota actual pasada en el array.
 * También sacaremos señal por uno de los pines de la raspi.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

void inicializaPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	piLock (FLAGS_KEY);
	printf("\n Sistema Iniciado \n");
	fflush(stdout);
	flags = 0;
	piUnlock (FLAGS_KEY);
	new->posicion_nota_actual = 0;
	new->frecuencia_nota_actual = new->melodia->frecuencias[0];
	new->duracion_nota_actual = new->melodia->duraciones[0];
	softToneWrite(GPIO_PIN, new->frecuencia_nota_actual);
	free(new->myTimer);
	new->myTimer = tmr_new(callback);
	tmr_startms(new->myTimer, new->duracion_nota_actual);

}

/**
 *	Esta función nos indica si se ha detenido la melodía.
 *	Si es así dejamos de sacar señal por el pin de la raspi detenemos el timer
 *	y además ponemos el FLAG PLAYER STOP a cero para cuando se reinicie el sistema.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

void stopPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	softToneWrite (GPIO_PIN, 0);
	printf("\n Melodia detenida \n");
	fflush(stdout);
	piLock(FLAGS_KEY);
	flags &= ~FLAG_PLAYER_STOP;
	piUnlock(FLAGS_KEY);
	tmr_stop(new->myTimer);


}

/**
 *	Esta función hace el comienzo de la nueva nota. Para ello escribe en el pin de salida
 *	de la raspi la nueva frecuencia que se está reproduciendo. También vuelve a activar
 *	el flag de nota time out con la duración del timer
 * 	que tendrá la duración de la nota actual pasada en el array.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

void comienzaNuevaNota(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	softToneWrite(GPIO_PIN, new->frecuencia_nota_actual);
	free(new->myTimer);
	new->myTimer = tmr_new(callback);
	tmr_startms(new->myTimer,new->duracion_nota_actual);

}

/**
 *	Esta función comprueba si se actualiza la melodía a la siguiente nota.
 *	Para ello desactiva el flag de time out y para el timer.
 *	Después imprime la nota actual por pantalla y comprueba si la nota actual
 *	coincide con la última posición del array. Si llega al final salta el FLAG_PLAYER_END
 *	y se acaba la melodía. Si no, actualiza la posición de la nota su frecuencia y su duración.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

void actualizaPlayer(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	piLock(FLAGS_KEY);
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);
	tmr_stop(new->myTimer);
	printf("\n Nota actual: %i \n", new->posicion_nota_actual);
	printf("\n DuraciÃ³n de la nota actual: %i \n", new->duracion_nota_actual);
	printf("\n Frecuencia de la nota actual: %i \n", new->frecuencia_nota_actual);
	fflush(stdout);

	if(new->posicion_nota_actual != new->melodia->num_notas-1){
		new->posicion_nota_actual ++;
		new->frecuencia_nota_actual = new->melodia->frecuencias[new->posicion_nota_actual];
		new->duracion_nota_actual = new->melodia->duraciones[new->posicion_nota_actual];
	}else{
		piLock(FLAGS_KEY);
		flags |= FLAG_PLAYER_END;
		piUnlock(FLAGS_KEY);
	}
}

/**
 *	Esta función comprueba si se ha acabado la melodía. Para ello desactiva el
 *	FLAG_PLAYER_START y para el timer de forma definitiva.
 *
 *  @param fsm_t* this puntero que nos permite pasar los datos
 *  del player a la maquina de estados para hacer las transiciones
 */

void finalMelodia(fsm_t* this){
	TipoPlayer* new;
	new= (TipoPlayer*) (this->user_data);
	piLock(FLAGS_KEY);
	flags &=  ~FLAG_PLAYER_START; //Desactivamos el FLAG START
	softToneWrite(GPIO_PIN, 0);
	piUnlock(FLAGS_KEY);
	tmr_stop(new->myTimer); //Paro el timer
	printf("\n Melodia acabada \n"); //Lanzamos un mensaje melodía acabada
}


