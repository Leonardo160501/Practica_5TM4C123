 #include "lib/include.h"

int main(void)
{
    uint16_t Result[3];
    char ADC[4];
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART3();
    Configura_Reg_PWM1(1000);
    while(1)
    {
        

    }
    
}
