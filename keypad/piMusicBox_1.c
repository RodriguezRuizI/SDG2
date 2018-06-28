#include "tipos.h"


#define PIN_GPIO 18
#define CLK_FMS 10
#define DEBOUNCE_TIME 100
#define miPin 14


//Arrays de las frecuencias de las melodías
int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] = {1200,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};
int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};
int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};
int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};

void delay_until(unsigned int ms);
static int debounceTime1 = 0;
void flags_ISR();
volatile int flags=0;
void callback(union sigval value);




/* FUNCIONES DE ENTRADA O COMPROBACION */
// Conjunto de funciones de comprobacion a implementar conforme al modelo de
// máquina de estados propuesto en el enunciado para la reproduccion

//Cambio de WAIT_START a WAIT_NEXT
int CompruebaPlayerStart (fsm_t* this) {
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_START);
	piUnlock (FLAGS_KEY);
	return result;
}

//Cambio de WAIT_NEXT a WAIT_START
int CompruebaPlayerStop (fsm_t* this) {
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_STOP);
	piUnlock (FLAGS_KEY);
	return result;
}

int CompruebaFinalMelodia (fsm_t* this) {
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	return result;
}

//Cambia de WAIT_END a WAIT_NEXT
int CompruebaNuevaNota (fsm_t* this) {
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	return !result;  //el flag tiene que estar a cero, pero tiene que devolver 1 para poder transicionar al siguiente estado
}

/* FUNCIONES DE SALIDA O ACTUALIZACION */

//Cambio de WAIT_NEXT a WAIT_END")
int CompruebaNotaTimeout (fsm_t* this) {
	int result = 0;
	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_TIMEOUT);
	piUnlock (FLAGS_KEY);
	return result;
	// En particular permite la declaracion de la tabla de transiciones especificada a continuacion
	// El alumno debera crear nuevos procedimientos de actualizacion e incorporarlos a la tabla

}


void InicializaPlayer(fsm_t* this){ //Pasamos a WAIT_NEXT. Inicializa el timer.
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);


	p_player->posicion_nota_actual =0;
	p_player->frecuencia_nota_actual=p_player->melodia->frecuencias[0];
	p_player->duracion_nota_actual=p_player->melodia->duraciones[0];
	//Inicilizar timer
	softToneWrite(PIN_GPIO,p_player->frecuencia_nota_actual);
	p_player->miTimer = tmr_new(callback);
	tmr_startms(p_player->miTimer,p_player->duracion_nota_actual);
	//Quitamos las flags end y stop por si acaso están a 1
	flags = 0;
}


//Reseteo el flag nota timeout y lanzo el timer
void ActualizaPlayer(fsm_t* this){ //Pasa a Wait_end
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);


	printf("Actualizo %d \n",(p_player->posicion_nota_actual));
	fflush(stdout);

	//Cargamos la siguiente nota -- Si no es la ultima
	flags &= ~FLAG_NOTA_TIMEOUT;
    tmr_stop(p_player->miTimer);


	if(p_player->posicion_nota_actual <= p_player->melodia->num_notas){
		printf("\n[ActualizaPlayer][ComienzaNuevaNota][NOTA %i][FREC %i][DUR %i]\n", p_player->posicion_nota_actual, p_player->frecuencia_nota_actual,p_player->duracion_nota_actual);
		fflush(stdout);
		p_player->posicion_nota_actual++;
		p_player->frecuencia_nota_actual=p_player->melodia->frecuencias[p_player->posicion_nota_actual];
		p_player->duracion_nota_actual=p_player->melodia->duraciones[p_player->posicion_nota_actual];
		//printf("Actualizo %d \n",(p_player->posicion_nota_actual));
	}else{
		flags |= FLAG_PLAYER_END;
	}

	 //Si ultima nota -> flag end = 1
}

void ComienzaNuevaNota(fsm_t* this){
	//Pasa a WAIT_NEXT. Pone el FLAG_NOTA_TIMEOUT A 0
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);
	piLock(TECLAS_KEY);
	printf("COMIENZA %d \n",(p_player->posicion_nota_actual));
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	p_player->miTimer= tmr_new(callback);
	tmr_startms(p_player->miTimer, p_player->duracion_nota_actual);
	softToneWrite(PIN_GPIO, p_player->frecuencia_nota_actual);
	//llamar al timer para reiniciarlo en cero y empezar a contar la siguiente nota




}

void StopPlayer(fsm_t* this){
	TipoPlayer* p_player;//llamar a timer stop, supongamos que alguien arranca la tarjeta
	p_player = (TipoPlayer*)(this->user_data);
	softToneWrite (PIN_GPIO, 0);
	flags |= FLAG_PLAYER_STOP;
	tmr_stop (p_player->miTimer);

	piLock(TECLAS_KEY);
	printf("\n[FinalMelodia][FLAG_PLAYER_END]\n");
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	}

