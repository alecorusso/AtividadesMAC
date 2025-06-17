// Código do carrinho seguidor de linha com infravermelho e ultrassom
// Feito por Alexander Oliveira e Matheus Viana
// Versão 1.0

#include <zephyr.h>             // Funções básicas do Zephyr (ex: k_msleep)
#include <drivers/gpio.h>       // API para controle de GPIO
#include "pwm.h"                // API para controle de PWM

// Ultrassom
#define TPM1_IRQ_LINE TPM1_IRQn  // relaciona a interrupção ao timer TPM1
#define TPM2_IRQ_LINE TPM2_IRQn  // relaciona a interrupção ao timer TPM2
#define TPM_IRQ_PRIORITY 1      // define a prioridade da interrupção
#define pinoTrigger 1 //PTB1
#define pinoEchoUP 20 //PTE20
#define pinoEchoDOWN 2 //PTB2
#define TPM_MOD_ULTRASSOM 37500
#define frequencia_PWM 0.01 // ciclos/ms
#define velocidade_do_som 34 //cm/ms
volatile uint16_t instante_up = 0; // Armazena instante (em ticks) da borda de subida do sinal de Echo
volatile uint16_t instante_down = 0; // Armazena instante (em ticks) da borda de descida do sinal de Echo

// Sensores Infravermelho e motores
#define INPUT_PORT_E  "GPIO_4"   // Porta E
#define INPUT_PORT_C  "GPIO_2"   // Porta C
#define INPUT_PIN_DIREITO   29   // PTE29 (sensor direito)
#define INPUT_PIN_ESQUERDO   6   // PTC6 (sensor esquerdo)
#define TPM_MOD_MOTORES 3749
uint16_t duty_motor = 3500;

void tpm1_isr(void *arg)
{
       TPM1->STATUS |= TPM_STATUS_CH0F_MASK; // zera a flag que gerou a interrupção
       instante_up = TPM1->CONTROLS[0].CnV; // coloca o valor atual do timer na variável "captured"l
}

void tpm2_isr(void *arg)
{
       TPM2->STATUS |= TPM_STATUS_CH0F_MASK; // zera a flag que gerou a interrupção
       instante_down = TPM2->CONTROLS[0].CnV; // coloca o valor atual do timer na variável "captured"l
}

