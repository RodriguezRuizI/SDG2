

#ifndef SRC_VIEW_KEYPAD_H_
#define SRC_VIEW_KEYPAD_H_

#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include "../view/display.h"
//#include "../threads.h"


#define MAX_PIN 4

//Definición de las conexiones entre el teclado
//y la raspberry
//Los números representan los pines GPIO
#define GPIO_R1 5
#define GPIO_R2 6
#define GPIO_R3 13
#define GPIO_R4 26

#define GPIO_C1 12
#define GPIO_C2 16
#define GPIO_C3 20
#define GPIO_C4 21

char key[MAX_PIN][MAX_PIN];
int row_pin[MAX_PIN];
int col_pin[MAX_PIN];


char* scan_key();
char* scan_chain(int max_length);
char* scan_chain_stop(int max_length);
void set_up_keypad();
void* scan_key_thread();
int scan_num();
float scan_float();

#endif /* SRC_VIEW_KEYPAD_H_ */
