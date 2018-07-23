#include <ADuC842.h>
#include <stdio.h>
void configura_serial();


void main (void){
	PLLCON = 0x88; //Habilita o pino de fast interrupt response com 16.7 MHz
	configura_serial(); //Configura a comunicação serial do AduC
 	//Configura o TIC
 	//TIMECON = 0x13; // configura o TIC para contar um período único de 10 segundos
 	//INTVAL = 0x0A; // 10 segundos
 	//IEIP2 = 0x44; // habilita interrupções do TIC


	INT0 = 1;
	INT1 = 1;
	TCON = 0x05;  // trigger em borda de descida
 	EA = 1; // habilita todas as interrupções
	EX0 = 1; // habilita interrupção externa
	PX0 = 1; // prioridade pra externa
	EX1 = 1; // habilita interrupção externa
	PX1 = 1; // prioridade pra externa
 	P3_4 = 0;
	while (1){
		if(!EA){
			EA = 1;
		}
 	}
}


void TIC_int () interrupt 0{
	//TIMECON=0x13;
 	P3_4 = !P3_4;
 	printf("10 segundos foram ultrapassados\n");
}

void configura_serial (void){
	// Configuração do Timer 3 como gerador de BAUD RATE
 	T3CON = 0x85;
 	T3FD = 0x2d;
 	SCON = 0x52;
} 