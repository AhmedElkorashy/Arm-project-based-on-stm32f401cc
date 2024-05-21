/************************************************************************/
/*							FILES INCLUSIONS							*/

/************************************************************************/
/***********************LIB*************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
/************************MCAL***********************/
#include "../include/MCAL/MRCC/MRCC_Interface.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MNVIC/MNVIC_Interface.h"
#include "../include/MCAL/MEXTI/MEXTI_Interface.h"

void Handler1 (void);
void Handler2 (void);
void Handler3 (void);
void Handler5 (void);
void Handler6 (void);

int main()
{
	u8 local_u8Iterator = 0;
	MRCC_voidInit();
	/**choosing group 4 and sub 4**/
	MNVIC_voidSetInterruptGroupMode(Groups4_Sub4);
	/**setting the interrupt and give them priority**/
	MNVIC_voidSetInterruptPriority(6,2,1);
	MNVIC_voidSetInterruptPriority(7,0,1);
	MNVIC_voidSetInterruptPriority(8,1,1);
	MNVIC_voidSetInterruptPriority(23,3,1);

	MRCC_voidEnablePeripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_SYSCFG);
	/**button from 0 to 2*/
	for(local_u8Iterator=0;local_u8Iterator<=2;local_u8Iterator++)
	{
		MGPIO_voidSetPinMode(GPIO_PORTB , local_u8Iterator , GPIO_INPUT);
		MGPIO_voidSetPinInputMode(GPIO_PORTB , local_u8Iterator , GPIO_PULLUP);
	}
	/**button from 5 to 6*/
	for(local_u8Iterator=5;local_u8Iterator<=6;local_u8Iterator++)
	{
		MGPIO_voidSetPinMode(GPIO_PORTB , local_u8Iterator , GPIO_INPUT);
		MGPIO_voidSetPinInputMode(GPIO_PORTB , local_u8Iterator , GPIO_PULLUP);
	}
	/**the handlers**/
	MEXTI_voidSetCallBack(MEXTI_LINE0,Handler1);
	MEXTI_voidSetCallBack(MEXTI_LINE1,Handler2);
	MEXTI_voidSetCallBack(MEXTI_LINE2,Handler3);
	MEXTI_voidSetCallBack(MEXTI_LINE5,Handler5);
	MEXTI_voidSetCallBack(MEXTI_LINE6,Handler6);
	/****enabling the peripheral ***/
	MNVIC_voidEnablePeripheralInterrupt(6);
	MNVIC_voidEnablePeripheralInterrupt(7);
	MNVIC_voidEnablePeripheralInterrupt(8);
	MNVIC_voidEnablePeripheralInterrupt(23);
	MNVIC_voidEnablePeripheralInterrupt(23);
	/** leds from 0 to 9*/
	for ( local_u8Iterator = 0 ; local_u8Iterator < 10 ; local_u8Iterator++)
	{
		MGPIO_voidSetPinMode(GPIO_PORTA , local_u8Iterator , GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTA , local_u8Iterator , GPIO_PUSH_PULL , GPIO_LOW_SPEED);
		MGPIO_voidSetResetPin(GPIO_PORTA , local_u8Iterator , GPIO_RESET);
	}
	/**enabling the interrupt to happen**/
	MEXTI_voidInit();
	while(1);
}
void Handler1 (void)
{
	while (1)
	{
		for(int i=0;i<=1;i++)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_HIGH);
			for(u64 i=0;i<1000000;i++);
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_LOW);
			for(u64 i=0;i<1000000;i++);
		}
	}
}
void Handler2 (void)
{
	while (1)
	{
		for(int i=2;i<=3;i++)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_HIGH);
			for(u64 i=0;i<100000;i++);
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_LOW);
			for(u64 i=0;i<100000;i++);
		}
	}
}
void Handler3 (void)
{
	while (1)
	{
		for(int i=4;i<=5;i++)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_HIGH);
			for(u64 i=0;i<1000000;i++);
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_LOW);
			for(u64 i=0;i<1000000;i++);
		}
	}
}
void Handler5 (void)
{
	while (1)
	{
		for(int i=6;i<=7;i++)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_LOW);
			for(u64 i=0;i<1000000;i++);
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_HIGH);
			for(u64 i=0;i<1000000;i++);
		}
	}
}
void Handler6 (void)
{
	while (1)
	{
		for(int i=8;i<=9;i++)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_HIGH);
			for(u64 i=0;i<1000000;i++);
			MGPIO_voidSetPinValue(GPIO_PORTA,i,GPIO_PIN_LOW);
			for(u64 i=0;i<1000000;i++);
		}
	}
}
