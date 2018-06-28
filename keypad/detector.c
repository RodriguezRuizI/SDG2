/*
 * detector.c
 *
 *  Created on: 31 mar. 2018
 *      Author: USUARIO
 */
#include "tipos.h"
#include "keypad.h"
/*
 * Clase para controlar la segunda máquina de estados
 */

//flags de la segunda máquina de estados
volatile int flagsTarj=0;


//FUNCIONES DE ENTRADA DE LA SEGUNDA MÁQUINA DE ESTADOS

//Se saca la tarjeta
int TarjetaNoDisponible (fsm_t* this) {
	int res=0;
	piLock (FLAGS_KEY);
	res = (flagsTarj & FLAG_CARD_IN);
	piUnlock (FLAGS_KEY);
	return !res;
}


//la tarjeta introducida está disponible
int TarjetaDisponible (fsm_t* this) {
	int res=0;
	piLock (FLAGS_KEY);
	res = (flagsTarj & FLAG_CARD_IN);
	piUnlock (FLAGS_KEY);
	return res;
}

//la tarjeta no se asocia con ninguna melodía
int TarjetaNoValida (fsm_t* this) {
	int res=0;
	piLock (FLAGS_KEY);
	res = (flagsTarj & FLAG_VALID_CARD);
	piUnlock (FLAGS_KEY);
	return !res;
}


//La tarjeta está asociada a una melodía
int TarjetaValida(fsm_t* this) {
	int res=0;
	piLock (FLAGS_KEY);
	res = (flagsTarj & FLAG_VALID_CARD);
	piUnlock (FLAGS_KEY);
	return res;
}

//Siempre devuelve uno porque de la detección
//de la tarjeta se encarga el optoacoplador
int CompruebaComienzo (fsm_t* this) {

	return 1;
}

//Se acaba la melodía
int CompruebaFinalReproduccion (fsm_t* this) {
	int res=0;
	piLock (FLAGS_KEY);
	res = (flagsTarj & FLAG_SYSTEM_END);
	piUnlock (FLAGS_KEY);
	return res;
}


//FUNCIONES DE SALIDA

//Aquí se inicializa el teclado matricial
void ComienzaSistema(fsm_t* this){
	piLock(TECLAS_KEY);
	printf("ComienzaSistema \n");
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	//inicializa el teclado matricial;
	set_up_keypad();
}

//el sistema espera a que una tarjeta se introduzca
void EsperoTarjeta(fsm_t* this){

//	piLock(TECLAS_KEY);
	//printf("ESPERANDO TARJETA\n");
	//piUnlock(TECLAS_KEY);
}

//La tarjeta no vale, vuelve a esperar una tarjeta
void DescartaTarjeta(fsm_t* this){
	piLock(TECLAS_KEY);
	printf("DescartaTarjeta \n");
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	piLock(FLAGS_TARJ);
	flagsTarj &= ~FLAG_CARD_IN;
	piUnlock(FLAGS_TARJ);
	piLock(TECLAS_KEY);
	printf("TARJETA NO VALIDA\n");
	piUnlock(TECLAS_KEY);
}


//El sistema lee la tarjeta y en función
//de la tecla que pulsemos inicializa una melodía
//inicializa otra melodía o directamente si
//el botón no está asociado con ninguna
//melodia dice que la tecla no es valida
//y no reproduce nada
void LeerTarjeta(fsm_t* this){
	piLock(TECLAS_KEY);
	printf("LeeTarjeta \n");
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	char* cadena = scan_key(); //te devuelve la tecla pulsada
	switch(cadena[0]){
	case '1':
		InicializaMelodia(&mi_melodia,"Caucasica",frecuenciaDespacito,tiempoDespacito,160);
		piLock(FLAGS_TARJ);
		flagsTarj |= FLAG_VALID_CARD;
		piUnlock(FLAGS_TARJ);
		break;
	case '2':
		InicializaMelodia(&mi_melodia,"Caucasica",frecuenciaGOT,tiempoGOT,518);
		piLock(FLAGS_TARJ);
		flagsTarj |= FLAG_VALID_CARD;
		piUnlock(FLAGS_TARJ);
		break;
	case '3':
		InicializaMelodia(&mi_melodia,"Caucasica",frecuenciaTetris,tiempoTetris,55);
		piLock(FLAGS_TARJ);
		flagsTarj |= FLAG_VALID_CARD;
		piUnlock(FLAGS_TARJ);
		break;
	case '4':
		InicializaMelodia(&mi_melodia,"Caucasica",frecuenciaStarwars,tiempoStarwars,59);
		piLock(FLAGS_TARJ);
		flagsTarj |= FLAG_VALID_CARD;
		piUnlock(FLAGS_TARJ);
		break;
	default:
		piLock(TECLAS_KEY);
		printf("Tecla no valida");
		piUnlock(TECLAS_KEY);
		fflush(stdout);
		piLock(FLAGS_TARJ);
		flagsTarj &= ~FLAG_VALID_CARD;
		piUnlock(FLAGS_TARJ);
		break;
	}


}

//empieza la melodía
void ComienzaReproduccion(fsm_t* this){
piLock(TECLAS_KEY);
printf("Comienza reproducción");
piUnlock(TECLAS_KEY);
fflush(stdout);
piLock(FLAGS_KEY);
flags |= FLAG_PLAYER_START;
piUnlock(FLAGS_KEY);

}

//extraemos la tarjeta
void CancelaReproduccion(fsm_t* this){
	piLock(TECLAS_KEY);
	printf("CancelaReproduccion \n");
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	piLock(FLAGS_KEY);
	flags |= FLAG_PLAYER_END;
	piUnlock(FLAGS_KEY);
}

void ComprueboTarjeta(fsm_t* this){


}

//Ya no hay más notas
void FinalizaReproduccion(fsm_t* this){
	piLock(TECLAS_KEY);
	printf("FinReproduccion \n");
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	piLock(FLAGS_KEY);
	flags |= FLAG_PLAYER_END;
	piUnlock(FLAGS_KEY);

}
