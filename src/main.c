/* FILENAME: main.c
*  Author:  Ali El Bana
*  Version:  V1.0
*  DATE:   Fri 6/1/2022
*/

/************************************************************************/
/*                        Include headers                        	    */
/************************************************************************/

#include "COTS/LIB/LSTD_TYPES.h"
#include "COTS/LIB/LSTD_COMPILER.h"
#include "COTS/LIB/LSTD_VALUES.h"
#include "COTS/LIB/LSTD_BITMATH.h"

#include "COTS/MCAL/RCC/MRCC_interface.h"
#include "COTS/MCAL/SysTick/SysTick_interface.h"
#include "COTS/MCAL/GPIO/GPIO_interface.h"
#include "COTS/MCAL/TIM1/TIM1_interface.h"

#include "COTS/HAL/LDR/LDR_interface.h"
#include "COTS/HAL/LCD/LCD_interface.h"

/************************************************************************/
/*                     Functions implementations                      	*/
/************************************************************************/

int main( void )
{

	/* Define a variable to hold the ADC conversion value */
	u16_t L_u16BrightnessLevel = INITIAL_ZERO ;

	/* Initiate RCC for PORTA, PORTB and TIM1 */
	MRCC_vInit( ) ;
	MRCC_vEnablePeriphralCLK( RCC_AHB1, AHB1ENR_GPIOBEN ) ;
	MRCC_vEnablePeriphralCLK( RCC_AHB1, AHB1ENR_GPIOAEN ) ;
	MRCC_vEnablePeriphralCLK( RCC_APB2, APB2ENR_TIM1EN  ) ;

	/* Lock GPIO pins specified for SW debug */
	MGPIOx_vLockedPins( ) ;

	/* Initiate STK timer */
	MSysTick_vInit( ) ;

	/* Initiate TIM1 and enable the counter */
	MTIM1_vGeneratePWM( TIM1_CH3, PWM1, CENTER1,
						PSC_VALUE, ARR_VALUE, CR_VALUE ) ;

	MTIM1_vEnableCounter( ) ;

	/* Initiate the LCD */
	HLCD_vInit( ) ;

	/* Initiate the LDR */
	HLDR_vInit( ) ;

	/* Display Do chars on the first line */
	HLCD_vDispString( "Do:" ) ;

	while( TRUE )
	{

		/* Get ADC conversion */
		L_u16BrightnessLevel = HLDR_u16DigitalOutputValue( ) ;

		/* Go to the first line and square4 on the LCD */
		HLCD_vGoTo( HLCD_LINE1, HLCD_Square4 ) ;

		/* Display brightness number */
		HLCD_vDispNumber( L_u16BrightnessLevel ) ;

		/* Out the conversion value on the TIM1_CH3 */
		MTIM1_vSetCompareReg3Value( L_u16BrightnessLevel ) ;

		/* Display brightness bar */
		HLCD_vDispBrightnessBar( L_u16BrightnessLevel ) ;

		/* Delay 60ms */
		MSysTick_vDelayMilliSec( 60 ) ;

		/* Clear the old ADC conversion value */
		HLCD_vClearChar( HLCD_LINE1, HLCD_Square4 ) ;
		HLCD_vClearChar( HLCD_LINE1, HLCD_Square5 ) ;
		HLCD_vClearChar( HLCD_LINE1, HLCD_Square6 ) ;
		HLCD_vClearChar( HLCD_LINE1, HLCD_Square7 ) ;
		HLCD_vClear2ndRow( ) ;

		/* Delay 10ms */
		MSysTick_vDelayMilliSec( 10 ) ;

	}

}

/**************************************************************************************/
/**************************************************************************************/




























