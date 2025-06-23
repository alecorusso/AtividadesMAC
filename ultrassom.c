#include <zephyr.h>             // Funções básicas do Zephyr (ex: k_msleep)
#include <drivers/gpio.h>       // API para controle de GPIO
#include "pwm.h"                // API para controle de PWM

#define TPM1_IRQ_LINE TPM1_IRQn  // relaciona a interrupção ao timer TPM1
#define TPM2_IRQ_LINE TPM2_IRQn  // relaciona a interrupção ao timer TPM2
#define TPM_IRQ_PRIORITY 1      // define a prioridade da interrupção
#define pinoTrigger 1 //PTB1
#define pinoEchoDOWN 20 //PTE20
#define TPM_MOD 37500
#define frequencia_PWM 10 // 
#define velocidade_do_som 34000 //cm/s

volatile uint16_t instante_up = 846; // 846 << tick alto << 847
volatile uint16_t instante_down = 0;

void tpm1_isr(void *arg)
{
       TPM1->STATUS |= TPM_STATUS_CH0F_MASK; // zera a flag que gerou a interrupção
       instante_down = TPM1->CONTROLS[0].CnV; // coloca o valor atual do timer na variável "instante_down"
}

void main(void)
{
    // Conecta a interrupção via Zephyr para o TPM 1
    IRQ_CONNECT(TPM1_IRQ_LINE, TPM_IRQ_PRIORITY, tpm1_isr, NULL, 0);
    irq_enable(TPM1_IRQ_LINE);

    // Inicializa TPM1 com módulo e prescaler desejado
    pwm_tpm_Init(TPM1, TPM_PLLFLL, TPM_MOD, TPM_CLK, PS_128, EDGE_PWM);

    // Configura canal 0 do TPM1 como Output Echo (input capture na borda de subida)
    pwm_tpm_Ch_Init(TPM1, 0, TPM_INPUT_CAPTURE_FALLING| TPM_CHANNEL_INTERRUPT, GPIOE, pinoEchoDOWN);

    // Configura canal 1 do TPM1 para trigger do sinal
    pwm_tpm_Ch_Init(TPM1, 1, TPM_PWM_H, GPIOB, pinoTrigger);

    // Define duração do sinal de trigger para 20 microssegundos
    pwm_tpm_CnV(TPM1, 1, 15);

    int duracao_sinal = 0;
    float duracao = 0;
    float distancia = 0;
    while (1)
    {
        duracao_sinal = instante_down - instante_up;
        duracao = (duracao_sinal/37500.0)/frequencia_PWM;
        distancia = duracao*velocidade_do_som/2;
        printk("Instante ALTO (tick): %d\n", instante_up);
        printk("Instante BAIXO (tick): %d\n", instante_down);
        printk("Duração (ticks): %d\n", duracao_sinal);
        printf("Duração (segundos): %f\n", duracao);
        printf("Distancia (metros): %f\n", distancia);
        printk("\n");
        k_msleep(500);
    }
}

//TICK DE 20 CM ~ 1294