void main(void)
{
    const struct device *portaE; // Apontador para endereço da porta E para sensor direito
    const struct device *portaC; // Apontador para endereço da porta C para sensor esquerdo
    int valDireito = 0, valEsquerdo = 0; // variáveis para valores de input digital dos sensores esquerdo e direito

    volatile int duracao_sinal = 0; // Variável para armazenar a duração do sinal de Echo em ticks
    volatile float duracao = 1.0;   // Variável para armazenar a duração do sinal de Echo em milissegundos
    volatile float distancia = 1.0; // Variável para armazenar a duração do sinal de Echo em centímetros



    // Ultrassom
    // Conecta a interrupção via Zephyr para o TPM 1
    IRQ_CONNECT(TPM1_IRQ_LINE, TPM_IRQ_PRIORITY, tpm1_isr, NULL, 0);
    irq_enable(TPM1_IRQ_LINE);
 
    // Conecta a interrupção via Zephyr para o TPM 2 
    IRQ_CONNECT(TPM2_IRQ_LINE, TPM_IRQ_PRIORITY, tpm2_isr, NULL, 0);
    irq_enable(TPM2_IRQ_LINE);

    // Inicializa TPM1 para ultrassom com módulo e prescaler desejado
    pwm_tpm_Init(TPM1, TPM_PLLFLL, TPM_MOD_ULTRASSOM, TPM_CLK, PS_128, EDGE_PWM);

    // Inicializa TPM2 para ultrassom com módulo e prescaler desejado
    pwm_tpm_Init(TPM2, TPM_PLLFLL, TPM_MOD_ULTRASSOM, TPM_CLK, PS_128, EDGE_PWM);

    // Configura canal 0 do TPM1 como Output Echo (input capture na borda de subida)
    pwm_tpm_Ch_Init(TPM1, 0, TPM_INPUT_CAPTURE_RISING| TPM_CHANNEL_INTERRUPT, GPIOE, pinoEchoUP);

    // Configura canal 0 do TPM2 como Output Echo (input capture na borda de descida)
    pwm_tpm_Ch_Init(TPM2, 0, TPM_INPUT_CAPTURE_FALLING| TPM_CHANNEL_INTERRUPT, GPIOB, pinoEchoDOWN);

    // Configura canal 1 do TPM1 para trigger do sinal de ultrassom
    pwm_tpm_Ch_Init(TPM1, 1, TPM_PWM_H, GPIOB, pinoTrigger);

    // Define duração do sinal de trigger do ultrassom para 20 microssegundos
    pwm_tpm_CnV(TPM1, 1, 15);



    // Motores
    // Inicializa TPM0 para motores com módulo e prescaler desejado
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MOD_MOTORES, TPM_CLK, PS_128, EDGE_PWM);

    pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOA, 4); // PTA4 para movimento dianteiro do motor direito
    pwm_tpm_Ch_Init(TPM0, 2, TPM_PWM_H, GPIOA, 5); // PTA5 para movimento traseiro do motor direito
    pwm_tpm_Ch_Init(TPM0, 3, TPM_PWM_H, GPIOC, 4); // PTC4 para movimento dianteiro do motor esquerdo
    pwm_tpm_Ch_Init(TPM0, 4, TPM_PWM_H, GPIOD, 4); // PTD4 para movimento traseiro do motor esquerdo


    //Sensores infravermelho
    portaE = device_get_binding(INPUT_PORT_E); // Pega endereço da Porta E
    portaC = device_get_binding(INPUT_PORT_C); // Pega endereço da Porta C
    gpio_pin_configure(portaE, INPUT_PIN_DIREITO, GPIO_INPUT); // Define sensor direito como input
    gpio_pin_configure(portaE, INPUT_PIN_ESQUERDO, GPIO_INPUT); // Define sensor esquedo como input

    while (1){
        while(distancia > 20){
            duracao_sinal = instante_down - instante_up;
            duracao = (duracao_sinal/37500.0)/frequencia_PWM;
            distancia = duracao*velocidade_do_som/2;
            /*printk("Instante ALTO (tick): %d\n", instante_up);
            printk("Instante BAIXO (tick): %d\n", instante_down);
            printk("Duração (ticks): %d\n", duracao_sinal);
            printf("Duração (milisegundos): %f\n", duracao);
            printf("Distancia (centimetros): %f\n", distancia);
            printk("\n");*/
            valDireito = !gpio_pin_get(portaE, INPUT_PIN_DIREITO);
            valEsquerdo = !gpio_pin_get(portaC, INPUT_PIN_ESQUERDO);

            pwm_tpm_CnV(TPM0, 1, 0);          // Motor direito pra frente
            pwm_tpm_CnV(TPM0, 2, duty_motor);

            pwm_tpm_CnV(TPM0, 3, 0);          // Motor esquerdo para frente
            pwm_tpm_CnV(TPM0, 4, duty_motor);

            while(valDireito == 0){
                //printk("entrou regresso direito\n");
                pwm_tpm_CnV(TPM0, 1, duty_motor);
                pwm_tpm_CnV(TPM0, 2, 0);
                valDireito = !gpio_pin_get(portaE, INPUT_PIN_DIREITO);
                valEsquerdo = !gpio_pin_get(portaC, INPUT_PIN_ESQUERDO);
            }
        
            while(valEsquerdo == 0){
                //printk("entrou regresso esquerdo\n");
                pwm_tpm_CnV(TPM0, 3, duty_motor);
                pwm_tpm_CnV(TPM0, 4, 0);
                valDireito = !gpio_pin_get(portaE, INPUT_PIN_DIREITO);
                valEsquerdo = !gpio_pin_get(portaC, INPUT_PIN_ESQUERDO);
            }
            //printk("Valor do PTE20: %d\n", valDireito);
            //printk("Valor do PTC6: %d\n", valEsquerdo);
            //k_msleep(500);
                k_msleep(500);
        }
        while(distancia <= 20){
            pwm_tpm_CnV(TPM0, 1, 0);          
            pwm_tpm_CnV(TPM0, 2, 0);
            pwm_tpm_CnV(TPM0, 3, 0);          
            pwm_tpm_CnV(TPM0, 4, 0);
            //printk("Esperando...\n");
            duracao_sinal = instante_down - instante_up;
            duracao = (duracao_sinal/37500.0)/frequencia_PWM;
            distancia = duracao*velocidade_do_som/2;
            k_msleep(500);
        }
    }
}
