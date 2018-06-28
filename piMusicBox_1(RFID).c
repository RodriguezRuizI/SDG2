
#include "piMusicBox_1.h"

int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] = {1200,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};
int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};
int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};
int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};

//Variable para realizar los bucles
int i;
int j;
int k;
int h;

//TIMER
tmr_t* timer_nota;

//Pin de la raspberry
#define GPIO_tone 18
#define GPIO_pulsador 20
#define GPIO_pulsador1 21
#define GPIO_pulsador2 26
#define GPIO_pulsador3 27



// FLAGS DEL SISTEMA
#define FLAG_PLAYER_START			0x01
#define FLAG_PLAYER_STOP 			0x02
#define FLAG_PLAYER_END				0x04
#define FLAG_NOTA_TIMEOUT  			0x08
#define FLAG_NOTA_NUEVA  			0x10
#define FLAG_PLAYER_PAUSE  			0x20

// FLAGS DE TARJETA
#define FLAG_SYSTEM_START			0x40
#define FLAG_CARD_OUT				0x80
#define FLAG_CARD_IN				0x100
#define FLAG_INVALID_CARD			0x200
#define FLAG_VALID_CARD				0x400
#define FLAG_CARD_IN2				0x800	
#define FLAG_CARD_OUT2				0x1000
#define FLAG_SYSTEM_END				0x2000


#define	FLAGS_KEY					1
#define	STD_IO_BUFFER_KEY				2

volatile int flags = 0;
typedef int MFRC522_Status_t;

TipoSistema sistema;
TipoMelodia melodia;
TipoMelodia melodia2;
TipoPlayer player;
TipoTarjeta tarjetaGOT;
TipoTarjeta tarjetaTetris;
Uid tarjeta1;
Uid tarjeta2;
Uid tarjetaIni;

//------------------------------------------------------
// FUNCIONES TIMER
//------------------------------------------------------
void boton_isr (){

	if(digitalRead(GPIO_pulsador) == 0){
	piLock(FLAGS_KEY);
	flags|= FLAG_CARD_IN;
	piUnlock(FLAGS_KEY);
	}else{
		piLock(FLAGS_KEY);
		flags|= FLAG_CARD_OUT;
		piUnlock(FLAGS_KEY);
	}

}


void boton_quit (){
	exit(1);
}

void boton_pausa (){
	piLock(FLAGS_KEY);
	flags|= FLAG_PLAYER_PAUSE;
	piUnlock(FLAGS_KEY);
}

void boton_start (){
	piLock(FLAGS_KEY);
	flags|= FLAG_SYSTEM_START;
	piUnlock(FLAGS_KEY);
}


void timer_isr (union sigval value) {
	piLock(FLAGS_KEY);
	flags|= FLAG_NOTA_TIMEOUT;
	piUnlock(FLAGS_KEY);
}

//------------------------------------------------------
// FUNCIONES DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaPlayerStart (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_START);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaPlayerPause (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_PAUSE);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaPlayerStop (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_STOP);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaNuevaNota (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_NUEVA);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaNotaTimeout (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_TIMEOUT);
	piUnlock (FLAGS_KEY);

	return result;
}

int CompruebaFinalMelodia (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);

	return result;
}

//Espera hasta la próxima activación del reloj
void delay_until (unsigned int next) {
	unsigned int now = millis();

	if (next > now) {
		delay (next - now);
	}
}

//------------------------------------------------------
// FUNCIONES DE LA MAQUINA DE ESTADOS TARJETA
//------------------------------------------------------


int CompruebaComienzo (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_SYSTEM_START);
	piUnlock (FLAGS_KEY);

	return result;
}

int TarjetaDisponible (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_CARD_IN);
	piUnlock (FLAGS_KEY);

	return result;
}
int TarjetaNoDisponible (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_CARD_OUT);
	piUnlock (FLAGS_KEY);

	return result;
}
int TarjetaValida (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_VALID_CARD);
	piUnlock (FLAGS_KEY);


	return result;
}

int TarjetaNoValida (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_INVALID_CARD);
	piUnlock (FLAGS_KEY);


	return result;
}

int CompruebaFinalReproduccion (fsm_t* this){
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_SYSTEM_END);
	piUnlock (FLAGS_KEY);


	return result;
}


//------------------------------------------------------
// FUNCIONES PARA INICIALIZAR LA MELODÍA
//------------------------------------------------------

int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) {

	strncpy(melodia->nombre, nombre, 100);
	melodia->num_notas = num_notas;
	for(i=0;i<num_notas;i++) {
		melodia->frecuencias[i]=array_frecuencias[i];
	}
	for(i=0;i<num_notas;i++) {
		melodia->duraciones[i]=array_duraciones[i];
	}

	return melodia->num_notas;
}

