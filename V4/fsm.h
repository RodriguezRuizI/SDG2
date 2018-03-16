/*
 * fsm.h
 *
 *  Created on: 1 de mar. de 2016
 *      Author: José Manuel Moya Fernández
 */

#ifndef FSM_H_
#define FSM_H_

typedef struct fsm_t fsm_t;

typedef int (*fsm_input_func_t) (fsm_t*);
typedef void (*fsm_output_func_t) (fsm_t*);

//Struct que nos permite saber el origen, destino,
//funci�n de entrada y salida del aut�mata

typedef struct fsm_trans_t {
  int orig_state;
  fsm_input_func_t in;
  int dest_state;
  fsm_output_func_t out;
} fsm_trans_t;

//Struct que nos da el estado actual y los datos que le pasa el usuario

struct fsm_t {
  int current_state;
  fsm_trans_t* tt;
  void* user_data;
};

//Funciones que intervienen en la m�quina de estados

fsm_t* fsm_new (int state, fsm_trans_t* tt, void* user_data);
void fsm_init (fsm_t* this, int state, fsm_trans_t* tt, void* user_data);
void fsm_fire (fsm_t* this);
void fsm_destroy (fsm_t* this);

#endif /* FSM_H_ */
