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
#include "semphr.h"

/*-----------------------------------------------------------*/

#define TASK1_PERIOD 	4000
#define TASK2_PERIOD 	7000
#define TASK3_PERIOD 	12000
#define TASK4_PERIOD 	14000

/* Tasks WCETs. */
#define TASK1_WCET		900
#define TASK2_WCET		1900
#define TASK3_WCET		900
#define TASK4_WCET		1900

static void vBusyWait( TickType_t ticks );

static void task1f( void* pvParameters );
static void task2f( void* pvParameters );
static void task3f( void* pvParameters );
static void task4f( void* pvParameters );

SemaphoreHandle_t s;

/*-----------------------------------------------------------*/

struct xTaskStruct {
	TickType_t wcet;
	TickType_t period;
};

typedef struct xTaskStruct xTask;

xTask task1 = { TASK1_WCET, TASK1_PERIOD };
xTask task2 = { TASK2_WCET, TASK2_PERIOD };
xTask task3 = { TASK3_WCET, TASK3_PERIOD };
xTask task4 = { TASK4_WCET, TASK4_PERIOD };

int main( void )
{
        // Inicializar y configurar la placa de desarrollo
        boardConfig();

        pwmConfig(0, PWM_ENABLE);

        pwmConfig(PWM7, PWM_ENABLE_OUTPUT);
        pwmConfig(PWM8, PWM_ENABLE_OUTPUT);
        pwmConfig(PWM9, PWM_ENABLE_OUTPUT);

        pwmWrite(PWM7, 10);
        pwmWrite(PWM8, 10);
        pwmWrite(PWM9, 10);

    	s = xSemaphoreCreateMutex();

        xTaskCreate( task1f, "T1", configMINIMAL_STACK_SIZE + 50, (void*) &task1, configMAX_PRIORITIES - 1, NULL );
        xTaskCreate( task2f, "T2", configMINIMAL_STACK_SIZE + 50, (void*) &task2, configMAX_PRIORITIES - 2, NULL );
        xTaskCreate( task3f, "T3", configMINIMAL_STACK_SIZE + 50, (void*) &task3, configMAX_PRIORITIES - 3, NULL );
        xTaskCreate( task4f, "T4", configMINIMAL_STACK_SIZE + 50, (void*) &task4, configMAX_PRIORITIES - 4, NULL );

        vTaskStartScheduler();
        for(;;);
}

static void vBusyWait( TickType_t ticks, pwmMap_t pwm )
{

	if (pwm != NULL) {
		pwmWrite(pwm, 255);
	}

    TickType_t elapsedTicks = 0;
    TickType_t currentTick = 0;
    while ( elapsedTicks < ticks ) {
        currentTick = xTaskGetTickCount();
        while ( currentTick == xTaskGetTickCount() ) {
            __asm__("nop");
        }
        elapsedTicks++;
    }
}

void task1f(void *p)
{
		TickType_t pxPreviousWakeTime = 0;

        while( TRUE ) {
        		gpioWrite( CIAA_BOARD_LED, TRUE);

        		if (pwmRead(PWM7) > 0) {
        			pwmWrite(PWM7, 32);
        		}
        		if (pwmRead(PWM8) > 0) {
        		    pwmWrite(PWM8, 32);
        		}
        		if (pwmRead(PWM9) > 0) {
        		    pwmWrite(PWM9, 32);
        		}

        		vBusyWait( TASK1_WCET, NULL );

        		gpioWrite( CIAA_BOARD_LED, FALSE);

        		vTaskDelayUntil( &pxPreviousWakeTime, TASK1_PERIOD );
        }

        vTaskDelete( NULL );
}

void task2f(void *p)
{

		TickType_t pxPreviousWakeTime = 0;

        while( TRUE ) {
        		pwmWrite(PWM7, 255);

        		if (pwmRead(PWM8) > 0) {
        		    pwmWrite(PWM8, 32);
        		}
        		if (pwmRead(PWM9) > 0) {
        		    pwmWrite(PWM9, 32);
        		}

        		vBusyWait( TASK2_WCET, PWM7 );

                pwmWrite(PWM7, 0);

        		vTaskDelayUntil( &pxPreviousWakeTime, TASK2_PERIOD );
        }

        vTaskDelete( NULL );
}

void task3f(void *p)
{

	TickType_t pxPreviousWakeTime = 0;

    while( TRUE ) {
    		pwmWrite(PWM8, 255);

    		if (pwmRead(PWM9) > 0) {
    		    pwmWrite(PWM9, 8);
    		}

    		vBusyWait( TASK3_WCET, PWM8 );

    		pwmWrite(PWM8, 0);

    		vTaskDelayUntil( &pxPreviousWakeTime, TASK3_PERIOD );
    }

    vTaskDelete( NULL );
}

void task4f(void *p)
{

	TickType_t pxPreviousWakeTime = 0;

    while( TRUE ) {
    		pwmWrite(PWM9, 255);

    		vBusyWait( TASK4_WCET, PWM9 );

    		pwmWrite(PWM9, 0);

    		vTaskDelayUntil( &pxPreviousWakeTime, TASK4_PERIOD );
    }

    vTaskDelete( NULL );
}