void FinalMelodia(fsm_t* this){ //
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);
	if(p_player->posicion_nota_actual>=p_player->melodia->num_notas){
		flags |= FLAG_PLAYER_END;
		printf("\nFinalMelodia\n");
		fflush(stdout);

		//añado un timer
		tmr_stop(p_player->miTimer);
	}


}



//Función que pone a uno el FLAG NOTA TIMEOUT
void callback(union sigval value){
	piLock(FLAGS_KEY);
	flags |= FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);

}




int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) {
	int i=0;
	printf("\nMELODIA INICIALIZADA\n");

    melodia->num_notas = num_notas;
	strcpy(melodia->nombre, nombre);

	for(i=0; i<num_notas; i++){
		melodia->duraciones[i] = array_duraciones[i];
		melodia->frecuencias[i] = array_frecuencias[i];
	}

	return melodia->num_notas;

}

//Inicialización del HW
	int systemSetup (void) {

		wiringPiSetupGpio();
		softToneCreate(PIN_GPIO); //crea una onda en el PIN
		//detecta flancos de subida y de bajada
		wiringPiISR(miPin, INT_EDGE_BOTH, flags_ISR);
		//set_up_keypad();
		return 0;
	}

//software
	void fsm_setup(fsm_t* music_fsm) {
		piLock (FLAGS_KEY);
		flags = 0;
		flagsTarj= 0;
		piUnlock (FLAGS_KEY);

	}


int main (){
	unsigned int next;
	TipoSistema sistema;

	TipoTarjeta mi_tarjeta;
	sistema.player.melodia=&(mi_melodia);


    //Primera máquina de estados
	fsm_trans_t reproductor[] = {
			{ WAIT_START, CompruebaPlayerStart, WAIT_PUSH, InicializaPlayer },
			{ WAIT_PUSH, CompruebaPlayerStop, WAIT_START, StopPlayer },
			{ WAIT_PUSH, CompruebaNotaTimeout, WAIT_END, ActualizaPlayer },
			{ WAIT_END, CompruebaFinalMelodia, WAIT_START, FinalMelodia },
			{ WAIT_END, CompruebaNuevaNota, WAIT_PUSH, ComienzaNuevaNota },
			{-1, NULL, -1, NULL }
		};

    //Segunda máquina de estados
	fsm_trans_t tarjetero[] = {
				{ WAIT_STARTT, CompruebaComienzo, WAIT_CARD, ComienzaSistema },
				{ WAIT_CARD, TarjetaNoDisponible, WAIT_CARD, EsperoTarjeta },
				{ WAIT_CARD, TarjetaDisponible, WAIT_CHECK, LeerTarjeta },
				{ WAIT_CHECK, TarjetaNoValida, WAIT_CARD, DescartaTarjeta },
				{ WAIT_CHECK, TarjetaValida, WAIT_PLAY, ComienzaReproduccion },
				{ WAIT_PLAY, TarjetaDisponible, WAIT_PLAY, ComprueboTarjeta },
				{ WAIT_PLAY, TarjetaNoDisponible, WAIT_STARTT, CancelaReproduccion },
				{ WAIT_PLAY, CompruebaFinalReproduccion, WAIT_STARTT, FinalizaReproduccion },
					{-1, NULL, -1, NULL }
				};

	fsm_t* player_fsm = fsm_new (WAIT_START, reproductor,&(sistema.player));
	fsm_t* detector_fsm = fsm_new (WAIT_STARTT, tarjetero,&(mi_tarjeta));



	// Configuracion e inicializacion del sistema
	systemSetup();
	fsm_setup(player_fsm);
	fsm_setup(detector_fsm);
	next=millis();
	while (1) {

			fsm_fire(detector_fsm);
			fsm_fire(player_fsm);
			next += CLK_FMS;
			delay_until(next);
	}
	fsm_destroy (player_fsm);
	fsm_destroy(detector_fsm);

}

void delay_until (unsigned int next) {
	unsigned int now = millis();

	if (next > now) {
		delay (next - now);
    }

}


//Función que controla el optoacoplador
void flags_ISR(){
	piLock(TECLAS_KEY);
	printf("Tarjeta insertada");
	piUnlock(TECLAS_KEY);
	fflush(stdout);
	if(millis()<debounceTime1) {
		debounceTime1 = millis() + DEBOUNCE_TIME ;
		return;
	}
	int pin =digitalRead(miPin); //Pin para alimentar el optoacoplador
	if(pin == HIGH){     //si el pin esta a nivel alto como tenemos una resistencia
		                 //de pull up en estado de reposo no detecta tarjeta
		piLock (FLAGS_TARJ);
		flagsTarj &= ~FLAG_CARD_IN;
		piUnlock (FLAGS_TARJ);
		debounceTime1 = millis() + DEBOUNCE_TIME ;//para evitar el tiempo de rebote
	}
	else{
	//Si se introduce tarjeta pasamos a nivel bajo
	 //Y forzamos a uno LA FLAG CARD IN que se
	 //comunica con el teclado matricial
		piLock (FLAGS_TARJ);
		flagsTarj |=FLAG_CARD_IN;
		piUnlock (FLAGS_TARJ);


	}
}





