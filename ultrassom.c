#include <zephyr.h>         
#include <device.h>    
#include <drivers/gpio.h>       
#include "pwm.h"                

#define TPM1_IRQ_LINE TPM1_IRQn  // relaciona a interrupção ao timer TPM1
#define TPM_IRQ_PRIORITY 1       // define a prioridade da interrupção
#define PORT_B       "GPIO_1"    // Nome do controlador GPIO (label no .pio\build\frdm_kl25z\zephyr\zephyr.dts)
#define LED_PIN        18        // Pino PTB18 onde está o LED vermelho
#define PORT_C       "GPIO_2"    // Porta C
#define PORT_E       "GPIO_4"    // Porta E
#define pinoTrigger  21          // PTE21
#define pinoEchoDOWN 20          // PTE20
#define TPM_MOD_ULTRASSOM 7500   // 50 Hz
#define frequencia_PWM_Ultrassom 50 // Hz
#define velocidade_do_som 34550.0  // cm/s
#define TPM_MOD_MOTORES 7500     // 50 Hz
uint16_t duty_motor_direito = TPM_MOD_MOTORES*2/3;
uint16_t duty_motor_esquerdo = TPM_MOD_MOTORES*4/9;

volatile uint16_t instante_up = 932; // tick alto ~ 932
volatile uint16_t instante_down = 0; // variável para armazenar tick da borda de descida (instante 20 cm ~~ 1363)
volatile uint16_t ticks[5] = {0};    // vetor para armazenar os últimos 5 valores da borda de descida

void tpm1_isr(void *arg)
{
       TPM1->STATUS |= TPM_STATUS_CH0F_MASK; // zera a flag que gerou a interrupção
       instante_down = TPM1->CONTROLS[0].CnV; // coloca o valor atual do timer na variável "instante_down"

       // Loop para relocar os últimos 4 valores em tick da borda descida
       for(int i = 4; i > 0; i--){
           ticks[i-1] = ticks[i];
       }
       
       ticks[4] = instante_down;  // Armazena o último valor lido em tick da borda de descida no vetor
}

