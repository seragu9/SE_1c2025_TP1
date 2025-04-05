/**
 * @file    main.cpp
 * @brief   Sistema de monitoreo de frecuencia cardíaca utilizando el sensor KY-039.
 * @details Este programa detecta picos en la señal del sensor KY-039 para 
 *          calcular los latidos por minuto y mostrar los valores en tiempo
 *          real a través de un puerto UART. Además, utiliza un botón para
 *          activar o desactivar la medición y un LED indicador para mostrar el
 *          estado del sistema.
 * 
 * @author  Sergio Aguirre
 * @date    4 de Abril de 2025
 * @version 1.0
 * 
 * @section dependencies Librerías Requeridas
 * - mbed.h: Librería base para el desarrollo con Mbed.
 * - arm_book_lib.h: Librería auxiliar.
 * - string.h: Librería estándar para manipulación de strings.
 * 
 * @section hardware Hardware Requerido
 * - Sensor KY-039 conectado al pin A0.
 * - Botón conectado al pin definido como BUTTON1.
 * - LED conectado al pin definido como LED1.
 * - Conexión UART para comunicación serie.
 * 
 * @section notes Notas Importantes
 * - Este programa utiliza un promedio móvil para suavizar las lecturas del sensor.
 * - Los BPM se calculan con un promedio ponderado basado en los últimos tres latidos detectados.
 * - Para personalizar umbrales o intervalos de tiempo, ajustar las constantes definidas.
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

DigitalOut readingLed(LED1);  ///< LED indicador de lectura activa
DigitalIn button(BUTTON1);    ///< Pulsador para iniciar/detener lecturas
AnalogIn ky039(A0);            ///< Entrada analógica del sensor KY-039

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);


//=====[Declaration and initialization of public global variables]=============

float reads[SIZE_SAMPLE] = {0};    ///< Lecturas del sensor para promedio móvil
float sum = 0, last = 0, first = 0, second = 0, third = 0, before = 0, print_value = 0; ///< Contadores y punteros
bool rising = false;             ///< Indicador de detección de pico
int rise_count = 0, ptr = 0, last_beat_counter = 0;    ///< Contadores
uint32_t cycle_count = 0; // Contador de ciclos


bool valueReady = 0;             ///< Bandera para nuevo valor disponible
bool readingState = 0;           ///< Estado de lectura activa

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void reset_counter();
void readBPM();
void buildMessage();
void sendUartMessage(char * tosend);



//=====[Main function, the program entry point after power on or reset]========
/** 
 * @brief Función principal que coordina la inicialización y el bucle principal.
 * - Detecta el cambio de estado del botón.
 * - Activa/desactiva el LED y las lecturas del sensor.
 * - Llama a las funciones de cálculo y comunicación.
 */
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

/** 
 * @brief Inicializa las entradas del sistema.
 * - Configura el botón con resistencia PullDown.
 */
void inputsInit() {
    button.mode(PullDown);
}

/** 
 * @brief Inicializa las salidas del sistema.
 * - Apaga el LED indicador.
 */
void outputsInit() {
    readingLed = OFF;
}

/** 
 * @brief Realiza la lectura del sensor KY-039 y calcula los BPM.
 * - Implementa una ventana de promedios móviles.
 * - Detecta picos y calcula los BPM usando un promedio ponderado.
 */
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

/** 
 * @brief Construye y envía un mensaje UART con el valor de BPM.
 */
void buildMessage() {
    //  enviar el mensaje por UART
    char str[100];
    
    if(valueReady){
            sprintf(str,"Latidos por minuto: %.2f", print_value);
            sendUartMessage(str);
            valueReady = false;
        }
}

/** 
 * @brief Envía un mensaje a través de UART.
 * @param tosend Mensaje a enviar.
 */
void sendUartMessage(char * tosend) {
    //  enviar el mensaje init por UART
    char str[100];
    int stringLength;

    sprintf(str,"%s\n", tosend);
    stringLength = strlen(str);
    uartUsb.write(str, stringLength);
}

/** 
 * @brief Resetea el contador de ciclos si es necesario.
 */
void reset_counter() {
    if (cycle_count > 1e6 || !readingState) {
        cycle_count = 0;
    }
}


