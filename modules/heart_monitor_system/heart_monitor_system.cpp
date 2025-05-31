/** @file heart_monitor_system.cpp
 *  @brief Módulo principal del sistema.
 *
 *  Este módulo se encarga de dirigir el programa principal del
 *  monitoreo de frecuencia cardiaca
 */
 
 //=====[Libraries]=============================================================


#include "arm_book_lib.h"
#include "heart_monitor_system.h"

#include "string.h"
#include "display.h"
#include "pulse_sensor.h"
#include "serial_com.h"
#include "button.h"
#include "audio.h"

#define READ_INIT_MSG "Comenzando lectura...."
#define READ_FINISH_MSG "Lectura finalizada"
#define MAX_CHAR_MESSAGE 100

//=====[Declaration and initialization of public global objects]===============

DigitalOut readingLed(LED1);



//=====[Declaration and initialization of public global variables]=============


bool valueReady = 0;
bool readingState =0;

float bpm_value;

Ticker tickerMessageBPM;
bool messageReady = false; 


//=====[Declarations (prototypes) of functions]=========================

void inputsInit();
void outputsInit();

void buildMessage();
void tickActivateMessage();

/**
 * @brief Inicializa los parametros del sistema
 *
 */
void heartMonitorSystemInit(){

    inputsInit();
    outputsInit();
    ssd1306_init();
    ssd1306_clear_display();
    ssd1306_print(0, 2, "   INICIANDO... ");
    audioInit();

    tickerMessageBPM.attach( tickActivateMessage, 2000ms);

}


/**
 * @brief Actualizacion del sistema
 *
 */
void heartMonitorSystemUpdate(){

    if(debounceButtonUpdate()){
            readingState = !readingState;
            if (readingState){
                sendUartMessage(READ_INIT_MSG);
                ssd1306_clear_display();
                ssd1306_print(0, 0, READ_INIT_MSG);
            } else{
                sendUartMessage(READ_FINISH_MSG);
                ssd1306_clear_display();
                ssd1306_print(0, 0, READ_FINISH_MSG);
            }
        }
        
        
        if(readingState){
            readingLed = ON;
            readBPM();
            if(messageReady){
                bpm_value = getBPM();
                buildMessage(); // Ejecuta solo si el flag está activo
                messageReady = false; // Resetear el flag después de ejecutar
            }
        } else{
            readingLed = 0;
        }
        
        delay(TIME_INCREMENT_MS);

}




void inputsInit() {
    //button.mode(PullDown);
}

void outputsInit() {
    readingLed = OFF;
}


void tickActivateMessage() {
    messageReady = true; // Activar el flag cada cierto tiempo
}

void buildMessage() {
    //  enviar el mensaje por UART
    char str[MAX_CHAR_MESSAGE];
    sprintf(str,"Latidos por minuto: %d", (int)bpm_value);
    sendUartMessage(str);
    // enviar a display
    sprintf(str,"          %d", (int)bpm_value);
    ssd1306_clear_display();
    ssd1306_print(0, 2, "Latidos por minuto:");
    ssd1306_print(0, 4, str);
}

