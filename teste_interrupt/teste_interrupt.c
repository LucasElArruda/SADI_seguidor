#include <ADuC842.h>
#include <stdio.h>
void configura_serial();


void main (void){
	PLLCON = 0x88; //Habilita o pino de fast interrupt response com 16.7 MHz
	configura_serial(); //Configura a comunicação serial do AduC
 	//Configura o TIC
 	TIMECON = 0x13; // configura o TIC para contar um período único de 10 segundos
 	INTVAL = 0x0A; // 10 segundos
 	IEIP2 = 0x44; // habilita interrupções do TIC
 	EA = 1; // habilita todas as interrupções
 	P3_4 = 0;
	while (1){
 	}
}


void TIC_int () interrupt 10{
	TIMECON=0x13;
 	P3_4 = !P3_4;
 	printf("10 segundos foram ultrapassados\n");
}

void configura_serial (void){
	// Configuração do Timer 3 como gerador de BAUD RATE
 	T3CON = 0x85;
 	T3FD = 0x2d;
 	SCON = 0x52;
} 