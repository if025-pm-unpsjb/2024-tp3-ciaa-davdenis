
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI



void turn( void* params );

int main( void )
{

	// ---------- CONFIGURACIONES ------------------------------
   boardConfig();

   uartConfig(UART_USB, 9600);
   uartInterrupt( UART_USB, TRUE );
   uartCallbackSet( UART_USB, UART_RECEIVE, turn, NULL );

   pwmConfig(0, PWM_ENABLE);

   pwmConfig(PWM7, PWM_ENABLE_OUTPUT);
   pwmConfig(PWM8, PWM_ENABLE_OUTPUT);
   pwmConfig(PWM9, PWM_ENABLE_OUTPUT);

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {	}

   return 0;
}

void turn(void *p) {

	switch( uartRxRead( UART_USB ) ) {
	case '1':
		if (gpioRead(CIAA_BOARD_LED)) {
			gpioWrite(CIAA_BOARD_LED, FALSE);
		} else {
			gpioWrite(CIAA_BOARD_LED, TRUE);
		}
		break;
	case '2':
		if (pwmRead(PWM7) == 0) {
			pwmWrite(PWM7, 255);
		} else {
			pwmWrite(PWM7, 0);
		}
		break;
	case '3':
		if (pwmRead(PWM8) == 0) {
			pwmWrite(PWM8, 255);
		} else {
			pwmWrite(PWM8, 0);
		}
		break;
	case '4':
		if (pwmRead(PWM9) == 0) {
			pwmWrite(PWM9, 255);
		} else {
			pwmWrite(PWM9, 0);
		}
		break;
	}

}
