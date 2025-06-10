#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ELE2IT24_DIMER.H"

void app_main(void){

    dimer_define_pinos(22,23);
    dimer_iniciar();

    while (1)
    {
        dimer_define_brilho(50);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    
}