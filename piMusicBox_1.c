
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <softTone.h>

#include "kbhit.h" // Para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas

#include "piMusicBox_1.h"

int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] = {1200,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};
int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};
int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};
int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};

//------------------------------------------------------
//------------------------------------------------------
// INICIO DE LA IMPLEMENTACION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------
//------------------------------------------------------

// Variable global compartida
volatile int flags = 0;

// Funcion de espera hasta la proxima activacion del reloj
void delay_until (unsigned int next) {
	unsigned int now = millis();
	if (next > now) {
		delay (next - now);
    }
}

//------------------------------------------------------
// FUNCIONES DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

// FUNCIONES DE ENTRADA O COMPROBACION DE LA MAQUINA DE ESTADOS
int CompruebaPlayerStart (fsm_t* this) {
	// resultado a devolver segun el estado del flag
	int result;
	// comprobacion del estado del flag
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_START);
	piUnlock (FLAGS_KEY);
	// devuelve el resultado de la comprobacion
	return result;
}

int CompruebaPlayerStop (fsm_t* this) {
	// resultado a devolver segun el estado del flag
	int result;
	// comprobacion del estado del flag
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_STOP);
	piUnlock (FLAGS_KEY);
	// devuelve el resultado de la comprobacion
	return result;
}

int CompruebaNotaTimeout (fsm_t* this) {
	// resultado a devolver segun el estado del flag
	int result;
	// comprobacion del estado del flag
	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_TIMEOUT);
	piUnlock (FLAGS_KEY);
	// devuelve el resultado de la comprobacion
	return result;
}

int CompruebaNuevaNota (fsm_t* this) {
	// resultado a devolver segun el estado del flag
	int result;
	// comprobacion del estado del flag
	piLock (FLAGS_KEY);
	result = (flags & ~FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	// devuelve el resultado de la comprobacion
	return result;
}

int CompruebaFinalMelodia (fsm_t* this) {
	// resultado a devolver segun el estado del flag
	int result;
	// comprobacion del estado del flag
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	// devuelve el resultado de la comprobacion
	return result;
}

// FUNCIONES DE SALIDA O ACCION DE LA MAQUINA DE ESTADOS


void InicializaPlayer (fsm_t* this) {
	TipoSistema *p_player = (TipoSistema *)(this->user_data);
	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);

	p_player->player.posicion_nota_actual = 0;
	p_player->player.frecuencia_nota_actual = p_player->player.melodia->frecuencias[p_player->player.posicion_nota_actual];
	p_player->player.duracion_nota_actual = p_player->player.melodia->duraciones[p_player->player.posicion_nota_actual];

	piLock (STD_IO_BUFFER_KEY);
	printf("\n[PLAYER][InicializaPlayer][COMIENZA MELODIA]");
	piUnlock (STD_IO_BUFFER_KEY);

}



void StopPlayer (fsm_t* this) {
	TipoSistema *p_sistema = (TipoSistema *)(this->user_data);
	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);

	p_sistema->player.posicion_nota_actual = 0;

	piLock (STD_IO_BUFFER_KEY);
	printf("\n[PLAYER][StopPlayer][MELODIA INTERRUMPIDA]");
	piUnlock (STD_IO_BUFFER_KEY);
}

void FinalMelodia (fsm_t *fsm) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);

	// TODO: Final Melodia
	piLock (STD_IO_BUFFER_KEY);
	printf("LED APAGADO\n");
	piUnlock (STD_IO_BUFFER_KEY);
}


void ActualizaPlayer (fsm_t* this) {
	TipoSistema *p_sistema = (TipoSistema *)(this->user_data);
	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);

	// Pasa a la nota en la siguiente posicion
	p_sistema->player.posicion_nota_actual++;
	p_sistema->player.frecuencia_nota_actual = p_sistema->player.melodia->frecuencias[p_sistema->player.posicion_nota_actual];
	p_sistema->player.duracion_nota_actual = p_sistema->player.melodia->duraciones[p_sistema->player.posicion_nota_actual];

	piLock (STD_IO_BUFFER_KEY);
	printf("\n[PLAYER][ActualizaPlayer][NUEVA NOTA (%d DE %d)]", p_sistema->player.posicion_nota_actual, p_sistema->player.melodia->num_notas);
	piUnlock (STD_IO_BUFFER_KEY);
}

void ComienzaNuevaNota (fsm_t* this) {
	TipoSistema *p_sistema = (TipoSistema *)(this->user_data);
	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_START;
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);

	int frecuencia = p_sistema->player.frecuencia_nota_actual;
	softToneWrite(0, frecuencia);

	piLock (STD_IO_BUFFER_KEY);
	printf("\n[PLAYER][ComienzaNuevaNota][NOTA %d][FREC %d][DURA %d]\n", p_sistema->player.posicion_nota_actual, p_sistema->player.frecuencia_nota_actual, p_sistema->player.duracion_nota_actual);
	piUnlock (STD_IO_BUFFER_KEY);
}


