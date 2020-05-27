#include "gassp72.h"
#include "etat.h"
#define SYSTICK_PER 1440000 // 20ms = le temps max de tir / 5
#define M2TIR 0x000A0000
#define Periode_PWM_en_Tck 720 // 100kHz >> 20kHz -> 72MHz / 100kHz = 720
#define Periode_en_Tck 72*PeriodeSonMicroSec // 72MHz * 10^-6 * PeriodeSonMicroSec

extern short PeriodeSonMicroSec; // tous les sons ont la même période
extern short LongueurSon_BruitVerre;
extern short Son_BruitVerre;
extern short LongueurSon_M;
extern short Son_M;
extern short LongueurSon_N;
extern short Son_N;

int module_carre(unsigned short[], int);
unsigned short dma_buf[64];
int frequence_pistolet[6] = {17, 18, 19, 20, 23, 24}; // 17*5=85, 18*5=90 ...
int dft_pistolet[6]; // pour stocker les resultats des dft
int cmpt_occurences[6]; // pour compter le nombre de fenêtres consécutives où le tir dépasse M2TIR
int score[6]; // pour compter le score de chaque pistolet
type_etat etat; // structure pour gérer le son

void play_sound(int i) {
	etat.position = 0; // on relance le son
	switch(i) {
		case 0:
			etat.taille = LongueurSon_BruitVerre;
			etat.son = &Son_BruitVerre;
			break;
		case 1:
			etat.taille = LongueurSon_M;
			etat.son = &Son_M;
			break;
		default:
			etat.taille = LongueurSon_N;
			etat.son = &Son_N;
	}
}

void sys_callback(){
	// Démarrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	int k;
	for(k = 0; k < 6; k++){
		dft_pistolet[k] = module_carre(dma_buf, frequence_pistolet[k]);
		if (dft_pistolet[k] > M2TIR) {
			if (++cmpt_occurences[k] > 3) {
				score[k]++;
				play_sound(k%3);
				cmpt_occurences[k] = 0;
			}
		} else {
			cmpt_occurences[k] = 0;
		}
	}
}

void timer_callback(void);

int main(void) {
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entrée analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage à l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);
	// config port PB0 pour être utilisé par TIM3-CH3
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	// config TIM3-CH3 en mode PWM
	etat.resolution = PWM_Init_ff( TIM3, 3, Periode_PWM_en_Tck );
	etat.position = 0; // on met le son à la fin parcequ'on ne veut pas le lire au démarrage
	etat.taille = 0;
	etat.periode_ticks = PeriodeSonMicroSec;
	// config port PB1 pour être utilisé en sortie
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// initialisation du timer 4
	// Periode_en_Tck doit fournir la durée entre interruptions,
	// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
	Timer_1234_Init_ff( TIM4, Periode_en_Tck );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
	// cette fonction doit être conforme à l'AAPCS
	Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
	// lancement du timer
	Run_Timer( TIM3 );
	Run_Timer( TIM4 );

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, 0x4E );
	Single_Channel_ADC( ADC1, 2 );
	// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf (a créér)
	Init_ADC1_DMA1( 0, dma_buf );

	// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
	Systick_Period_ff( SYSTICK_PER );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorité, sys_callback est l'adresse de cette fonction, a créér en C
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;

	while(1){}
}
