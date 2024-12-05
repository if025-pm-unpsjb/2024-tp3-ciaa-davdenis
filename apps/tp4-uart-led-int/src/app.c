
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI

int main( void )
{

	uint8_t receivedByte;

   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   pwmConfig(0, PWM_ENABLE);

   pwmConfig(PWM7, PWM_ENABLE_OUTPUT);
   pwmConfig(PWM8, PWM_ENABLE_OUTPUT);
   pwmConfig(PWM9, PWM_ENABLE_OUTPUT);

   uartConfig(UART_USB, 9600);

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {

	   if (uartReadByte(UART_USB, &receivedByte) == TRUE) {

		   if (receivedByte == '1') {
			   if (gpioRead(CIAA_BOARD_LED)) {
		       		gpioWrite(CIAA_BOARD_LED, FALSE);
			   } else {
		       		gpioWrite(CIAA_BOARD_LED, TRUE);
			   }
		   }

		   if (receivedByte == '2') {
			   if (pwmRead(PWM7) == 0) {
				   pwmWrite(PWM7, 255);
			   } else {
				   pwmWrite(PWM7, 0);
			   }
		   }

		   if (receivedByte == '3') {
			   if (pwmRead(PWM8) == 0) {
				   pwmWrite(PWM8, 255);
			   } else {
				   pwmWrite(PWM8, 0);
			   }
		   }

		   if (receivedByte == '4') {
			   if (pwmRead(PWM9) == 0) {
				   pwmWrite(PWM9, 255);
			   } else {
				   pwmWrite(PWM9, 0);
			   }
		   }
	   }
   }

   return 0;
}
