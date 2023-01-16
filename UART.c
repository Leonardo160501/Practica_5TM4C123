#include "lib/include.h"


extern void Configurar_UART3(void)
{
    //Habilitar el deloj del UART y el gpio con registros
    SYSCTL->RCGCUART |= (1<<3); 
    SYSCTL-> RCGCGPIO |= (1<<2); //Puerto C
    //Configurar el GPIO
    GPIOC-> AFSEL |= (1<<6) | (1<<7);
    //              Rx       Tx
    GPIOC->DIR |= (0<<6) | (1<<7);
    GPIOC->PUR |= (0<<6) | (0<<7);
    GPIOC->PDR |= (0<<6) | (0<<7);
    GPIOC->DEN |= (1<<6) | (1<<7);
    GPIOC->AMSEL = 0x00; //Desactivamos la funcion analogica
    GPIOC->PCTL = (GPIOC->PCTL & 0X00FFFFFF) | 0x11000000;

    UART3->CTL |= (0<<8) | (0<<9) | (0<<0) | (0<<4); 
    //Velocidad 115200 baudrate, frecuencia de reloj 50,000,000.
    //BRD = 50,000,000 / (16 * 115200) = 27.1267361
    //UARTFBRD[DIVFRAC] = integer(.1267361 * 64 + 0.5) = 8.6111104
    //para 9600 
    //130
    //14
    UART3->IBRD = 27;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART3->FBRD = 8;
    UART3->LCRH = (0x3<<5) | (1<<4);
    UART3->CC = 0x00;
    UART3->CTL |= (1<<8) | (1<<9) | (1<<0) | (1<<4); 
    
}


extern void printChar(char c) //enviamos un caracter
{
    while((UART3->FR & (1<<5)) != 0 );
    UART3->DR = c;
}
extern void printString(char* string)//enviamos una cadena
{
    while(*string){
       printChar(*(string++)); 
    }
    printChar('\n');
}











//Experimento 2

//El envio es su nombre  (rave) 

// invertirlo y regresarlo con numeros consecutivos
// entre letras (e1v2a3r) 

