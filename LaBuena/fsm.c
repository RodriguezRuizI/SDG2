/*
 * fsm.c
 *
 *  Created on: 1 de mar. de 2016
 *      Author: Jos√© Manuel Moya Fern√°ndez
 */

#include <stdlib.h>
#include "fsm.h"

/**
 * Crea un nuevo tipo fsm al que le reserva un trozo de memoria de tamaÒo fsm
 *
 * @param state indica el estado actual
 * @param tt pasa el puntero que nos da la informaciÛn de estados
 * @param user_data pasa los datos del usuario
 */
fsm_t* fsm_new (int state, fsm_trans_t* tt, void* user_data){
  fsm_t* this = (fsm_t*) malloc (sizeof (fsm_t));
  fsm_init (this, state, tt, user_data);
  return this;
}

/**
 *Inicializa la m·quina de estados con los par·metros de estado y transiciones
 *
 * @param fsm_t* this puntero que controla los estados y par·metros de la fsm
 * @param state indica el estado actual
 * @param tt pasa el puntero que nos da la informaciÛn de estados
 *@param user_data pasa los datos del usuario
 */

void fsm_init (fsm_t* this, int state, fsm_trans_t* tt, void* user_data){
  this->current_state = state;
  this->tt = tt;
  this->user_data = user_data;
}

/**
 * Libera el espacio ocupado por la m·quina de estados
 *
 * @param fsm_t* this borra a donde apunta el puntero fsm y libera el espacio
 */

void fsm_destroy (fsm_t* this){
  free(this);
}
/**
 * Provoca la transiciÛn de la m·quina de estados de un estado a otro
 * actualizando el estado actual y el destino seg˙n se cumplen las condiciones
 *
 * @param fsm_t* this puntero que controla los estados
 */
void fsm_fire (fsm_t* this){
  fsm_trans_t* t;
  for (t = this->tt; t->orig_state >= 0; ++t) {
    if ((this->current_state == t->orig_state) && t->in(this)) {
      this->current_state = t->dest_state;
      if (t->out)
        t->out(this);
      break;
    }
  }
}

