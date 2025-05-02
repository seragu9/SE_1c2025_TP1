/** @file pulse_sensor.cpp
 *  @brief Módulo para la lectura del sensor de pulso HW827.
 *
 *  Este módulo captura y procesa la señal del sensor analógico HW827
 *  para medir la frecuencia cardíaca en BPM.
 */
 
 //=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "pulse_sensor.h"

#define TIME_INCREMENT_MS 10
#define SIZE_SAMPLE 4
#define rise_threshold 5



//=====[Declaration of external public global variables]=======================


float second = 0, third = 0;
static uint32_t pulse_counter = 0, last_beat_count = 0; // Contador de ciclos2


AnalogIn hw827(A0);


static void reset_counter();

/**
 * @brief Calcula los latidos por minuto (BPM) a partir de la señal analógica.
 *
 * @return Frecuencia cardíaca en BPM.
 */
float readBPM() {
    static float prev_value = 0.0;
    
    float bpm = 0;

    float reader = hw827.read() * 3.3;  // Convertir a tension (0 - 3.3V)

    // Umbral de detección de pulso
    float threshold = 1.65 + 0.012; // continua + variación de 12mV

    // Detectar el ascenso del pulso
    if (prev_value < threshold && reader >= threshold) {
        int count_diff = pulse_counter - last_beat_count;
        
        if (count_diff > 45) { // Filtrar latidos muy rápidos (300ms con 10ms por ciclo)
            bpm = (6000.0 / (count_diff*0.6 + second*0.4)); // 6000 ciclos de 10ms
            
            reset_counter(); // resetea contador si es necesario
            last_beat_count = pulse_counter;  // Guardar el ciclo en el que ocurrió el pulso
            third = second;
            second = count_diff;
        }
    }
    
    prev_value = reader;  // Actualizar valor anterior
    pulse_counter++;  // Incrementar contador en cada llamada
    return bpm;
}

/**
 * @brief Resetea el contador de ciclos si excede el límite definido.
 */

void reset_counter() {
    if (pulse_counter > 1e6) {
        pulse_counter = pulse_counter - last_beat_count;
    }
    
    
}
