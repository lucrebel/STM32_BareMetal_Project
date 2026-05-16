
#include "stm32f4xx.h"

#define GPIOAEN 	(1U<<0) //Bit at index 0 set to =1, to allow GPIOA  clock access EN = ENABLE
#define PIN5 		(1U<<5) //Bit at index 5 set to =1
#define LED_PIN		PIN5 //Create led pin that takes over Pin5




int main()
{
	//GPIOA is connected to the AHB Bus (communication pathway) ENABLE!
	RCC->AHB1ENR |= GPIOAEN; //Führt comman aus, die bitsetzung im index 0 auf 1 ->bus access, define nur als simplifizierung!

	/*SET PIN (PA5) MODE TO OUTPUT*/
	GPIOA -> MODER |=(1U<<10);
	GPIOA -> MODER &=~(1<<11);
	while(1)
	{	//Output Output Data Register
		GPIOA->ODR ^=LED_PIN;
		for(int i = 0;i<10000;1++){

		}
	}
}
