#include <ADuC842.h>
#include <stdio.h>

//Variáveis
unsigned int i = 0;
unsigned int bufferad = 0;
unsigned int temp = 0;
unsigned int Duty = 0;
float Duty_Cycle = 0;
float valor_ad_conv = 0;
float valor_ad = 0;

//Protótipos das funções
void configura_serial(void);
void configura_PWM(void);

//Programa principal
void main(void) {
	PLLCON = 0x80; //Configuração do PLL
	ADCCON1 = 0x80; //Configuração do ADC
	configura_serial(); //Configuração da serial
	configura_PWM(); //Configuração do PWM
	while (1) {
		//Início da aquisição de 16 valores do canal 03------------------------------------------------
		for (i=0; i<16; i++)
		{
			ADCCON2 = (ADCCON2 & 0xF0) | 0x03; //Seleciona o canal 03
			//Utilizamos o canal 3 do conv AD devido ao aproveitamento do LDR que está conectado ao mesmo.
			SCONV = 1; //Inicia a conversão
			while (SCONV); //Espera a conversão terminar
			bufferad = ADCDATAL | ((ADCDATAH & 0x0F) << 8); // Valor do canal do ADC selecionado
			temp = temp + bufferad; //o valor temporário acumula 16 conversões
		}
	//Fim da aquisição ---------------------------------------------------------------------------
	valor_ad = (temp/16); //média das conversões obtidas e armazenadas na variável temp
	temp = 0; //anula a variável temporária para acumular o próximo conjunto de conversões
	valor_ad_conv = valor_ad*0.00061035; //Média dos valores lidos convertida para tensão (V)
	//escalona o valor AD de 12 bits para a variável Duty de 16 bits
	Duty = (valor_ad * 65535)/4095;
	//desloca para direita os oito bits mais significativos para as posições dos oito bits menos
	//significativos.
	PWM0H = Duty >> 8; // Armazena os oito bits mais significativos do Duty em PWM0H
	PWM0L = (Duty & 0x00FF); // Armazena os oito bits menos significativos do Duty em PWM0L
	Duty_Cycle = (Duty*100.0)/65535.0; //Valor em percentagem do Duty_Cycle
	//Mostra valor na saida serial:
	printf("Valor Analógico: %f Duty Cycle: %f%%\n", valor_ad_conv, Duty_Cycle);
	}
}

void configura_serial (void) //Configura a comunicação serial do AduC
{
	// Configuração do Timer 3 como gerador de BAUD RATE
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
	PWM1L = 0xFF; //PWM1H/L = 65535 -> Frequência do PWM = (16.777216 MHz/65536) = 256Hz
}