#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
    /*
    SYSCTL->RCGCPWM |= (1<<0); //Enable reloj de modulo PWM0 pag 354
    SYSCTL->RCGCGPIO |= (1<<5); //Enable reloj de GPIO Puerto F pag 340 pin 5
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); //Control de registros ya sea por GPIO o Otros Pag 672
    GPIOF->AFSEL |= 0x0E;
    GPIOF->PCTL |= (GPIOF->PCTL&0xFFFF000F) | 0x00006660; //Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689
    GPIOF->DEN |= (1<<3) | (1<<2) | (1<<1); // para decirle si es digital o no Pag 682
    //PWM0-> CC &= ~(1<<8);  //Enable o Disable Divisor  Pag 1747
    PWM0->_0_CTL = (0<<0);
    PWM0->_1_CTL = (0<<0); //Bloqueo y desbloqueo
    PWM0->_1_GENB = 0x0000080C; //Registro de las acciones del pwm Pag 1285
    PWM0->_1_GENA = 0x0000008C; //Registro de las acciones del pwm Pag 1282
    PWM0->_0_GENB = 0x0000008C;//PWM5
    PWM0->_1_LOAD = (int)(20000000/freq); //cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)
    PWM0->_0_LOAD = (int)(20000000/freq);
    PWM0->_1_CMPB = 15000;
    PWM0->_1_CMPA = 15000;
    PWM0->_0_CMPA = 15000;
    PWM0->_1_CTL = (1<<0);// Se activa el generador 3
    PWM0->_0_CTL = (1<<0);// Se activa el generador 2
    PWM0->ENABLE = (1<<3) | (1<<2) | (1<<1); //habilitar el bloque pa que pase Pag 1247
    */
    // Enable clock for PWM1
    SYSCTL->RCGCPWM |= (1 << 1);

    // Enable clock for port F
    SYSCTL->RCGCGPIO |= (1 << 5);

    // Set pin F5 as PWM output 
    GPIOF->AFSEL |= (1<<5);
    GPIOF->PCTL = (GPIOF->PCTL & 0xFF0FFFFF) | (4<<20);
    GPIOF->DIR |= (1<<5);
    GPIOF->DEN |= (1<<5);

    // Configure PWM clock to be system clock divided by 64
    PWM1->_2_CTL = (PWM1->_2_CTL & ~(0x3F << 2)) | (0x3F << 2);

    // Set PWM period to 400,000 clock cycles (50 Hz)
    PWM1->_2_LOAD = PWM_PERIOD;

    // Enable PWM output
    PWM1->ENABLE |= (1 << 2);

    // Set initial duty cycle to 10%
    PWM1->_2_CMPA = PWM_PERIOD / 10;

    // Start PWM
    PWM1->_2_CTL |= (1 << 0);
}


// Update PWM duty cycle based on ADC reading
void update_pwm_duty_cycle(void) {
    // Read the value of the ADC
    uint32_t adc_value = read_adc();

    // Scale the ADC value to the range of the PWM duty cycle
    uint32_t duty_cycle = (adc_value * PWM_PERIOD) / ADC_RANGE;

    // Limit the duty cycle to the range of 10% to 20%
    if (duty_cycle < (PWM_PERIOD * 0.1)) {
        duty_cycle = PWM_PERIOD * 0.1;
    } else if (duty_cycle > (PWM_PERIOD * 0.2)) {
        duty_cycle = PWM_PERIOD * 0.2;
    }

    // Update the PWM compare register with the new duty cycle
    PWM1->_2_CMPA = duty_cycle;
}
