#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define rgbw_mode false
#define led_count 25
#define data_pin 7
#define intervalo_atualizacao 100
#define tempo_blink 100
#define atraso_debounce 400

const uint btn_a_pin = 5;
const uint btn_b_pin = 6;
const uint btn_joy_pin = 22;

const uint led_vermelho_pin = 13;
const uint led_verde_pin = 11;
const uint led_azul_pin = 12;

int numero = 0;

bool buffer_leds[led_count] = {0};

bool leds_ativados = true;

uint32_t ultimo_tempo_a = 0;
uint32_t ultimo_tempo_b = 0;
uint32_t ultimo_tempo_joy = 0;

bool digitos[10][led_count] = {
   {0, 1, 1, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 1, 1, 0},
   
   {0, 0, 1, 0, 0,  
    0, 0, 1, 0, 0,  
    0, 0, 1, 0, 0,  
    0, 1, 1, 0, 0,  
    0, 0, 1, 0, 0},

   {0, 1, 1, 1, 0,  
    0, 1, 0, 0, 0,  
    0, 1, 1, 1, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 1, 1, 0},

   {0, 1, 1, 1, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 1, 1, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 1, 1, 0},

   {0, 1, 0, 0, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 1, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 0, 1, 0},

   {0, 1, 1, 1, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 1, 1, 0,  
    0, 1, 0, 0, 0,  
    0, 1, 1, 1, 0},

   {0, 1, 1, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 1, 1, 0,  
    0, 1, 0, 0, 0,  
    0, 1, 1, 0, 0},

   {0, 1, 0, 0, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 0, 0, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 1, 1, 0},

   {0, 1, 1, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 1, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 1, 1, 0},

   {0, 1, 1, 1, 0,  
    0, 0, 0, 1, 0,  
    0, 1, 1, 1, 0,  
    0, 1, 0, 1, 0,  
    0, 1, 1, 1, 0}
};

static inline void colocar_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

void definir_um_led(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t cor = urgb_u32(r, g, b);
    for (int i = 0; i < led_count; i++)
    {
        if (buffer_leds[i] && leds_ativados)
        {
            colocar_pixel(cor);
        }
        else
        {
            colocar_pixel(0);
        }
    }
}

void atualizar_leds(int numero)
{
    for (int i = 0; i < led_count; i++)
    {
        buffer_leds[i] = digitos[numero][i];
    }
}

void limpar_leds()
{
    for (int i = 0; i < led_count; i++)
    {
        buffer_leds[i] = 0;
    }
    definir_um_led(0, 0, 0);
}

void manipulador_irq_btn(uint gpio, uint32_t eventos)
{
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (gpio == btn_a_pin && tempo_atual - ultimo_tempo_a > atraso_debounce)
    {
        numero = (numero + 1) % 10;
        atualizar_leds(numero);
        definir_um_led(0, 255, 0);  // Definir todos os LEDs como verde
        ultimo_tempo_a = tempo_atual;
    }
    else if (gpio == btn_b_pin && tempo_atual - ultimo_tempo_b > atraso_debounce)
    {
        numero = (numero - 1 + 10) % 10;
        atualizar_leds(numero);
        definir_um_led(0, 255, 0);  // Definir todos os LEDs como verde
        ultimo_tempo_b = tempo_atual;
    }
    else if (gpio == btn_joy_pin && tempo_atual - ultimo_tempo_joy > atraso_debounce)
    {
        leds_ativados = !leds_ativados;
        if (leds_ativados)
        {
            atualizar_leds(numero);
            definir_um_led(0, 255, 0);  // Definir todos os LEDs como verde
        }
        else
        {
            limpar_leds();
        }
        ultimo_tempo_joy = tempo_atual;
    }
}

int main()
{
    stdio_init_all();

    gpio_init(btn_a_pin);
    gpio_set_dir(btn_a_pin, GPIO_IN);
    gpio_pull_up(btn_a_pin);

    gpio_init(btn_b_pin);
    gpio_set_dir(btn_b_pin, GPIO_IN);
    gpio_pull_up(btn_b_pin);

    gpio_init(btn_joy_pin);
    gpio_set_dir(btn_joy_pin, GPIO_IN);
    gpio_pull_up(btn_joy_pin);

    gpio_set_irq_enabled_with_callback(btn_a_pin, GPIO_IRQ_EDGE_FALL, true, &manipulador_irq_btn);
    gpio_set_irq_enabled_with_callback(btn_b_pin, GPIO_IRQ_EDGE_FALL, true, &manipulador_irq_btn);
    gpio_set_irq_enabled_with_callback(btn_joy_pin, GPIO_IRQ_EDGE_FALL, true, &manipulador_irq_btn);

    gpio_init(led_vermelho_pin);
    gpio_set_dir(led_vermelho_pin, GPIO_OUT);
    gpio_put(led_vermelho_pin, 0);

    gpio_init(led_verde_pin);
    gpio_set_dir(led_verde_pin, GPIO_OUT);
    gpio_put(led_verde_pin, 0);

    gpio_init(led_azul_pin);
    gpio_set_dir(led_azul_pin, GPIO_OUT);
    gpio_put(led_azul_pin, 0);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, data_pin, 800000, rgbw_mode);

    atualizar_leds(numero);

    uint32_t ultimo_tempo_blink = 0;
    bool estado_blink = false;

    while (1)
    {
        if (to_ms_since_boot(get_absolute_time()) - ultimo_tempo_blink >= tempo_blink)
        {
            estado_blink = !estado_blink;
            gpio_put(led_vermelho_pin, estado_blink);
            ultimo_tempo_blink = to_ms_since_boot(get_absolute_time());
        }

        definir_um_led(0, 255, 0);  // Definir todos os LEDs como verde
        sleep_ms(intervalo_atualizacao);
    }

    return 0;
}

