/** @file data_history.cpp
 *  @brief Módulo para guardar datos historicos
 *
 *  Este módulo guarda los datos sensados de pulso cardiaco.
 *  
 */

 //=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "data_history.h"
#include <stdio.h>
#include <string.h>

#define HTML_BUFFER         2048


//=====[Declaration of external public global variables]=======================




// Función para agregar registro
void addRegisterData(float bpm, const char* tag) {
    time_t now = time(NULL);           // requiere <time.h>
    struct tm* t = localtime(&now);    // toma del RTC

    snprintf(registers[historialIndex].datetime, sizeof(registers[historialIndex].datetime),
             "%04d-%02d-%02d %02d:%02d",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min);

    registers[historialIndex].bpm = bpm;
    strncpy(registers[historialIndex].tag, tag, sizeof(registers[historialIndex].tag));
    registers[historialIndex].tag[sizeof(registers[historialIndex].tag)-1] = '\0';

    historialIndex = (historialIndex + 1) % MAX_REG;
}





