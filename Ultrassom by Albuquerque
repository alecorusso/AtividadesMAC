#include <stdio.h>
#include <zephyr.h>
#include <drivers/gpio.h>
#include "pwm.h"

#define TPM_IRQ_LINE TPM1_IRQn
#define TPM_IRQ_PRIORITY 1

#define PINO_TRIGGER 1 // PTB1
#define PINO_ECHO 20   // PTE20

#define TPM_MOD 65500
#define PRESCALER 128
#define CLOCK_FREQ 48000000  // Hz
#define VELOCIDADE_SOM 340.0 // m/s

#define TEMPO_POR_TICK ((float)PRESCALER / CLOCK_FREQ) // em segundos

volatile uint16_t instante = 0;
volatile uint16_t borda1 = 0;
volatile uint16_t borda2 = 0;
volatile uint16_t largPulso = 0;
volatile int troca = 0;

void tpm1_isr(void *arg)
{
    TPM1->STATUS |= TPM_STATUS_CH0F_MASK; // Limpa a flag de interrupção
    instante = TPM1->CONTROLS[0].CnV;

    if (troca == 0)
    {
        borda1 = instante;
        troca = 1;
    }
    else
    {
        borda2 = instante;
        troca = 0;
    }

    if (borda1 > borda2)
    {
        largPulso = borda1 - borda2;
    }
    else
    {
        largPulso = borda2 - borda1;
    }
}

void main(void)
{
    IRQ_CONNECT(TPM_IRQ_LINE, TPM_IRQ_PRIORITY, tpm1_isr, NULL, 0);
    irq_enable(TPM_IRQ_LINE);

    pwm_tpm_Init(TPM1, TPM_PLLFLL, TPM_MOD, TPM_CLK, PS_128, EDGE_PWM);

    pwm_tpm_Ch_Init(TPM1, 0, TPM_INPUT_CAPTURE_BOTH | TPM_CHANNEL_INTERRUPT, GPIOE, PINO_ECHO);
    pwm_tpm_Ch_Init(TPM1, 1, TPM_PWM_H, GPIOB, PINO_TRIGGER);

    uint16_t duracao_sinal = 0;
    float duracao = 0.0, distancia = 0.0;

    while (1)
    {
        // Envia pulso de trigger (20 µs aprox)
        pwm_tpm_CnV(TPM1, 1, 8);
        k_busy_wait(60);
        pwm_tpm_CnV(TPM1, 1, 0);

        k_msleep(50); // aguarda tempo de resposta do sensor

        duracao_sinal = largPulso;
        duracao = duracao_sinal * TEMPO_POR_TICK;
        distancia = (duracao * VELOCIDADE_SOM) / 2.0;

        // Exibe resultados
        printk("Instante ALTO (tick): %d\n", borda1);
        printk("Instante BAIXO (tick): %d\n", borda2);
        printk("Largura do pulso (tick): %d\n", largPulso);
        printk("Duração (ticks): %d\n", duracao_sinal);
        printf("Duração (s): %f\n", duracao);
        printf("Distância (m): %f\n", distancia);
        printk("-----------------------------\n");

        k_msleep(500);
    }
}
