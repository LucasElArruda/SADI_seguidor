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

int ent0;
int ent1;
int ent2;

//Protótipos das funções
void configura_serial(void);
void configura_PWM(void);

//Programa principal
void main(void) {
  PLLCON = 0x88; //Configuração do PLL
  //ADCCON1 = 0x80; //Configuração do ADC
  configura_serial(); //Configuração da serial
  configura_PWM(); //Configuração do PWM



  while (1) {
    //Configura o valor de referencia do PWM0 para ser 2,5V e o PWM1 para ser 5V
        PWM0H = 0x7F;	//direita	//P2_6
        PWM0L = 0xFF;	//direita	//P2_6
        PWM1L = 0xFF;	//esquerda	//P2_7
        PWM1H = 0x7F;	//esquerda	//P2_7
    	//printf("Imprimindo as coisas aqui \n");

		ent0 = P2_0;  // direita
		ent1 = P2_1; // centro
		ent2 = P2_2; // esquerda		Leituras dos TCRT5k:
		printf("%d %d %d\n",ent0,ent1,ent2);

	/*	if(ent1==1){ //carro saiu do centro do alinhamento
			if(ent0==0){ //direita está detectando -> curva p direita -> aumentar rotação da roda esquerda
				//PWM0H = 0x7F; //permanece o mesmo
				PWM1H = 0xCF;  //aumenta velocidade
				}
			else if(ent2==0){//esquerda está detectando -> curva p esquerda
				PWM0H = 0xCF; 
				//PWM1H = 0x7F;
				}
		}
		else(ent1==0){ //carro está alinhado
			PWM0H = 0x7F;
			PWM1H = 0x7F;
  			}
  */
  }
}



void configura_serial (void){ //Configura a comunicação serial do AduC
  // Configuração do Timer 3 como gerador de BAUD RATE
  T3CON = 0x86;
  T3FD = 0x2d;
  SCON = 0x52;  //talvez precise mudar pra 0x50
}

void configura_PWM(void)
{
  PWMCON = 0x33;  // Mode 1
                  // PWM Counter = Selected Clock/1
                  // PWM Clock = 16.777216 MHz
  //PWM1H = 0xFF;
  //PWM1L = 0xFF; //PWM1H/L = 65535 -> Frequência do PWM = (16.777216 MHz/65536) = 256Hz
}															