
#include "piMusicBox_4.h" //para usar las funciones y estructuras definidas

#include <wiringPi.h> //usar funciones wiringPi
#include <softTone.h> //para escribir un tono en un pin
#include "string.h" //para poder copiar arryas de char
#include "estados.h" //para usar las funciones y estructuras definidas
#include "tmr.h" //para poder usar el timer
#include <stdio.h> //para poder usar printf

extern fsm_trans_t transition_table[]; //Llama a la tabla de transiciones en estados.c
extern int flags; //Llama a la variable global flags en estados.c

//Funcion privada de callback para inicializar flags
void callback();
void flags_ISR();

static int debounceTime1 = 0;
static int debounceTime2 = 0;
static int debounceTime3 = 0;
static int debounceTime4 = 0;

//Arrays con los posibles parametros de las canciones a reproducir
int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] = {1200,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};
int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};
int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};
int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};

/**
 *Método que inicializa una melodía de la cual pasaremos sus parámetros
 *
 *@param melodia pasa la melodía a reproducir
 *@param nombre pasa el nombre de la melodia
 *@param array_frecuencias pasa el array de frecuencias de la melodia
 *@param array_duraciones pasa el array de duración de las notas
 *@param num_notas pasa el numero total de notas de la melodía pasada
 */

int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) {
	int i=0;

	strcpy(melodia->nombre, nombre);

	for(i=0; i< MAX_NUM_NOTAS ; i++){

			melodia->frecuencias[i]=array_frecuencias[i];
	}
	for(i=0; i< MAX_NUM_NOTAS ; i++){
			melodia->duraciones[i]=array_duraciones[i];
		}
	melodia->num_notas=num_notas;

	return melodia->num_notas;
}

/**
 * Función que pone a cero la variable global flags al inicio de nuestra máquina de estados.
 *
 * fsm_t this pasa como parámetro el puntero que apunta a los parámetros de la música
 */
void fsm_setup(fsm_t* this) {
	piLock (FLAGS_KEY);
	flags = 0;
	piUnlock (FLAGS_KEY);
}

int compruebaBotonPlay(fsm_t* this){
	int pin =digitalRead(PLAY);
	if(pin == 1){
		digitalWrite(VERDE, HIGH);
		digitalWrite(ROJO, LOW);
		digitalWrite(BLANCO, LOW);
	}
	return pin;
}

int compruebaBotonPausa(fsm_t* this){
	int pin =digitalRead(PAUSE);
	if(pin == 1){
		digitalWrite(BLANCO, HIGH);
		digitalWrite(VERDE, LOW);
		digitalWrite(ROJO, LOW);
	}
	return pin;
}

int compruebaBotonStop(fsm_t* this){
	int pin =digitalRead(STOP);
	if(pin == 1){
		digitalWrite(ROJO, HIGH);
		digitalWrite(VERDE, LOW);
		digitalWrite(BLANCO, LOW);
	}
	return pin;
}

void botonStart(){
	if(millis()<debounceTime1) {
		debounceTime2 = millis() + DEBOUNCE_TIME_PUL ;
		return;
	    }
	if(digitalRead(PLAY)==1 && ((flags & FLAG_PLAYER_STOP) || (flags & FLAG_PAUSE))){

		debounceTime2 = millis() + DEBOUNCE_TIME_PUL;
	}
}
void botonStop(){
	if(millis()<debounceTime1) {
		debounceTime3 = millis() + DEBOUNCE_TIME_PUL ;
		return;
	    }
	if((digitalRead(STOP) == 1) && !(flags & FLAG_PLAYER_STOP) && !(flags & FLAG_PLAYER_END)&& !(flags & FLAG_PAUSE)){
		flags &= ~FLAG_PLAYER_STOP;
		debounceTime3 = millis() + DEBOUNCE_TIME_PUL;
	}
}
void botonPause(){
	if(millis()<debounceTime1) {
		debounceTime4 = millis() + DEBOUNCE_TIME_PUL ;
		return;
	    }
	if(digitalRead(PAUSE) == 1 && !(flags & FLAG_PLAYER_STOP) && !(flags & FLAG_PLAYER_END)){
		flags &= ~FLAG_PAUSE;
		debounceTime4 = millis() + DEBOUNCE_TIME_PUL;
	}
}

void flags_ISR(){
	if(millis()<debounceTime1) {
		debounceTime1 = millis() + DEBOUNCE_TIME ;
		return;
	    }
	int pin =digitalRead(PIN_ENT);
	if(pin == HIGH){
		piLock (FLAGS_KEY);
		flags |= FLAG_PLAYER_STOP;
		piUnLock (FLAGS_KEY);
	}
	else{
		piLock (FLAGS_KEY);
		flags |= FLAG_PLAYER_START;
		piUnLock (FLAGS_KEY);
		debounceTime1 = millis() + DEBOUNCE_TIME ;
	}
}

/**
 * Inicia las funciones de wiringPi que permiten sacar una señal
 * por los pines de la raspi
 */
int systemSetup (void) {
	wiringPiSetupGpio();
	pinMode (GPIO_PIN, OUTPUT);
	pinMode (PIN_ENT, INPUT);
	softToneCreate(GPIO_PIN);
	pullUpDnControl (PIN_ENT, PUD_DOWN) ;
	wiringPiISR (PIN_ENT, INT_EDGE_BOTH, flags_ISR);
	return 0;
}

/**
 * Función que le hace un delay al sistema
 * @param unsigned int next que será la variable encargada de asignar el tiempo de delay
 */
void delay_until (unsigned int next) {
	unsigned int now = millis();

	if (next > now) {
		delay (next - now);
    }
}

/**
 *Función de callback que activa el flag de timeout cuando esto es requerido
 */

void callback(){
	piLock (FLAGS_KEY);
	fflush(stdout);
	flags |= FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);
}


int main (){
	TipoSistema sistema; // Creamos una variable tipo sistema
	TipoMelodia melodia; // Creamos una variable tipo melodia
	unsigned int next; // entero sin signo para el delay
	sistema.player.melodia = &melodia; //asignamos el puntero melodia


	//Iniciamos la función de wiringPi que permite sacar la onda por el PIN 18
	systemSetup();

	//Inicializamos una melodía para reproducirla
	InicializaMelodia(sistema.player.melodia, "DESPACITO", frecuenciaDespacito, tiempoDespacito, 160);

	//Inicializa los parámetros que hay que pasarle a la máquina de estados para que funcione
	fsm_t* aux_fsm = fsm_new(WAIT_START, transition_table, &(sistema.player));
	//Pone la variable global flags a cero
	fsm_setup(aux_fsm);
	//asocia al entero sin signo un tiempo en milisegundos
	next = millis();
	while (1) {
		fsm_fire (aux_fsm); //llama a la función que controla la transición de estados
		next += CLK_FMS; //incrementa el tiempo
		delay_until (next); // hace un delay
	}
	fsm_destroy (aux_fsm); //liberamos el espacio ocupado por la máquina de estados
}
