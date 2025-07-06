#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include "pwm.h"

#define INPUT_PORT_C  "GPIO_2"   // Porta C
#define INPUT_PORT_E  "GPIO_4"   // Porta E
#define pinoDireitoFrente     1  // PTC1
#define pinoDireitoTras       2  // PTC2
#define pinoEsquerdoFrente    3  // PTC3
#define pinoEsquerdoTras      4  // PTC4
#define TPM_MOD_MOTORES 7500
uint16_t duty_motor_direito = TPM_MOD_MOTORES*2/3;
uint16_t duty_motor_esquerdo = TPM_MOD_MOTORES*4/9;

#define pinoSensorDireito   12         // PTC12 (sensor direito)
#define pinoSensorEsquerdo  13         // PTC13 (sensor esquerdo)

void main(void){

    // Motores
    // Inicializa TPM0 com módulo e prescaler desejado
    pwm_tpm_Init(TPM0_BASE_PTR, TPM_PLLFLL, TPM_MOD_MOTORES, TPM_CLK, PS_128, EDGE_PWM);
    // Configura canais 0, 1, 2 e 3 do TPM0 para controle dos sentidos dos motores
    pwm_tpm_Ch_Init(TPM0, 0, TPM_PWM_H, GPIOC, 1);    // Movimento dianteiro motor direito
    pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOC, 2);    // Movimento traseiro motor direito
    pwm_tpm_Ch_Init(TPM0, 2, TPM_PWM_H, GPIOC, 3);    // Movimento dianteiro motor esquerdo
    pwm_tpm_Ch_Init(TPM0, 3, TPM_PWM_H, GPIOC, 4);    // Movimento traseiro motor esquerdo

    // Sensores IV
    // Define variável para endereço da portaC
    const struct device *portaC = device_get_binding(INPUT_PORT_C);
    // Define pinos dos sensores IV como input digital
    gpio_pin_configure(portaC, pinoSensorDireito, GPIO_INPUT);
    gpio_pin_configure(portaC, pinoSensorEsquerdo, GPIO_INPUT);
    int valDireito, valEsquerdo;

    while (1) {
        valDireito = !gpio_pin_get(portaC, pinoSensorEsquerdo);
        valEsquerdo = !gpio_pin_get(portaC, pinoSensorDireito);

        if(valDireito == 1 && valEsquerdo == 1){
            pwm_tpm_CnV(TPM0, 0, duty_motor_direito);     // Motor direito pra frente
            pwm_tpm_CnV(TPM0, 1, 0);
            pwm_tpm_CnV(TPM0, 2, duty_motor_esquerdo);    // Motor esquerdo para frente
            pwm_tpm_CnV(TPM0, 3, 0);
        }

        else if(valDireito == 1 && valEsquerdo == 0){
            pwm_tpm_CnV(TPM0, 0, duty_motor_direito);     // Motor direito pra frente
            pwm_tpm_CnV(TPM0, 1, 0);
            pwm_tpm_CnV(TPM0, 2, 0);                      // Motor esquerdo trava
            pwm_tpm_CnV(TPM0, 3, 0);
        }

        else if(valDireito == 0 && valEsquerdo == 1){
            pwm_tpm_CnV(TPM0, 0, 0);                      // Motor direito trava
            pwm_tpm_CnV(TPM0, 1, 0);
            pwm_tpm_CnV(TPM0, 2, duty_motor_esquerdo);    // Motor esquerdo para frente
            pwm_tpm_CnV(TPM0, 3, 0);
        }

        else if(valDireito == 0 && valEsquerdo == 0){
            pwm_tpm_CnV(TPM0, 0, duty_motor_direito);     // Motor direito pra frente
            pwm_tpm_CnV(TPM0, 1, 0);
            pwm_tpm_CnV(TPM0, 2, duty_motor_esquerdo);    // Motor esquerdo para frente
            pwm_tpm_CnV(TPM0, 3, 0);
        }
    }
}
