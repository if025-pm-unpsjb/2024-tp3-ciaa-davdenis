
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI

gpioMap_t leds[] = {CIAA_BOARD_LED, LED1, LED2, LED3};
gpioMap_t botones[] = {TEC1, TEC2, TEC3, TEC4};

bool ledState[] = {OFF, OFF, OFF, OFF};
bool botonState[] = {FALSE, FALSE, FALSE, FALSE};


int main(void) {

    boardConfig();

    while (1) {

    	for (int i=0; i<4; i++) {

    		if (!gpioRead(botones[i])) {
    			if (!botonState[i]) {
    				botonState[i] = true;
    				ledState[i] = !ledState[i];
    				gpioWrite(leds[i], ledState[i]);
    			}
    		} else {
    			botonState[i] = false;
    		}

    	}

    	delay(10);
    }

    return 0;
}