void InicializaPlayerAux (TipoPlayer *player, TipoMelodia *melodia){

	piLock (STD_IO_BUFFER_KEY);

	player->melodia = melodia;
	player->posicion_nota_actual = 0;

	player->duracion_nota_actual = player->melodia->duraciones[0];
	player->frecuencia_nota_actual = player->melodia->frecuencias[0];

	piUnlock (STD_IO_BUFFER_KEY);
}
void InicializaTipos(TipoTarjeta *Tarjeta1, TipoTarjeta *Tarjeta2, Uid *tarjeta11, Uid *tarjeta22, TipoMelodia *melodia, TipoMelodia *melodia2, TipoSistema *sistema, Uid *tarjetaIni){



		//UID de la Tarjeta 1

		tarjeta11->size = 4;
		tarjeta11->uidByte[0] = 116;
		tarjeta11->uidByte[1] = 15;
		tarjeta11->uidByte[2] = 171;
		tarjeta11->uidByte[3] = 41;

		//UID de la Tarjeta 2

		tarjeta22->size = 4;
		tarjeta22->uidByte[0] = 25;
		tarjeta22->uidByte[1] = 50;
		tarjeta22->uidByte[2] = 132;
		tarjeta22->uidByte[3] = 19;

		//UID init

		tarjetaIni->size = 4;
		tarjetaIni->uidByte[0] = 0;
		tarjetaIni->uidByte[1] = 0;
		tarjetaIni->uidByte[2] = 0;
		tarjetaIni->uidByte[3] = 0;

		sistema->uid_tarjeta_actual = tarjetaIni;

		Tarjeta1->melodia = melodia;
		Tarjeta1->uid = tarjeta11;

		Tarjeta2->melodia = melodia2;
		Tarjeta2->uid = tarjeta22;

}

void InicializaPlayer (fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);

	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);

	p_player->posicion_nota_actual = 0;
	p_player->duracion_nota_actual = p_player->melodia->duraciones[0];
	p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[0];


	softToneWrite (GPIO_tone, p_player->frecuencia_nota_actual);

	printf("\n[PLAYER][InicializaPlayer][NOTA %d][FREC %d][DURA %d]\n", p_player->posicion_nota_actual+1, p_player->frecuencia_nota_actual, p_player->duracion_nota_actual);
	tmr_startms(timer_nota,sistema.player.duracion_nota_actual);
	piUnlock (STD_IO_BUFFER_KEY);
}

void InicializaSistema(TipoPlayer player, TipoMelodia *melodia, TipoMelodia *melodia2, TipoSistema *sistema, TipoTarjeta *TarjetaGOT, TipoTarjeta *TarjetaTetris, Uid *Tarjeta1, Uid *Tarjeta2){
	
	sistema->uid_tarjeta_actual->size = 4;

	sistema->uid_tarjeta_actual->uidByte[0] = 0;
	sistema->uid_tarjeta_actual->uidByte[1] = 0;
	sistema->uid_tarjeta_actual->uidByte[2] = 0;
	sistema->uid_tarjeta_actual->uidByte[3] = 0;
		
	
	sistema->estado;
	sistema->num_tarjetas_activas= 5;
	sistema->tarjetas_activas[0] = TarjetaGOT;
	sistema->tarjetas_activas[1] = TarjetaTetris;
	sistema->player = player;
}

//------------------------------------------------------
// FUNCIONES DE ACCIÓN
//------------------------------------------------------


//Actualiza la nota
void ActualizarPlayer (fsm_t* this) {
	piLock (FLAGS_KEY);
	flags &= ~FLAG_NOTA_TIMEOUT;
	flags &= ~FLAG_PLAYER_PAUSE;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);

	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);

		p_player->posicion_nota_actual++;
		printf("\n[PLAYER][ActualizaPlayer][NUEVA NOTA (%d de %d)]\n",p_player->posicion_nota_actual+1, p_player->melodia->num_notas);
		fflush(stdout);
		piLock (FLAGS_KEY);
		flags |= FLAG_NOTA_NUEVA;
		piUnlock (FLAGS_KEY);

		if(p_player->posicion_nota_actual+1 == p_player->melodia->num_notas){
			printf("\n[PLAYER][ActualizaPlayer][REPRODUCIDAS TODAS LAS NOTAS]\n");
					fflush(stdout);
					piLock (FLAGS_KEY);
					flags |= FLAG_PLAYER_END;
					piUnlock (FLAGS_KEY);
		}


	piUnlock (STD_IO_BUFFER_KEY);
}



