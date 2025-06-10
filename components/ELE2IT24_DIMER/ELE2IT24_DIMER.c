#include "ELE2IT24_DIMER.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"

#define PULSO_TRIAC_US 100

static gpio_num_t zcd_pin;
static gpio_num_t triac_pin;

static float brilho = 0;

static volatile uint16_t delay_triac = 0;
static esp_timer_handle_t triac_timer;

static void triac_callback(void *arg) {
    gpio_set_level(triac_pin, 1);
    esp_rom_delay_us(PULSO_TRIAC_US);
    gpio_set_level(triac_pin, 0);
}

static void IRAM_ATTR zcd_isr_handler(void *arg) {
    if (!esp_timer_is_active(triac_timer)) {
        esp_timer_start_once(triac_timer, delay_triac);
    }
}

void dimer_define_pinos(gpio_num_t zcd_gpio, gpio_num_t triac_gpio) {
    zcd_pin = zcd_gpio;
    triac_pin = triac_gpio;
}

void dimer_iniciar(void) {
    gpio_config_t io_conf = {0};

    // Configuração do pino do TRIAC
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << triac_pin);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    gpio_set_level(triac_pin, 0);  // TRIAC desativado inicialmente

    // Configuração do pino do ZCD
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << zcd_pin);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);


        // Timer TRIAC
        const esp_timer_create_args_t triac_timer_args = {
            .callback = &triac_callback,
            .name = "triac_timer"
        };
        esp_timer_create(&triac_timer_args, &triac_timer);
    
        // ISR ZCD
        gpio_install_isr_service(0);
        gpio_isr_handler_add(zcd_pin, zcd_isr_handler, NULL);
}

void dimer_define_brilho(float porcentagem) {
    if (porcentagem < 0){ porcentagem = 0;}
    if (porcentagem > 100){ porcentagem = 100;}

    brilho = porcentagem;
    delay_triac = (uint16_t)((-6933 * brilho)/100) + 7633;
}