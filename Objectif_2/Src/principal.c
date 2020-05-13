#include "gassp72.h"
#define SYSTICK_PER 1440000 //20ms=le temps max de tir / 5
#define M2TIR 0x000A0000

int module_carre(unsigned short[], int);
unsigned short dma_buf[64];
int frequence_pistolet[6] = {17, 18, 19, 20, 23, 24}; // 17*5=85, 18*5=90 ...
int dft_pistolet[6]; // pour stocker les resultats des dft
int cmpt_occurences[6]; // pour compter le nombre de fen�tres cons�cutives o� le tir d�passe M2TIR
int score[6]; // pour compter le score de chaque pistolet

void sys_callback(){
	// D�marrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	int k;
	for(k = 0; k < 6; k++){
		dft_pistolet[k] = module_carre(dma_buf, frequence_pistolet[k]);
		if (dft_pistolet[k] > M2TIR) {
			if (++cmpt_occurences[k] > 3) {
				score[k]++;
				cmpt_occurences[k] = 0;
			}
		} else {
			cmpt_occurences[k] = 0;
		}
	}
}

int main(void) {
	// activation de la PLL qui multiplie la fr�quence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entr�e analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage � l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, 0x4E );
	Single_Channel_ADC( ADC1, 2 );
	// D�clenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf (a cr��r)
	Init_ADC1_DMA1( 0, dma_buf );

	// Config Timer, p�riode exprim�e en p�riodes horloge CPU (72 MHz)
	Systick_Period_ff( SYSTICK_PER );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorit�, sys_callback est l'adresse de cette fonction, a cr��r en C
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;

	while(1){}
}