//------------------------------------------------------
// void InicializaMelodia (TipoMelodia *melodia)
//------------------------------------------------------



int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) {
	// TODO: A completar por el alumno
	// Nombre de la melodia
	strcpy(melodia->nombre, nombre);
	// Array de frecuencias y duraciones
	int i;
	while(i<num_notas) {
		melodia->frecuencias[i] = array_frecuencias[i];
		melodia->duraciones[i] = array_duraciones[i];
		i++;
	}
	printf("Numero de Notas de la cancion=%i.\n", num_notas);
	//printf("Numero de frec de la cancion=\n",melodia_Patata.frecuencias );
	//printf("Numero de dura de la cancion=\n",melodia_Patata.duraciones );
	//printf("nombre  de la cancion=\n", melodia_Patata.nombre);
	//printf("Numero de Notas de la cancion=\n", melodia_Patata);

	// Numero de notas de la melodia
	melodia->num_notas = num_notas;

	// Devuelves el numero de notas
	return melodia->num_notas;
}

//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

// int systemSetup (void): procedimiento de configuracion del sistema.
// Realizara, entra otras, todas las operaciones necesarias para:
// configurar el uso de posibles librerias (e.g. Wiring Pi),
// configurar las interrupciones externas asociadas a los pines GPIO,
// configurar las interrupciones periodicas y sus correspondientes temporizadores,
// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema
int systemSetup (void) {


		wiringPiSetupGpio();

	pinMode(0, OUTPUT) ; // declaro pin 0 como salida
	softToneCreate(0);

	int x = 0;
	piLock (STD_IO_BUFFER_KEY);
	// sets up the wiringPi library
	if (wiringPiSetupGpio () < 0) {
		printf ("Unable to setup wiringPi\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}
	// Lanzamos thread para exploracion del teclado convencional del PC
	x = piThreadCreate (thread_explora_teclado);
	if (x != 0) {
		printf ("it didn't start!!!\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
	}
	piUnlock (STD_IO_BUFFER_KEY);

	// Exito en la inicializacion
	return 1;
}

//------------------------------------------------------
// PI_THREAD (thread_explora_teclado): Thread function for keystrokes detection and interpretation
//------------------------------------------------------

PI_THREAD (thread_explora_teclado) {
	int teclaPulsada;

	while(1) {
		delay(10); // Wiring Pi function: pauses program execution for at least 10 ms

		piLock (STD_IO_BUFFER_KEY);

		if(kbhit()) {
			teclaPulsada = kbread();

			switch(teclaPulsada) {
				case 's':
					piLock (FLAGS_KEY);
					flags |= FLAG_PLAYER_START;
					piUnlock (FLAGS_KEY);
					break;

				case 't':
					piLock (FLAGS_KEY);
					flags |= FLAG_PLAYER_STOP;
					piUnlock (FLAGS_KEY);
					break;

				case 'q':
					exit(0);
					break;

				default:
					printf("INVALID KEY!!!\n");
					break;
			}
		}

		piUnlock (STD_IO_BUFFER_KEY);
	}
}


int main (){
	TipoSistema sistema;

	// Tabla de transiciones de la maquina de estado
	fsm_trans_t ControlSistema[] = {
		{WAIT_START, CompruebaPlayerStart, WAIT_PUSH, InicializaPlayer},
		{WAIT_PUSH, CompruebaPlayerStop, WAIT_START, StopPlayer},
		{WAIT_PUSH, CompruebaNotaTimeout, WAIT_END, ActualizaPlayer},
		{WAIT_END, CompruebaNuevaNota, WAIT_PUSH, ComienzaNuevaNota},
		{WAIT_END, CompruebaFinalMelodia, WAIT_START, FinalMelodia},
		{-1, NULL, -1, NULL}
	};

	// Inicializacion de la maquina de estados
	fsm_t* ControlSistema_fsm = fsm_new(WAIT_START, ControlSistema, (TipoSistema*)&sistema);

	// Configuracion e inicializacion del sistema
	systemSetup();

	TipoMelodia melodia_actual;
	InicializaMelodia(&(melodia_actual), "Tetris", frecuenciaTetris, tiempoTetris, 55);

	unsigned int next;
	next = millis();

	while (1) {
		fsm_fire(ControlSistema_fsm);
		next += CLK_MS;
		delay_until(next);
	}

	fsm_destroy(ControlSistema_fsm);
}