void main(void)
{
    // Ultrassom
    // Conecta a interrupção via Zephyr para o TPM 1
    IRQ_CONNECT(TPM1_IRQ_LINE, TPM_IRQ_PRIORITY, tpm1_isr, NULL, 0);
    irq_enable(TPM1_IRQ_LINE);
    // Inicializa TPM1 com módulo e prescaler desejado
    pwm_tpm_Init(TPM1, TPM_PLLFLL, TPM_MOD_ULTRASSOM, TPM_CLK, PS_128, EDGE_PWM);
    // Configura canal 0 do TPM1 como Output Echo (input capture na borda de descida)
    pwm_tpm_Ch_Init(TPM1, 0, TPM_INPUT_CAPTURE_FALLING | TPM_CHANNEL_INTERRUPT, GPIOE, pinoEchoDOWN);
    // Configura canal 1 do TPM1 para trigger do sinal
    pwm_tpm_Ch_Init(TPM1, 1, TPM_PWM_H, GPIOE, pinoTrigger);
    // Define duração do sinal de trigger para ~20 microssegundos
    pwm_tpm_CnV(TPM1, 1, 100);
    int duracao_sinal = 0;     // ticks
    float duracao = 0;         // s
    float distancia = 0;       // cm

	//printk("aqui\n");
    // Motores
    // Inicializa TPM0 para motores com módulo e prescaler desejado
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MOD_MOTORES, TPM_CLK, PS_128, EDGE_PWM);
    // Configura canais 0, 1, 2 e 3 do TPM0 para controle dos sentidos dos motores
    pwm_tpm_Ch_Init(TPM0, 0, TPM_PWM_H, GPIOC, 1); // PTA4 para movimento dianteiro do motor direito
    pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOC, 2); // PTA5 para movimento traseiro do motor direito
    pwm_tpm_Ch_Init(TPM0, 2, TPM_PWM_H, GPIOC, 3); // PTC4 para movimento dianteiro do motor esquerdo
    pwm_tpm_Ch_Init(TPM0, 3, TPM_PWM_H, GPIOC, 4); // PTD4 para movimento traseiro do motor esquerdo

    //LED
    const struct device *portB = device_get_binding(PORT_B);
    gpio_pin_configure(portB, LED_PIN, GPIO_OUTPUT_ACTIVE);
    gpio_pin_set(portB, LED_PIN, 0);

    k_msleep(1000);

    gpio_pin_set(portB, LED_PIN, 1);

    int flag = 0;
    int parcela = 0;
    while (1){
		parcela = 0;
        for(int i = 0; i < 5; i ++){
        parcela += ticks[i];
        }
        duracao_sinal = parcela/5 - instante_up; // duracao de 20 cm ~ 431
        duracao = (duracao_sinal*1.0/TPM_MOD_ULTRASSOM)/frequencia_PWM_Ultrassom;
        distancia = duracao*velocidade_do_som/2;
        /*printk("Instante ALTO (tick): %d\n", instante_up);
        printk("Instante BAIXO 1 (tick): %d\n", ticks[0]);
        printk("Instante BAIXO 2 (tick): %d\n", ticks[1]);
        printk("Instante BAIXO 3 (tick): %d\n", ticks[2]);
        printk("Instante BAIXO 4 (tick): %d\n", ticks[3]);
        printk("Instante BAIXO 5 (tick): %d\n", ticks[4]);
		*/
        printk("Duração (ticks): %d\n", duracao_sinal);
        //printf("Duração (segundos): %f\n", duracao);
        //printf("Distancia (metros): %f\n", distancia);
		printk("flag: %d\n", flag);
        //printk("\n");
		k_msleep(500);

        if(duracao_sinal > 900 && flag < 5){
            pwm_tpm_CnV(TPM0, 0, duty_motor_direito);     // Motor direito para frente
            pwm_tpm_CnV(TPM0, 1, 0);    
            pwm_tpm_CnV(TPM0, 2, duty_motor_esquerdo);    // Motor esquerdo para frente
            pwm_tpm_CnV(TPM0, 3, 0);
            flag = 0;   
        }

        else if (900 > duracao_sinal && duracao_sinal > 500 && flag < 5){
            pwm_tpm_CnV(TPM0, 0, duty_motor_direito/2);     // Motor direito para frente
            pwm_tpm_CnV(TPM0, 1, 0);    
            pwm_tpm_CnV(TPM0, 2, duty_motor_esquerdo/2);    // Motor esquerdo para frente
            pwm_tpm_CnV(TPM0, 3, 0);
            flag = 0;
        }

        else if (500 > duracao_sinal && duracao_sinal > 439 && flag < 5){
            pwm_tpm_CnV(TPM0, 0, duty_motor_direito/4);     // Motor direito para frente
            pwm_tpm_CnV(TPM0, 1, 0);    
            pwm_tpm_CnV(TPM0, 2, duty_motor_esquerdo/4);    // Motor esquerdo para frente
            pwm_tpm_CnV(TPM0, 3, 0);
            flag = 0;
        }

        else if (300 < duracao_sinal && duracao_sinal < 419 && flag < 5){
            pwm_tpm_CnV(TPM0, 0, 0);                       // Motor direito para trás
            pwm_tpm_CnV(TPM0, 1, duty_motor_direito/4);    
            pwm_tpm_CnV(TPM0, 2, 0);                       // Motor esquerdo para trás
            pwm_tpm_CnV(TPM0, 3, duty_motor_direito/4);
            flag = 0;
        }

        else if (100 < duracao_sinal && duracao_sinal < 300 && flag < 5){
            pwm_tpm_CnV(TPM0, 0, 0);                       // Motor direito para trás
            pwm_tpm_CnV(TPM0, 1, duty_motor_direito/2);    
            pwm_tpm_CnV(TPM0, 2, 0);                       // Motor esquerdo para trás
            pwm_tpm_CnV(TPM0, 3, duty_motor_direito/2);
            flag = 0;
        }

        else if (duracao_sinal < 100 && flag < 5){
            pwm_tpm_CnV(TPM0, 0, 0);                       // Motor direito para trás
            pwm_tpm_CnV(TPM0, 1, duty_motor_direito);    
            pwm_tpm_CnV(TPM0, 2, 0);                       // Motor esquerdo para trás
            pwm_tpm_CnV(TPM0, 3, duty_motor_direito);
            flag = 0;
        }

        else if (439 > duracao_sinal && duracao_sinal > 419 && flag < 5){
            pwm_tpm_CnV(TPM0, 0, 0);                       // Motor direito travado
            pwm_tpm_CnV(TPM0, 1, 0);    
            pwm_tpm_CnV(TPM0, 2, 0);                       // Motor esquerdo travado
            pwm_tpm_CnV(TPM0, 3, 0);
            flag++;
        }

        else if (439 > duracao_sinal && duracao_sinal > 419 && flag == 5){
            for(int i = 0; i < 8; i++){
                gpio_pin_toggle(portB, LED_PIN);
                k_msleep(300);
            }
            break;
        }
    }
}
