#ifndef __ELE2IT24_DIMER_H
#define __ELE2IT24_DIMER_H

#include "driver/gpio.h"
#include <stdint.h>

//iniciar a biblioteca
void dimer_iniciar(void);

//definir os pinos do dimmer - ZCD e TRIAC
void dimer_define_pinos(gpio_num_t zcd_gpio, gpio_num_t triac_gpio);

//definir o brilho em porcentagem
void dimer_define_brilho(float porcentagem);

#endif