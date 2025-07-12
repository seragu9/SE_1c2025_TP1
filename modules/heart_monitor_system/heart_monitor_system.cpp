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
#include "non_blocking_delay.h"
#include "data_history.h"
#include "wifi_com.h"

#define READ_INIT_MSG "Comenzando lectura...."
#define READ_FINISH_MSG "Lectura finalizada"
#define MAX_CHAR_MESSAGE 100
#define SET_TIME 		1751835446

//=====[Declaration and initialization of public global objects]===============

DigitalOut readingLed(LED1);

static nonBlockingDelay_t heartMonitorSystemDelay;
static nonBlockingDelay_t readSensorBPM;
//=====[Declaration and initialization of public global variables]=============


bool valueReady = 0;
bool readingState =0;

bool warnThreshold = false;
nonBlockingDelay_t warnTimer;
bool alertaActiva = false;

//static float bpm_value;

Ticker tickerMessageBPM;
bool messageReady = false; 

int low_limit, high_limit;
char tag_name[MAX_CHAR_TAG];

float bpm_value;
//=====[Declarations (prototypes) of functions]=========================

void inputsInit();
void outputsInit();

void buildMessage();
void tickActivateMessage();

void thresholdAlertUpdate(float bpm, int umbralBajo, int umbralAlto);
void displayMessageAlert();
/**
 * @brief Inicializa los parametros del sistema
 *
 */
void heartMonitorSystemInit(){

    tickInit();
    inputsInit();
    low_limit = DEFAULT_LOW_THRESHOLD;
    high_limit = DEFAULT_HIGH_THRESHOLD;
    sprintf(tag_name,"%s", DEFAULT_TAG);
    outputsInit();
    ssd1306_init();
    ssd1306_clear_display();
    ssd1306_print(0, 2, "   INICIANDO... ");
    //audioInit();
    wifiComInit();
    set_time(SET_TIME); // time
    tickerMessageBPM.attach( tickActivateMessage, 5000ms);
    nonBlockingDelayInit( &heartMonitorSystemDelay, TIME_INCREMENT_MS );
    nonBlockingDelayWrite(&readSensorBPM, 50);
}


/**
 * @brief Actualizacion del sistema
 *
 */
void heartMonitorSystemUpdate(){
    
    if( nonBlockingDelayRead(&heartMonitorSystemDelay) ) {
        if(debounceButtonUpdate()){
                readingState = !readingState;
                if (readingState){
                    sendUartMessage(READ_INIT_MSG);
                    ssd1306_clear_display_middle();
                    ssd1306_print(0, 2, READ_INIT_MSG);
                } else{
                    sendUartMessage(READ_FINISH_MSG);
                    ssd1306_clear_display_middle();
                    ssd1306_print(0, 2, READ_FINISH_MSG);
                }
        }
            
        if(readingState){
            readingLed = ON;
            if(nonBlockingDelayRead(&readSensorBPM)){
                readBPM();
				nonBlockingDelayWrite(&readSensorBPM,50);
            } 
             
            if(messageReady){
                bpm_value = getBPM();//
                buildMessage(); // Ejecuta solo si el flag está activo
                messageReady = false; // Resetear el flag después de ejecutar
            }
        } else{
            readingLed = 0;
        }
        displayMessageAlert();
    }
    wifiComUpdate();
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

    thresholdAlertUpdate(bpm_value, low_limit, high_limit);
    sprintf(str,"Latidos por minuto: %d", (int)bpm_value);
    sendUartMessage(str);
    // enviar a display
    sprintf(str,"          %d", (int)bpm_value);
    ssd1306_clear_display_middle();
    ssd1306_print(0, 2, "Latidos por minuto:");
    ssd1306_print(0, 4, str);
    addRegisterData((int) bpm_value, tag_name);
}

void displayMessageAlert(){
    if (alertaActiva){
        ssd1306_print(0, 0, " ALERTA VALOR CRITICO !");
    } else {
        ssd1306_clear_top_rows();
    }
}
void thresholdAlertUpdate(float bpm, int umbralBajo, int umbralAlto) {
    
    if (bpm==0) return;

    if (!alertaActiva && (bpm < umbralBajo || bpm > umbralAlto)) {
        alertaActiva = true;
        warnThreshold = true;
        ssd1306_print(0, 0, " ALERTA VALOR CRITICO !");
        nonBlockingDelayInit(&warnTimer, TIME_ALARM);  // 
    }

    
    if (alertaActiva && nonBlockingDelayRead(&warnTimer)) {
        alertaActiva = false;
        warnThreshold = false;
        ssd1306_clear_top_rows();
    }
}
