/*
 * Control del teclado matricial
 */

#include "keypad.h"

void debounce_delay(int debounce,int pin);
void output_chain(char* chain);

void debounce_delay(int debounce, int pin){
	while (!digitalRead(col_pin[pin])) {
		delay(debounce);
	}
}
//Sondea el teclado de forma bloqueante
//primero excita las filas y después va por columnas
char* scan_key() {
	int i = 0;
		int j = 0;
		char result;
		char* result_str = (char*)malloc(2*sizeof(char));

		while (j != -1) {
			for (i = 0; i < MAX_PIN && j != -1; i++) {
				pinMode(row_pin[i], OUTPUT);
				digitalWrite(row_pin[i], LOW);
				for (j = 0; j < MAX_PIN; j++) {
					if (!digitalRead(col_pin[j])) {
						result = key[i][j];
						printf("%c \n", result);
						fflush(stdout);
						debounce_delay(1, j);
						j = -1;
						break;
					}
				}
				pinMode(row_pin[i], INPUT);
				pullUpDnControl(row_pin[i], PUD_OFF);
			}
		}

		result_str[0] = result;
		result_str[1] = '\0';
		return result_str;

}

char* scan_chain(int max_length) {
	int i = 0;
	char* chain = (char*)malloc(max_length*sizeof(char));
	strcpy(chain,"");
	char* tmp;
	while (strcmp((tmp = scan_key()), "A") != 0 && strlen(chain) < max_length) {
		if(strcmp(tmp,"B") && strcmp(tmp,"C") && strcmp(tmp,"#") && strcmp(tmp,"*") && strcmp(tmp,"D")){
			strcat(chain, tmp);
		}else if(!strcmp(tmp,"D") && strlen(chain) > 0){
			char* tp = (char*)malloc(sizeof(char)*5);
			char* result_str = (char*)malloc(2*sizeof(char));
			strcpy(tp,"");
			for(i = 0; i < strlen(chain)-1;i++){
				result_str[0] = chain[i];
				result_str[1] = '\0';
				strcat(tp,result_str);
			}
			free(chain);
			chain = tp;
		}
		output_chain(chain);
		free(tmp);
	}
	return chain;
}


int scan_num(){
	char* chain = (char*)malloc(sizeof(char)*5);
	int num = 0;
	strcpy(chain,"");
	chain = scan_chain(10);
	num = atoi(chain);
	free(chain);
	return num;
}

float scan_float(){
	char* chain = (char*)malloc(5*sizeof(char));
	float num = 0;
	char* tmp;
	int i;

	strcpy(chain,"");
	while (strcmp((tmp = scan_key()), "A") && strlen(chain) < 5) {
		if(strcmp(tmp,"B") && strcmp(tmp,"C") && strcmp(tmp,"#") && strcmp(tmp,"D") && strcmp(tmp,"*")){
			strcat(chain, tmp);
		}else if(!strcmp(tmp,"D")){
			char* tp = (char*)malloc(sizeof(char)*5);
			char* result_str = (char*)malloc(2*sizeof(char));
			strcpy(tp,"");
			for(i = 0; i < strlen(chain)-1;i++){
				result_str[0] = chain[i];
				result_str[1] = '\0';
				strcat(tp,result_str);
			}
			free(chain);
			chain = tp;
		}else if(!strcmp(tmp,"*")){
			strcat(chain,".");
		}
		output_chain(chain);
		free(tmp);
	}
	num = atof(chain);
	free(chain);
	return num;
}


char* scan_chain_stop(int max_length) {
	char* chain = (char*)malloc(max_length*sizeof(char));
	char* tmp;
	int cmp;
	int i = 0;

	strcpy(chain,"");

	while (strcmp((tmp = scan_key()), "A") != 0 && strlen(chain) < max_length){
		cmp =strcmp(tmp,"*");
		if(cmp == 0){
			free(chain);
			printf("salgo de pantalla \n");
			fflush(stdout);
			return tmp;
		}
		if(strcmp(tmp,"B") && strcmp(tmp,"C") && strcmp(tmp,"#") && strcmp(tmp,"*") && strcmp(tmp,"D")){
					strcat(chain, tmp);
				}else if(!strcmp(tmp,"D")){
					char* tp = (char*)malloc(sizeof(char)*5);
					char* result_str = (char*)malloc(2*sizeof(char));
					strcpy(tp,"");
					for(i = 0; i < strlen(chain)-1;i++){
						result_str[0] = chain[i];
						result_str[1] = '\0';
						strcat(tp,result_str);
					}
					free(chain);
					chain = tp;
		}
		output_chain(chain);
		fflush(stdout);
		free(tmp);
	}
	return chain;
}

//Inicialización del keypad
void set_up_keypad() {

	int i;

	row_pin[0] = GPIO_R1;
	row_pin[1] = GPIO_R2;
	row_pin[2] = GPIO_R3;
	row_pin[3] = GPIO_R4;

	col_pin[0] = GPIO_C1;
	col_pin[1] = GPIO_C2;
	col_pin[2] = GPIO_C3;
	col_pin[3] = GPIO_C4;

	for (i = 0; i < MAX_PIN; i++) {
		pinMode(col_pin[i], INPUT);
		pullUpDnControl(col_pin[i], PUD_UP);
	}

	for (i = 0; i < MAX_PIN; i++) {
		pinMode(row_pin[i], INPUT);
		pullUpDnControl(row_pin[i], PUD_OFF);
	}

//Definición de las teclas del teclado
	key[0][0] = '1';
	key[0][1] = '2';
	key[0][2] = '3';
	key[0][3] = 'A';
	key[1][0] = '4';
	key[1][1] = '5';
	key[1][2] = '6';
	key[1][3] = 'B';
	key[2][0] = '7';
	key[2][1] = '8';
	key[2][2] = '9';
	key[2][3] = 'C';
	key[3][0] = '*';
	key[3][1] = '0';
	key[3][2] = '#';
	key[3][3] = 'D';


}


void output_chain(char* chain){
	char* displn = (char*)malloc(21*sizeof(char));
	printf("Lleva presionado %s \n",chain);
	if(!strcmp(chain,"")){
		free(displn);
		return;
	}
	sprintf(displn,"Ha elegido: %s",chain);
	free(displn);
}
