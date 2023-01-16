#include "lib/include.h"

 /*
 * ADC.c
 *
 *  Created on: 04/01/2023
 *      Author: Leonardo Rodriguez
 */

extern void Configura_Reg_ADC0(void)
{
   SYSCTL->RCGCADC = (1<<0); 
   SYSCTL->RCGCGPIO |= (1<<4); //Habilitar el puerto E para el canal ANI0
   //Configurar el canal 8 a una velocidad de 1 Msps
   //SS2 secuenciador de 2 muestra del convertidor por software
   GPIOE->AFSEL = 0x0000; //Patra ver que funcion alternativa usar
   GPIOE->DIR |= (0<<3) | (0<<2); //usar el pin 3 y 2 del puerto E como entrada 0 Entrada | 1 Salida
   GPIOE->DEN |= 0x00; //Desactivamos la funcion digital porque es analogico
   GPIOE->PCTL = (GPIOE->PCTL & 0xFFFF00FF); //Se limpia el registro de control.
   GPIOE->AMSEL |= (1<<3) | (1<<2); //Activamos el pin 3 y 2 como analogico. 
   ADC0->SSPRI = 0x3012;
   ADC0->PC = 0x5;
   //Configuracion de la secuencia de muestreo//(Se puede programar)
   ADC0->ACTSS = (0<<2) | (0<<1); //Desabilitar el registro del secuenciador
   ADC0->EMUX = (0x0<<8) | (0x0<<4);
   ADC0->SSMUX2 = 0x0;
   ADC0->SSMUX1 = 0X1;
   ADC0->SSCTL2 = (1<<1) | (1<<2);
   ADC0->SSCTL1 = (1<<1) | (1<<2);
   ADC0->IM = (1<<2) | (1<<1); //Deshabilita la mascara de la interrupcion
   ADC0->ACTSS = (1<<2) | (1<<1);
   ADC0->PSSI |= (1<<2) | (1<<1);

}

extern void ADC0_InSeq2(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI |= (1<<2);
       while((ADC0->RIS & (1<<2))==0){}; // espera al convertidor
       Result[0] = ADC0->SSFIFO2&0xFFF;//  Leer  el resultado almacenado en la pila2
       ADC0->ISC = (1<<2);  //Conversion finalizada

}

extern void ADC0_InSeq1(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI |= (1<<1);
       while((ADC0->RIS & (1<<1))==0){}; // espera al convertidor
       Result[1] = ADC0->SSFIFO1&0xFFF;//  Leer  el resultado almacenado en la pila2
       ADC0->ISC = (1<<1);  //Conversion finalizada

}
