/**
 * Bibliotheque GASSP 2013-02-15
 *
 * GPIO - ADC - Sequenceur - System Timer - PWM - 72 MHz
 *
 */

// STM32F10X_CL : pour le STM32F107 "Communication Line"
// STM32F10X_MD : pour le STM32F103 "Medium Density"

//#define STM32F10X_MD	// 2019 fix for Keil 5.23

#include "stm32f10x.h"

// horloge systeme (config statique a 72 MHz pour le STM32F103) ------------
void CLOCK_Configure(void);

// Timers 1, 2, 3, 4 -------------------------------------------------------
// la duree entre deux debordements successifs doit etre donnnee en periodes
// d'horloge CPU (typiquement 72 MHz)
void Timer_1234_Init_ff( TIM_TypeDef *Timer, u32 Duree_ticks );

// activation d'une fonction de traitement de l'interruption timer (callback)
void Active_IT_Debordement_Timer( TIM_TypeDef *Timer, char Prio, void (*IT_function)(void) );

// bloque le timer
#define Bloque_Timer(Timer) Timer->CR1=(Timer->CR1)&~(1<<0)

// Lance timer
#define Run_Timer(Timer) Timer->CR1=(Timer->CR1)|(1<<0)

// PWM (basee sur un des Timers 1, 2, 3, 4 ---------------------------------
// la periode doit etre donnee en periodes d'horloge CPU (typiquement 72 MHz)
// la fonction rend la pleine echelle ou resolution, c'est a dire la plage
// de valeurs acceptees pour moduler la largeur d'impulsion
vu16 PWM_Init_ff( TIM_TypeDef *Timer, char Voie, u32 Periode_ticks );

// Timer systeme "SysTick" -------------------------------------------------

// la periode doit etre donnee en periodes d'horloge CPU (typiquement 72 MHz)
void Systick_Period_ff( unsigned int Periode_ticks );

// activation d'une fonction de traitement de l'interruption timer (callback)
void Systick_Prio_IT( char Prio, void (*Systick_function)(void) );

#define  SysTick_On ((SysTick->CTRL)=(SysTick->CTRL)|1<<0)
#define  SysTick_Off ((SysTick->CTRL)=(SysTick->CTRL)& ~(1<<0))
#define  SysTick_Enable_IT ((SysTick->CTRL)=(SysTick->CTRL)|1<<1)
#define  SysTick_Disable_IT ((SysTick->CTRL)=(SysTick->CTRL)& ~(1<<1))

// ADC - DMA ---------------------------------------------------------------
// Analog-to-Digital Conversion, Direct Memory Access

// la duree d'echantillonnage doit etre donnee en periodes d'horloge CPU (typiquement 72 MHz)
// la fonction rend la duree totale de conversion (meme unites)
u32 Init_TimingADC_ActiveADC_ff( ADC_TypeDef * ADC, u32 Duree_Ech_ticks );

// choix d'un canal ADC unique
void Single_Channel_ADC( ADC_TypeDef * ADC, char Voie_ADC );

// la periode de repetition des acquisitions doit etre donnee en periodes d'horloge CPU
// Les sources de déclenchement possibles :
#define TIM1_CC1 0
#define TIM1_CC2 1
#define TIM1_CC3 2
#define TIM2_CC2 3
#define TIM4_CC4 5
void Init_Conversion_On_Trig_Timer_ff( ADC_TypeDef * ADC, char Source, u32 Periode_ticks );

// initialisation d'acquisition en mode DMA
// Ptr_Table_DMA doit pointer sur un espace memoire suffisant pour le nombre d'ech. demande
void Init_ADC1_DMA1( char Circ, vu16 *Ptr_Table_DMA );


// Lance une DMA sur le nombre de points spécifie. Les resultats seront stockes
// dans la zone de RAM écrite est indiquée lors de l'appel de la fonction  Init_ADC1_DMA1
void Start_DMA1( u16 NbEchDMA );

// arret DMA
#define  Stop_DMA1 DMA1_Channel1->CCR =(DMA1_Channel1->CCR) &~0x1;

// fonction d'attente (bloquante)
// la duree depend de la periode d'acquisition et du nombre d'echantillons
void Wait_On_End_Of_DMA1(void);


// GPIO --------------------------------------------------------------------

// Sens
#define INPUT   'i'
#define OUTPUT  'o'

// Techno pour pin en entrée (INPUT)
#define ANALOG              0
#define INPUT_FLOATING      1
#define INPUT_PULL_DOWN_UP  2

// Techno pour pin en sortie (OUTPUT)
#define OUTPUT_PPULL    0
#define OUTPUT_OPDRAIN  1
#define ALT_PPULL       2
#define ALT_OPDRAIN     3

// La fonction initialise n'importe quelle broche de port (entrée, sortie, techno....)
// Exemple :
// Port_IO_Init(GPIOB, 8, OUTPUT, OUTPUT_PPULL);
// Place le bit 8 du port B en sortie Push-pull
// Renvoie 0 si tout est OK,  et 1 s'il y a un problème (plage d'entrée non respectée)
char GPIO_Configure(GPIO_TypeDef * Port, int Broche, int Sens, int Techno);

// Spécifier le numéro de broche (0 à 15)
// exemple : Port_IO_Set(GPIOB,8);
#define GPIO_Set(GPIO,Broche) GPIO->BSRR=(0x01<<Broche)

#define GPIO_Clear(GPIO,Broche) GPIO->BRR=(0x01<<Broche)
