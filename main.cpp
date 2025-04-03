/*! @mainpage TP 1
 * @date Viernes, Abril 4, 2025
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

//=====[Defines]===============================================================

#define SIZE_SAMPLE 4
#define rise_threshold 5
#define TIME_INCREMENT_MS 10
#define READ_INIT_MSG "Comenzando lectura...."
#define READ_FINISH_MSG "Lectura finalizada"

//=====[Declaration and initialization of public global objects]===============

DigitalOut readingLed(LED1);
DigitalIn button(BUTTON1);
AnalogIn ky039(A0);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);


//=====[Declaration and initialization of public global variables]=============

float reads[SIZE_SAMPLE] = {0};
float sum = 0, last = 0, first = 0, second = 0, third = 0, before = 0, print_value = 0;
bool rising = false;
int rise_count = 0, ptr = 0, last_beat_counter = 0;
uint32_t cycle_count = 0; // Contador de ciclos

bool valueReady = 0;
bool readingState =0;


//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void reset_counter();
void readBPM();
void buildMessage();
void sendUartMessage(char * tosend);



//=====[Main function, the program entry point after power on or reset]========

int main() {
    inputsInit();
    outputsInit();
    
    while (1) {
        
        if(button){
            readingState = !readingState;
            if (readingState){
                sendUartMessage(READ_INIT_MSG);
            } else{
                sendUartMessage(READ_FINISH_MSG);
            }
        }
        
        if(readingState){
            readingLed = ON;
            readBPM();
            
        } else{
            readingLed = 0;
        }
        reset_counter();
        buildMessage();
        delay(TIME_INCREMENT_MS);
    }
}


void inputsInit() {
    button.mode(PullDown);
}

void outputsInit() {
    readingLed = OFF;
}

void readBPM() {
    float reader = 0;
    
    reader = ky039.read();
    // Mantener la ventana de promedios móviles
    sum -= reads[ptr];
    sum += reader;
    reads[ptr] = reader;
    last = sum / SIZE_SAMPLE; // Calcula el promedio
    
    if (last >= before) {
        rise_count++;
        // incrementos consecutivos para considerar un pico
        if (!rising && rise_count > rise_threshold) {
            rising = true;
            first = (cycle_count - last_beat_counter) * TIME_INCREMENT_MS;
            //previous_beat_counter = last_beat_counter;
            last_beat_counter = cycle_count;
            // Cálculo de BPM con promedio ponderado
            print_value = 60000.0 / (0.4 * first + 0.3 * second + 0.3 * third);
            valueReady = true;
            
            third = second;
            second = first;
        }
    } else {
        rising = false;
        rise_count = 0;
    }
    before = last;
    ptr = (ptr + 1) % SIZE_SAMPLE; // se mantiene de 1 a 4
    cycle_count++; // Contador de ciclos
}

void buildMessage() {
    //  enviar el mensaje por UART
    char str[100];
    
    if(valueReady){
            sprintf(str,"Latidos por minuto: %.2f", print_value);
            sendUartMessage(str);
            valueReady = false;
        }
}

void sendUartMessage(char * tosend) {
    //  enviar el mensaje init por UART
    char str[100];
    int stringLength;

    sprintf(str,"%s\n", tosend);
    stringLength = strlen(str);
    uartUsb.write(str, stringLength);
}

void reset_counter() {
    if (cycle_count > 1e6 || !readingState) {
        cycle_count = 0;
    }
}