//Reproduce la nueva nota
void ComienzaNuevaNota (fsm_t* this) {

	piLock (FLAGS_KEY);
	flags &= ~FLAG_NOTA_NUEVA;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);

	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);

	if(p_player->posicion_nota_actual+1 == p_player->melodia->num_notas){
		piUnlock (STD_IO_BUFFER_KEY);

		return;
	}else{
		p_player->duracion_nota_actual = p_player->melodia->duraciones[p_player->posicion_nota_actual];
		p_player->frecuencia_nota_actual = p_player->melodia->frecuencias[p_player->posicion_nota_actual];

		printf("\n[PLAYER][ComienzaNuevaNota][NOTA %d][FREC %d][DURA %d]\n", p_player->posicion_nota_actual+1, p_player->frecuencia_nota_actual, p_player->duracion_nota_actual);
		fflush(stdout);
		tmr_startms(timer_nota,sistema.player.duracion_nota_actual);
		//This updates the tone frequency value on the given pin. The tone will be played until you set the frequency to 0.
		softToneWrite (GPIO_tone, p_player->frecuencia_nota_actual);
	}

	piUnlock (STD_IO_BUFFER_KEY);

}

//Detiene la reproducción.
void StopPlayer(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_STOP;
	flags &= ~FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);

	printf("\n[PLAYER][StopPlayer]\n");
	fflush(stdout);
	softToneWrite (GPIO_tone, 0);

	piUnlock (STD_IO_BUFFER_KEY);

}

void PausePlayer (TipoSistema *sistema){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_PAUSE;
	flags &= ~FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);

	printf("\n[PLAYER][Pause]\n");
	fflush(stdout);
	softToneWrite (GPIO_tone, 0);

	piUnlock (STD_IO_BUFFER_KEY);
}


//Avisa cuando se reproduce toda la canción.
void FinalMelodia(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_PLAYER_END;
	flags &= ~FLAG_PLAYER_START;
	flags|= FLAG_SYSTEM_END;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);

	printf("\n[PLAYER][FinalMelodia]\n");
	fflush(stdout);
	softToneWrite (GPIO_tone, 0);

	piUnlock (STD_IO_BUFFER_KEY);
}

//------------------------------------------------------
// FUNCIONES DE ACCIÓN
//------------------------------------------------------

void ComienzaSistema(fsm_t* this){
	
	piLock (FLAGS_KEY);
	flags |= FLAG_CARD_OUT;
	piUnlock (FLAGS_KEY);	

	piLock (STD_IO_BUFFER_KEY);
	printf("[Sistema Inicializado]\n");
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);
}

void EsperoTarjeta(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_CARD_OUT;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	printf("[Esperando Tarjeta...]\n");
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);
	}

void LeerTarjeta(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_CARD_IN;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	printf("[Tarjeta Reconocida]\n");
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);

	TipoSistema *p_sistema;
	p_sistema = (TipoSistema*)(this->user_data);

	FILE *fp;

	char command[100];
	char path[100];

	strcpy(command, "bash /root/MFRC522-python/LeeTarjeta.sh");
	// Open the command for reading.
	fp = popen(command, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}
	// Read the output a line at a time - output it.
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("SALIDA %s", path);
		fflush(stdout);
	}

	fp = fopen("/root/MFRC522-python/uid_leido.txt", "r+");
	// Comprobamos si hay una nueva tarjeta disponible...
	if( fp != NULL)	{
		if (fscanf(fp, "%d,%d,%d,%d",
			&(p_sistema->uid_tarjeta_actual->uidByte[0]),
			&(p_sistema->uid_tarjeta_actual->uidByte[1]),
			&(p_sistema->uid_tarjeta_actual->uidByte[2]),
			&(p_sistema->uid_tarjeta_actual->uidByte[3])) == 4 ) {
			// En caso de haberla la leemos...
			printf("Card found!!!\n");
			fflush(stdout);
			p_sistema->uid_tarjeta_actual->size = 4;
			//strcpy(p_sistema->uid_tarjeta_actual_string, PrintCardUID(p_sistema->uid_tarjeta_actual));

	piLock (STD_IO_BUFFER_KEY);
	printf("[Comprobando Validez...]\n");
	fflush(stdout);
	piUnlock (STD_IO_BUFFER_KEY);

	if(CheckCardValidity(&sistema, &tarjetaGOT, &tarjetaTetris)  == 1) {
		piLock (STD_IO_BUFFER_KEY);
		printf("[Tarjeta introducida valida]\n");
		fflush(stdout);
		piUnlock (STD_IO_BUFFER_KEY);
	piLock (FLAGS_KEY);
	flags |= FLAG_VALID_CARD;
	piUnlock (FLAGS_KEY);


	}else {
		piLock (STD_IO_BUFFER_KEY);
		printf("[Tarjeta introducida no valida]\n");
		fflush(stdout);
		piUnlock (STD_IO_BUFFER_KEY);

		piLock (FLAGS_KEY);
		flags |= FLAG_INVALID_CARD;
		piUnlock (FLAGS_KEY);

			}

		}

}

}

