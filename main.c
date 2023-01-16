 #include "lib/include.h"

int main(void)
{
    uint16_t Result[2];
    char ADC[4];
    Configurar_PLL(_50MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC0();
    Configurar_UART3();
    while(1)
    {
        ADC0_InSeq2(Result);
        utoa(Result[0],ADC,10); 
        printString(ADC);
        ADC[0] = '0';
        ADC[1] = '0';
        ADC[2] = '0';
        ADC[3] = '0';   
        SysTick_espera_1ms(100);
        ADC0_InSeq1(Result);
        utoa(Result[1],ADC,10); 
        printString(ADC);   
        ADC[0] = '0';
        ADC[1] = '0';
        ADC[2] = '0';
        ADC[3] = '0';         

    }
    
}
