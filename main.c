 #include "lib/include.h"

int main(void)
{
    uint16_t Result[3];
    char ADC[4];
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART0();
    Configura_Reg_PWM1();
    while(1)
    {
        update_pwm_duty_cycle();
    }
    
}
