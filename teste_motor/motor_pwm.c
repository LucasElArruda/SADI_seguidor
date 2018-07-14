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
  //ADCCON1 = 0x80; //Configuração do ADC
  configura_serial(); //Configuração da serial
  configura_PWM(); //Configuração do PWM

  
  
  while (1) {
    //Configura o valor de referencia do PWM0 para ser 2,5V e o PWM1 para ser 5V
  	PWM0H = 0x7F;
	PWM0L = 0xFF; 
  	
  	//PWM1L = 0x00;
  	//PWM1H = 0x00;
    printf("Imprimindo as coisas aqui \n");
  }
}

void configura_serial (void){ //Configura a comunicação serial do AduC
  // Configuração do Timer 3 como gerador de BAUD RATE
  T3CON = 0x86;
  T3FD = 0x2d;
  SCON = 0x52;	//talvez precise mudar pra 0x50
}

void configura_PWM(void)
{
  PWMCON = 0x93;  // Mode 1
		  // PWM Counter = Selected Clock/1
		  // PWM Clock = 16.777216 MHz
  PWM1H = 0xFF;
  PWM1L = 0xFF; //PWM1H/L = 65535 -> Frequência do PWM = (16.777216 MHz/65536) = 256Hz
}
