
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI

#define BUFFER_SIZE 128

int main( void )
{

	uint8_t receivedByte;
	uint8_t buffer[BUFFER_SIZE];
	uint32_t index = 0;

   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   uartConfig(UART_USB, 9600);

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {

	   if (uartReadByte(UART_USB, &receivedByte) == TRUE) {

		   uartWriteByte(UART_USB, receivedByte);

		   if (index < (BUFFER_SIZE - 1)) {
			   buffer[index++] = receivedByte;
		   }

		   if (receivedByte == '\r') {
			   buffer[index] = '\0';

			   uartWriteString(UART_USB, "\r\n");
			   uartWriteString(UART_USB, (char*) buffer);
			   uartWriteString(UART_USB, "\r\n");

			   index = 0;

		   }

	   }

   }

   return 0;
}
