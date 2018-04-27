/*
 * tmr.c
 *
 *  Created on: 1 de mar. de 2016
 *      Author: Administrador
 */

#include "tmr.h"
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <wiringPi.h>

/**
 * Crea un nuevo timer en la función que se le pasa como parámetro
 *@param notify_func_t isr es una función a introducir
 */

tmr_t* tmr_new (notify_func_t isr){
    tmr_t* this = (tmr_t*) malloc (sizeof (tmr_t));
    tmr_init (this, isr);
    return this;
}
/**
 * Inicializa los parámetros del puntero timer que se le pasan a la función
 * pasada como parámetro.
 *
 * @param tmr_t* this es un puntero al timer
 * @param notify_func_t isr es una función a introducir
 */
void tmr_init (tmr_t* this, notify_func_t isr) {
    this->se.sigev_notify = SIGEV_THREAD;
    this->se.sigev_value.sival_ptr = &(this->timerid);
    this->se.sigev_notify_function = isr;
    this->se.sigev_notify_attributes = NULL;
    timer_create (CLOCK_REALTIME, &(this->se), &(this->timerid));  /* o CLOCK_MONOTONIC si se soporta */
}

/**
 * Destruye el timer y libera el espacio que ocupa
 *
 * @param tmr_t* this puntero que apunta a nuestro timer
 */

void tmr_destroy(tmr_t* this){
    tmr_stop (this);
    free(this);
}

/**
 *Asigna un tiempo periódico al puntero timer
 *
 *@param tmr_t* this puntero que apunta a nuestro timer
 *@param int ms indica el tiempo de duración del timer
 */

void tmr_startms(tmr_t* this, int ms) {
    this->spec.it_value.tv_sec = ms / 1000;
    this->spec.it_value.tv_nsec = (ms % 1000) * 1000000;
    this->spec.it_interval.tv_sec = 0;
    this->spec.it_interval.tv_nsec = 0;
    timer_settime (this->timerid, 0, &(this->spec), NULL);
}
/**
 * Borra el id del timer que estábamos usando para asignarle otro.
 *
 *@param tmr_t* this puntero que apunta a nuestro timer
 */
void tmr_stop (tmr_t* this) {
    timer_delete (this->timerid);
}

