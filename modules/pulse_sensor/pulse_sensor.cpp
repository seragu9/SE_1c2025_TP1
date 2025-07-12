/** @file pulse_sensor_module.cpp
 *  @brief Módulo para la lectura del sensor de pulso HW827.
 *
 *  Este módulo captura y procesa la señal del sensor analógico HW827
 *  para medir la frecuencia cardíaca en BPM.
 */
 
 //=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "pulse_sensor.h"
#include "heart_monitor_system.h"

#define SIZE_SAMPLE 4
#define rise_threshold 5



//=====[Declaration of external public global variables]=======================


float bpm;
AnalogIn hw827(A0);


/**
 * @brief Calcula los latidos por minuto (BPM) a partir de la señal analógica.
 *
 * @return Frecuencia cardíaca en BPM.
 */
void readBPM() {

    float reader = hw827.read();
    // Filtro y estado
    static float señalFiltrada = 0.0f;
    static float promedio = 0.5f;
    static float deltaAnterior = 0.0f;

    // Tiempo
    static uint32_t tiempo = 0;
    static uint32_t ultimoLatido = 0;
    const uint32_t pasoMuestreo = 50;            // milisegundos por llamada
    const uint32_t tiempoInactividad = 3000;     // ms sin latido → BPM = 0
    tiempo += pasoMuestreo;

    // Intervalos y BPM
    static uint16_t intervalos[4] = {1000, 1000, 1000, 1000};
    static int idx = 0;
    //static float bpmSuavizado = 0.0f;

    // Parámetros
    const float alpha = 0.9f;
    const float beta  = 0.99f;
    const float umbralDelta = 0.01f;
    // Filtrado
    señalFiltrada = alpha * señalFiltrada + (1 - alpha) * reader;
    promedio = beta * promedio + (1 - beta) * señalFiltrada;
    float delta = señalFiltrada - promedio;

    
    static bool creciendo = false;
    static uint32_t intervalo = 0;
    if (delta > deltaAnterior) {
        creciendo = true;
    } else if (delta < deltaAnterior && creciendo && deltaAnterior > umbralDelta) {
        // Pico detectado
        creciendo = false;
        intervalo = tiempo - ultimoLatido;

		// filtrar picos rapidos con ruido
        if (intervalo >= 300 && intervalo <= 2000) {
            intervalos[idx] = intervalo;
            idx = (idx + 1) % 4;
            // Promedio de los últimos intervalos
            uint32_t suma = 0;
            for (int i = 0; i < 4; i++) suma += intervalos[i];
            uint32_t promIntervalo = suma / 4;
            int bpm_actual = 60000 / promIntervalo;// calculo BPM
            if(bpm) bpm = bpm_actual;
            bpm = 0.8f * bpm + 0.2f * bpm_actual;
        }

        ultimoLatido = tiempo;
    }

    deltaAnterior = delta;
}


float getBPM() {
    return bpm;
    }

