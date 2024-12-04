
#include "../../example/inc/app.h"         // <= Su propia cabecera (opcional)

#include "sapi.h"        // <= Biblioteca sAPI
// Variables para almacenar el estado de los LEDs
bool led1State = OFF;
bool led2State = OFF;
bool led3State = OFF;
bool ledGState = OFF;

gpioMap_t leds[] = {CIAA_BOARD_LED, LED1, LED2, LED3};
gpioMap_t botones[] = {TEC1, TEC2, TEC3, TEC4};

bool ledState[] = {OFF, OFF, OFF, OFF};
bool botonState[] = {FALSE, FALSE, FALSE, FALSE};


// Variables para detectar flanco de bajada en los botones
bool tec1Pressed = false;
bool tec2Pressed = false;
bool tec3Pressed = false;
bool tec4Pressed = false;

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
/*
        if (!gpioRead(TEC1)) {
            if (!tec1Pressed) {
                tec1Pressed = true;
                led1State = !led1State;
                gpioWrite(CIAA_BOARD_LED, led1State);
            }
        } else {
            tec1Pressed = false;
        }

        if (!gpioRead(TEC2)) {
            if (!tec2Pressed) {
                tec2Pressed = true;
                led2State = !led2State;
                gpioWrite(LED1, led2State);
            }
        } else {
            tec2Pressed = false;
        }

        if (!gpioRead(TEC3)) {
            if (!tec3Pressed) {
                tec3Pressed = true;
                led3State = !led3State;
                gpioWrite(LED2, led3State);
            }
        } else {
            tec3Pressed = false;
        }

        if (!gpioRead(TEC4)) {
            if (!tec4Pressed) {
                tec4Pressed = true;
                ledGState = !ledGState;
                gpioWrite(LED3, ledGState);
            }
        } else {
            tec4Pressed = false;
        }
*/

