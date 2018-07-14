#include <ADuC842.h>
#include <stdio.h>

//Vari�veis
unsigned int i = 0;
unsigned int bufferad = 0;
unsigned int temp = 0;
unsigned int Duty = 0;
float Duty_Cycle = 0;
float valor_ad_conv = 0;
float valor_ad = 0;

//Prot�tipos das fun��es
void configura_serial(void);
void configura_PWM(void);

//Programa principal
void main(void) {
	PLLCON = 0x80; //Configura��o do PLL
	ADCCON1 = 0x80; //Configura��o do ADC
	configura_serial(); //Configura��o da serial
	configura_PWM(); //Configura��o do PWM
	while (1) {
		//In�cio da aquisi��o de 16 valores do canal 03------------------------------------------------
		for (i=0; i<16; i++)
		{
			ADCCON2 = (ADCCON2 & 0xF0) | 0x03; //Seleciona o canal 03
			//Utilizamos o canal 3 do conv AD devido ao aproveitamento do LDR que est� conectado ao mesmo.
			SCONV = 1; //Inicia a convers�o
			while (SCONV); //Espera a convers�o terminar
			bufferad = ADCDATAL | ((ADCDATAH & 0x0F) << 8); // Valor do canal do ADC selecionado
			temp = temp + bufferad; //o valor tempor�rio acumula 16 convers�es
		}
	//Fim da aquisi��o ---------------------------------------------------------------------------
	valor_ad = (temp/16); //m�dia das convers�es obtidas e armazenadas na vari�vel temp
	temp = 0; //anula a vari�vel tempor�ria para acumular o pr�ximo conjunto de convers�es
	valor_ad_conv = valor_ad*0.00061035; //M�dia dos valores lidos convertida para tens�o (V)
	//escalona o valor AD de 12 bits para a vari�vel Duty de 16 bits
	Duty = (valor_ad * 65535)/4095;
	//desloca para direita os oito bits mais significativos para as posi��es dos oito bits menos
	//significativos.
	PWM0H = Duty >> 8; // Armazena os oito bits mais significativos do Duty em PWM0H
	PWM0L = (Duty & 0x00FF); // Armazena os oito bits menos significativos do Duty em PWM0L
	Duty_Cycle = (Duty*100.0)/65535.0; //Valor em percentagem do Duty_Cycle
	//Mostra valor na saida serial:
	printf("Valor Anal�gico: %f Duty Cycle: %f%%\n", valor_ad_conv, Duty_Cycle);
	}
}

void configura_serial (void) //Configura a comunica��o serial do AduC
{
	// Configura��o do Timer 3 como gerador de BAUD RATE
	T3CON = 0x85;
	T3FD = 0x2d;
	SCON = 0x52;
}


void configura_PWM(void)
{
	PWMCON = 0x93; // Mode 1
	// PWM Counter = Selected Clock/1
	// PWM Clock = 16.777216 MHz
	PWM1H = 0xFF;
	PWM1L = 0xFF; //PWM1H/L = 65535 -> Frequ�ncia do PWM = (16.777216 MHz/65536) = 256Hz
}