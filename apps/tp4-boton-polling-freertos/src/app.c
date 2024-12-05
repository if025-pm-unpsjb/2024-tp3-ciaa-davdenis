/*
 * main.c
 *
 *  Created on: 13 oct. 2022
 *      Author: fep
 */

#include "FreeRTOS.h"
#include "task.h"
#include "app.h"         // <= Su propia cabecera (opcional)
#include "sapi.h"        // <= Biblioteca sAPI

/*-----------------------------------------------------------*/
static void task1f( void* pvParameters );
static void task2f( void* pvParameters );
static void task3f( void* pvParameters );
static void task4f( void* pvParameters );


int main( void )
{
        // Inicializar y configurar la placa de desarrollo
        boardConfig();

        pwmConfig(0, PWM_ENABLE);

        pwmConfig(PWM7, PWM_ENABLE_OUTPUT);
        pwmConfig(PWM8, PWM_ENABLE_OUTPUT);
        pwmConfig(PWM9, PWM_ENABLE_OUTPUT);

        xTaskCreate( task1f, "T1", 256, NULL, configMAX_PRIORITIES - 1, NULL );
        xTaskCreate( task2f, "T2", 256, NULL, configMAX_PRIORITIES - 1, NULL );
        xTaskCreate( task3f, "T3", 256, NULL, configMAX_PRIORITIES - 1, NULL );
        xTaskCreate( task4f, "T4", 256, NULL, configMAX_PRIORITIES - 1, NULL );

        vTaskStartScheduler();
        for(;;);
}


void task1f(void *p)
{
	TickType_t pxPreviousWakeTime = 0;
	bool botonPressed = false;
	bool ledState = OFF;

    while( TRUE ) {

		if (!gpioRead(TEC1)) {
			if (!botonPressed) {
				botonPressed = true;
				ledState = !ledState;
				gpioWrite(CIAA_BOARD_LED, ledState);
			}
		} else {
			botonPressed = false;
		}

     }

}

void task2f(void *p)
{
	TickType_t pxPreviousWakeTime = 0;
	bool botonPressed = false;
	bool ledState = OFF;

    while( TRUE ) {

		if (!gpioRead(TEC2)) {
			if (!botonPressed) {
				botonPressed = true;
				ledState = !ledState;
				if (ledState) {
					pwmWrite(PWM7, 255);
				} else {
					pwmWrite(PWM7, 0);
				}
			}
		} else {
			botonPressed = false;
		}

    }

}

void task3f(void *p)
{
	TickType_t pxPreviousWakeTime = 0;
	bool botonPressed = false;
	bool ledState = OFF;

    while( TRUE ) {

		if (!gpioRead(TEC3)) {
			if (!botonPressed) {
				botonPressed = true;
				ledState = !ledState;
				if (ledState) {
					pwmWrite(PWM8, 255);
				} else {
					pwmWrite(PWM8, 0);
				}
			}
		} else {
			botonPressed = false;
		}

     }

}

void task4f(void *p)
{
	TickType_t pxPreviousWakeTime = 0;
	bool botonPressed = false;
	bool ledState = OFF;

    while( TRUE ) {

		if (!gpioRead(TEC4)) {
			if (!botonPressed) {
				botonPressed = true;
				ledState = !ledState;
				if (ledState) {
					pwmWrite(PWM9, 255);
				} else {
					pwmWrite(PWM9, 0);
				}
			}
		} else {
			botonPressed = false;
		}

     }

}
