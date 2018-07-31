#include <ADuC842.h>
#include <stdio.h>

void configura_serial();

void main (void){
	PLLCON = 0x88; //Habilita o pino de fast interrupt response com 16.7 MHz
	configura_serial(); //Configura a comunicação serial do AduC
	//Configura o TIC
	TIMECON = 0x13; // configura o TIC para contar um período único de 10 segundos
	INTVAL = 0x0A; // 10 segundos
	IE = 0x90;
	IEIP2 = 0x44; // habilita interrupções do TIC
	EA = 1; // habilita todas as interrupções
	P3_4 = 0;
	while (1){
	}
}


unsigned char str;

void transmit_data(unsigned char str) {
 	SBUF = str;
	while(TI==0);
	TI = 0;
}

void TIC_int () interrupt 10{
	TIMECON=0x13;
	P3_4 = !P3_4;
	//str = 'Z';
	//transmit_data(str);
	//printf("10 segundos foram ultrapassados\n");
}






void UART_int() interrupt 4{
 	str = SBUF;
	RI = 0;
	//TI = 0;
	if(str == 'L'){
	 	P3_4 = 0;
	} else if(str == 'D'){
	 	P3_4 = 1;
	}
	transmit_data(str);
}

void configura_serial (void){ //Configura a comunicação serial do AduC
	// Configuração do Timer 3 como gerador de BAUD RATE
	T3CON = 0x86;
	T3FD = 0x2d;
	SCON = 0x52;
}