void DescartaTarjeta(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_INVALID_CARD;
	piUnlock (FLAGS_KEY);

	piLock (FLAGS_KEY);
	flags |= FLAG_CARD_OUT;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	printf("[Tarjeta Invalida]");
	piUnlock (STD_IO_BUFFER_KEY);
}

void ComienzaReproduccion(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_VALID_CARD;
	flags|= FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);
	

	
	TipoSistema *p_sistema;
	p_sistema = (TipoSistema*)(this->user_data);
		
	p_sistema->player.melodia = p_sistema->tarjetas_activas[p_sistema->pos_tarjeta_actual]->melodia;

	piLock (FLAGS_KEY);
	flags|= FLAG_PLAYER_START;
	piUnlock (FLAGS_KEY);	

	piLock (STD_IO_BUFFER_KEY);
	printf("[Comienza Reproduccion]");
	piUnlock (STD_IO_BUFFER_KEY);
}
void ComprueboTarjeta(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_CARD_IN;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	printf("[Tarjeta insertada]");
	piUnlock (STD_IO_BUFFER_KEY);
}

void CancelaReproduccion(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_CARD_OUT;
	flags|= FLAG_PLAYER_STOP;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	softToneWrite (GPIO_tone, 0);
	printf("[Tarjeta Retirada]");
	piUnlock (STD_IO_BUFFER_KEY);
}


void FinalReproduccion(fsm_t* this){

	piLock (FLAGS_KEY);
	flags &= ~FLAG_SYSTEM_END;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	printf("[La melodia de la tarjeta ha finalizado]");
	piUnlock (STD_IO_BUFFER_KEY);
}

//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

// int systemSetup (void): procedimiento de configuracion del sistema.
// RealizarÃ¡, entra otras, todas las operaciones necesarias para:
// configurar el uso de posibles librerÃ­as (e.g. Wiring Pi),
// configurar las interrupciones externas asociadas a los pines GPIO,
// configurar las interrupciones periÃ³dicas y sus correspondientes temporizadores,
// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema
int systemSetup (void) {

	piLock (STD_IO_BUFFER_KEY);

	//This initialises wiringPi and assumes that the calling program is going to be using the wiringPi pin numbering scheme.
	//This is a simplified numbering scheme which provides a mapping from virtual pin numbers 0 through 16 to the real underlying Broadcom GPIO pin numbers.
	wiringPiSetupGpio();
	pinMode(GPIO_tone, OUTPUT);
	pinMode(GPIO_pulsador, INPUT);
	pinMode(GPIO_pulsador1, INPUT);
	pinMode(GPIO_pulsador2, INPUT);
	pinMode(GPIO_pulsador3, INPUT);
	pullUpDnControl(GPIO_pulsador, PUD_DOWN);
	pullUpDnControl(GPIO_pulsador1, PUD_DOWN);
	pullUpDnControl(GPIO_pulsador2, PUD_DOWN);
	pullUpDnControl(GPIO_pulsador3, PUD_DOWN);
	wiringPiISR(GPIO_pulsador1, INT_EDGE_RISING, boton_quit);
	wiringPiISR(GPIO_pulsador2, INT_EDGE_RISING, boton_pausa);
	wiringPiISR(GPIO_pulsador3, INT_EDGE_RISING, boton_start);
	wiringPiISR(GPIO_pulsador, INT_EDGE_RISING, boton_isr);
//	wiringPiISR(GPIO_pulsador, INT_EDGE_FALLING, boton_isr2);
	//This creates a software controlled tone pin. You can use any GPIO pin and the pin numbering will be that of the wiringPiSetup() function you used.
	softToneCreate (GPIO_tone);


	piUnlock (STD_IO_BUFFER_KEY);

	return 0;
}

