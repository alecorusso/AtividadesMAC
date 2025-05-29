#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include "pwm.h"

#define INPUT_PORT_E  "GPIO_4"   // Porta E
#define INPUT_PORT_C  "GPIO_2"   // Porta B
#define INPUT_PIN_E   29         // PTE29 (sensor direito)
#define INPUT_PIN_C   6          // PTC6 (sensor esquerdo)
#define TPM_MODULE 3749
uint16_t duty = 3500;

void main(void)
{
    const struct device *portaE;
    const struct device *portaC;
    int direcPTE29, direcPTC6, valDireito, valEsquerdo;

    pwm_tpm_Init(TPM1_BASE_PTR, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Init(TPM2_BASE_PTR, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Ch_Init(TPM1, 0, TPM_PWM_H, GPIOE, 20);
    pwm_tpm_Ch_Init(TPM1, 1, TPM_PWM_H, GPIOE, 21);
    pwm_tpm_Ch_Init(TPM2, 0, TPM_PWM_H, GPIOE, 22);
    pwm_tpm_Ch_Init(TPM2, 1, TPM_PWM_H, GPIOE, 23);

    portaE = device_get_binding(INPUT_PORT_E);
    portaC = device_get_binding(INPUT_PORT_C);

    direcPTE29 = gpio_pin_configure(portaE, INPUT_PIN_E, GPIO_INPUT);
    direcPTC6 = gpio_pin_configure(portaC, INPUT_PIN_C, GPIO_INPUT);

    while (1) {
        valDireito = !gpio_pin_get(portaE, INPUT_PIN_E);
        valEsquerdo = !gpio_pin_get(portaC, INPUT_PIN_C);

        if(valDireito == 1){
            pwm_tpm_CnV(TPM1, 0, 0);
            pwm_tpm_CnV(TPM1, 1, duty);
        }else if(valDireito == 0){
            printk("entrou 1\n");
            pwm_tpm_CnV(TPM1, 0, duty);
            pwm_tpm_CnV(TPM1, 1, 0);
        }

        if(valEsquerdo == 1){
            pwm_tpm_CnV(TPM2, 0, 0);
            pwm_tpm_CnV(TPM2, 1, duty);
        }else if(valEsquerdo == 0){
            printk("entrou 2\n");
            pwm_tpm_CnV(TPM2, 0, duty);
            pwm_tpm_CnV(TPM2, 1, 0);
        }
        //printk("Valor do PTE20: %d\n", valDireito);
        //printk("Valor do PTC6: %d\n", valEsquerdo);
        //k_msleep(500);
    }
}
