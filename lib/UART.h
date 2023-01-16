#ifndef UART_UART_H_
#define UART_UART_H_

extern void Configurar_UART3(void);
extern void habilitar_InUART3(void);
extern void printChar(char c);
extern void printString(char* string);
extern void UART3_ISR(void);



#endif /* UART_UART_H_ */