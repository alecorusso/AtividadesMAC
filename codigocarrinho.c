#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include "pwm.h"

#define INPUT_PORT_E  "GPIO_4"   // Porta E
#define INPUT_PORT_C  "GPIO_2"   // Porta C
#define INPUT_PIN_DIREITO   29         // PTE29 (sensor direito)
#define INPUT_PIN_ESQUERDO   6          // PTC6 (sensor esquerdo)
#define TPM_MODULE 3749
uint16_t duty = 3500;

void main(void)
{
    const struct device *portaE;
    const struct device *portaC;
    int direcPTE29, direcPTC6, valDireito, valEsquerdo;

    pwm_tpm_Init(TPM0_BASE_PTR, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOA, 4);
    pwm_tpm_Ch_Init(TPM0, 2, TPM_PWM_H, GPIOA, 5);
    pwm_tpm_Ch_Init(TPM0, 3, TPM_PWM_H, GPIOC, 4);
    pwm_tpm_Ch_Init(TPM0, 4, TPM_PWM_H, GPIOD, 4);

    portaE = device_get_binding(INPUT_PORT_E);
    portaC = device_get_binding(INPUT_PORT_C);

    direcPTE29 = gpio_pin_configure(portaE, INPUT_PIN_E, GPIO_INPUT);
    direcPTC6 = gpio_pin_configure(portaC, INPUT_PIN_C, GPIO_INPUT);

    while (1) {
        valDireito = !gpio_pin_get(portaE, INPUT_PIN_DIREITO);
        valEsquerdo = !gpio_pin_get(portaC, INPUT_PIN_ESQUERDO);

        pwm_tpm_CnV(TPM0, 1, 0);          // Motor direito pra frente
        pwm_tpm_CnV(TPM0, 2, duty);

        pwm_tpm_CnV(TPM0, 3, 0);          // Motor esquerdo para frente
        pwm_tpm_CnV(TPM0, 4, duty);

        while(valDireito == 0){
            //printk("entrou 1\n");
            pwm_tpm_CnV(TPM0, 1, duty);
            pwm_tpm_CnV(TPM0, 2, 0);
            valDireito = !gpio_pin_get(portaE, INPUT_PIN_DIREITO);
            valEsquerdo = !gpio_pin_get(portaC, INPUT_PIN_ESQUERDO);
        }
        
        while(valEsquerdo == 0){
            //printk("entrou 2\n");
            pwm_tpm_CnV(TPM0, 3, duty);
            pwm_tpm_CnV(TPM0, 4, 0);
            valDireito = !gpio_pin_get(portaE, INPUT_PIN_DIREITO);
            valEsquerdo = !gpio_pin_get(portaC, INPUT_PIN_ESQUERDO);
        }
        //printk("Valor do PTE20: %d\n", valDireito);
        //printk("Valor do PTC6: %d\n", valEsquerdo);
        //k_msleep(500);
    }
}
