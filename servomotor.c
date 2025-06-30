#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include "pwm.h"
#include <MKL25Z4.h>

#define PORTA_E "GPIO_4"
#define pinoSinal 20 //PTE20

#define TPM_MODULE 7500

void main(void){
    pwm_tpm_Init(TPM1_BASE_PTR, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Ch_Init(TPM1, 0, TPM_PWM_H, GPIOE, pinoSinal);
    pwm_tpm_CnV(TPM1, 0, 150);    // posição min (-90°)
    //pwm_tpm_CnV(TPM1, 0, 202);  // posição -45°
    //pwm_tpm_CnV(TPM1, 0, 525);  // posição ~ 0°
    //pwm_tpm_CnV(TPM1, 0, 742);  // posição +45°
    //pwm_tpm_CnV(TPM1, 0, 957);  // posição max (+90°)

    while(1){
        uint16_t tick = 150;
        for(tick = 150; tick < 957; tick += 6){
            pwm_tpm_CnV(TPM1, 0, tick);
            k_msleep(20);
        }
        for(tick = 957; tick > 150; tick -= 6){
            pwm_tpm_CnV(TPM1, 0, tick);
            k_msleep(20);
        }
    }


}
