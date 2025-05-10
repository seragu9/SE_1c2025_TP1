/*! @mainpage TP 2
 * @date Viernes, Mayo 2, 2025
 * @author Sergio Aguirre
 * @section Sistema de monitoreo de frecuencia cardiaca
 *
 * 
 *
 */
//=====[Libraries]=============================================================
#include "mbed.h" 
#include "arm_book_lib.h"
#include "string.h"
#include "display.h"
#include "pulse_sensor.h"
#include "serial_com.h"
#include "button.h"

//=====[Defines]===============================================================


#define TIME_INCREMENT_MS 10
#define READ_INIT_MSG "Comenzando lectura...."
#define READ_FINISH_MSG "Lectura finalizada"



//=====[Declaration of public data types]======================================




//=====[Declaration and initialization of public global objects]===============

DigitalOut readingLed(LED1);




//=====[Declaration and initialization of public global variables]=============


bool valueReady = 0;
bool readingState =0;

float bpm;

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();

void buildMessage();


//=====[Main function, the program entry point after power on or reset]========

int main() {
    inputsInit();
    outputsInit();
    ssd1306_init();
    ssd1306_clear_display();
    ssd1306_print(0, 2, "   INICIANDO... ");
    while (true) {
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
            bpm = readBPM();
            
        } else{
            readingLed = 0;
        }
        if(bpm)
            buildMessage();
        delay(TIME_INCREMENT_MS);
    }
}



void inputsInit() {
    //button.mode(PullDown);
}

void outputsInit() {
    readingLed = OFF;
}



void buildMessage() {
    //  enviar el mensaje por UART
    char str[100];
    sprintf(str,"Latidos por minuto: %.0f", bpm);
    sendUartMessage(str);
    sprintf(str,"      %.0f", bpm);
    ssd1306_clear_display();
    ssd1306_print(0, 2, "Latidos por minuto:");
    ssd1306_print(0, 4, str);
}


