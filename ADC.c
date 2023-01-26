#include "lib/include.h"

 /*
 * ADC.c
 *
 *  Created on: 04/01/2023
 *      Author: Leonardo Rodriguez
 */

/*
    Usando el modulo 0 y 1 , configurar la tarjeta a la frecuencia asignada, para adquirir 6 señales analógicas a una velocidad de 1 millón de muestras por segundo, por los canales asignados  y guardar los valores en un arreglo para ser enviados con un botones  externos asociado al gpio D a través del protocolo de comunicación asíncrona a una velocidad de 115200 todo esto usando interrupciones.
    a) 1,3,4,5,11,9- 55Mhz- 115200 -sec 2 ,sec 1
    b) 2,4,6,7,10,1- 30MHZ -57600 -sec3, sec1
    c),3,5,7,4,2,8 70 MHZ 9600, -sec2, sec3, sec1
    d),11,9,6,7,4,2 33MHZ 19200 -sec3,sec0,sec2
    e)1,5,7,11,6,8 80MHZ 4800 -sec0 ,sec3
    la captura será en Matlab en 6 graficas.
*/

extern void Configura_Reg_ADC0(void)
{
   /*
   SYSCTL->RCGCADC = (1<<0); 
   SYSCTL->RCGCGPIO |= (1<<4) | (1<<3); //Habilitar el puerto E, D y B para los canales
   //Configurar el canal 8 a una velocidad de 1 Msps
   //SS2 secuenciador de 2 muestra del convertidor por software
   GPIOE->AFSEL = 0x0000; //Para ver que funcion alternativa usar
   GPIOD->AFSEL = 0X0000;
   GPIOE->DIR |= (0<<2) | (0<<0); //usar el pin 4, 2 Y 0 del puerto E como entrada 0 Entrada | 1 Salida
   GPIOD->DIR |= (0<<3);
   GPIOE->DEN |= 0x00; //Desactivamos la funcion digital porque es analogico
   GPIOD->DEN |= 0X00; 
   GPIOE->PCTL = (GPIOE->PCTL & 0xFFFFF0F0); //Se limpia el registro de control.
   GPIOD->PCTL = (GPIOD->PCTL & 0xFFFF0FFF);
   GPIOE->AMSEL |= (1<<2) | (1<<0); //Activamos el pin 3 y 2 como analogico. 
   GPIOD->AMSEL |= (1<<3);
   ADC0->SSPRI = 0x3012;
   ADC0->PC = 0x5;
   //Configuracion de la secuencia de muestreo//(Se puede programar)
   ADC0->ACTSS = (0<<2); //Desabilitar el registro del secuenciador
   ADC0->EMUX = (0x0<<8);
   ADC0->SSMUX2 = (ADC0->SSMUX2 & ~0xFFFF) | (1<<0) | (3<<4) | (4<<8);
   ADC0->SSCTL2 = (1<<1) | (1<<2) | (1<<5) | (1<<6) | (1<<9) | (1<<10);
   ADC0->IM = (1<<2) | (1<<1); //Deshabilita la mascara de la interrupcion
   ADC0->ACTSS = (1<<2);
   ADC0->PSSI |= (1<<2);
   */
      // Enable clock for ADC0
    SYSCTL->RCGCADC |= (1 << 0);

    // Enable clock for port E
    SYSCTL->RCGCGPIO |= (1 << 4);

    // Set pin E1 as ADC input
    GPIOE->AFSEL |= (1 << 1);
    GPIOE->DEN &= ~(1 << 1);

    // Configure ADC to sample on PE1
    ADC0->SSMUX3 = 1;

    // Enable sample sequence
    ADC0->ACTSS |= (1 << 3);

    // Enable ADC
    ADC0->CTL = (1 << 0);

}

extern void ADC0_InSeq2(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI |= (1<<2);
       while((ADC0->RIS & (1<<2))==0){}; // espera al convertidor
       Result[0] = ADC0->SSFIFO2&0xFFF;//  Leer  el resultado almacenado en la pila2
       Result[1] = ADC0->SSFIFO2&0xFFF;
       Result[2] = ADC0->SSFIFO2&0xFFF;
       ADC0->ISC = (1<<2);  //Conversion finalizada

}

uint32_t read_adc(void) {
    // Start ADC conversion
    ADC0->PSSI = (1 << 3);
    // Wait for conversion to complete
    while ((ADC0->RIS & (1 << 3)) == 0){};
    // Clear conversion complete flag
    ADC0->ISC = (1 << 3);
    // Return ADC value
    return ADC0->SSFIFO3 & 0xFFF;
}