int CheckCardValidity (TipoSistema *sistema, TipoTarjeta *tarjetaGOT, TipoTarjeta *tarjetaTetris){
int check = 0;
for(j=0;j<2;j++) {
		if(sistema->uid_tarjeta_actual->uidByte[0] == sistema->tarjetas_activas[j]->uid->uidByte[0] && sistema->uid_tarjeta_actual->uidByte[1] == sistema->tarjetas_activas[j]->uid->uidByte[1] && sistema->uid_tarjeta_actual->uidByte[2] == sistema->tarjetas_activas[j]->uid->uidByte[2] && sistema->uid_tarjeta_actual->uidByte[3] == sistema->tarjetas_activas[j]->uid->uidByte[3]){
			check = 1;
			sistema->pos_tarjeta_actual = j;
			return check;
		}else{
			check=0;
		}

}
return check;
}

void fsm_setup(fsm_t* MusicBoxPi_fsm) {
	piLock (FLAGS_KEY);
	flags = 0;
	piUnlock (FLAGS_KEY);

	piLock (STD_IO_BUFFER_KEY);
	printf("\nPulse una tecla para iniciar la melodia\n");
	piUnlock (STD_IO_BUFFER_KEY);
}

int main(){
	// Configuracion e inicializacion del sistema
	InicializaMelodia((TipoMelodia*)(&(melodia)), "GOT", frecuenciaGOT, tiempoGOT, 518);
	InicializaMelodia((TipoMelodia*)(&(melodia2)), "Tetris", frecuenciaTetris, tiempoTetris, 55);
	InicializaPlayerAux (&player, &melodia);
	InicializaTipos(&tarjetaGOT, &tarjetaTetris, &tarjeta1, &tarjeta2, &melodia, &melodia2, &sistema, &tarjetaIni);
	InicializaSistema(player, &melodia, &melodia2, &sistema, &tarjetaGOT, &tarjetaTetris, &tarjeta1, &tarjeta2);

	systemSetup();


	unsigned int next;

	// Maquina de estados: lista de transiciones
	// {EstadoOrigen,FunciónDeEntrada,EstadoDestino,FunciónDeSalida}
	fsm_trans_t MusicBoxPi_tabla[] = {
			{ WAIT_START,CompruebaPlayerStart, WAIT_PUSH, InicializaPlayer},
			{ WAIT_PUSH, CompruebaPlayerPause, WAIT_PAUSE, PausePlayer },
			{ WAIT_PAUSE, CompruebaPlayerPause, WAIT_END, ActualizarPlayer },
			{ WAIT_PUSH, CompruebaPlayerStop, WAIT_START, StopPlayer },
			{ WAIT_PUSH, CompruebaNotaTimeout, WAIT_END,ActualizarPlayer},
			{ WAIT_END, CompruebaFinalMelodia, WAIT_START, FinalMelodia},
			{ WAIT_END, CompruebaNuevaNota, WAIT_PUSH, ComienzaNuevaNota},
			{ -1, NULL, -1, NULL },
	};
	
		fsm_trans_t MusicBoxPiTarjeta_tabla[] = {
			{ WAIT_START_SYS, CompruebaComienzo, WAIT_CARD, ComienzaSistema},
			{ WAIT_CARD, TarjetaDisponible, WAIT_CHECK, LeerTarjeta },
			{ WAIT_CARD, TarjetaNoDisponible, WAIT_CARD, EsperoTarjeta },
			{ WAIT_CHECK, TarjetaNoValida, WAIT_CARD, DescartaTarjeta },
			{ WAIT_CHECK, TarjetaValida, WAIT_PLAY, ComienzaReproduccion},
			{ WAIT_PLAY, TarjetaNoDisponible, WAIT_START_SYS, CancelaReproduccion},
			{ WAIT_PLAY, TarjetaDisponible, WAIT_PLAY, ComprueboTarjeta},
			{ WAIT_PLAY, CompruebaFinalReproduccion, WAIT_START_SYS, FinalReproduccion},
			{ -1, NULL, -1, NULL },
	};

	//Creamos la máquina de estados y el timer.
	fsm_t* MusicBoxPi_fsm = fsm_new (WAIT_START, MusicBoxPi_tabla,&(sistema.player));
	fsm_t* MusicBoxPiTarjeta_fsm = fsm_new (WAIT_START_SYS, MusicBoxPiTarjeta_tabla, &sistema);
	timer_nota=tmr_new (timer_isr);

	//Configuración e inicialización del sistema
	fsm_setup (MusicBoxPiTarjeta_fsm);

	next = millis();
	while (1) {
		fsm_fire (MusicBoxPiTarjeta_fsm);
		fsm_fire (MusicBoxPi_fsm);
		next += CLK_MS;
		delay_until (next);
	}

	fsm_destroy (MusicBoxPi_fsm);
	fsm_destroy (MusicBoxPiTarjeta_fsm);

}

