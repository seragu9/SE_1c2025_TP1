/*! @mainpage TP 3
 * @date Viernes, Junio 30, 2025
 * @author Sergio Aguirre
 * @section Sistema de monitoreo de frecuencia cardiaca
 *
 * 
 *
 */
//=====[Libraries]=============================================================
#include "mbed.h" 
#include "arm_book_lib.h"
#include "heart_monitor_system.h"

//=====[Defines]===============================================================


//=====[Declaration of public data types]======================================


//=====[Declaration and initialization of public global objects]===============


//=====[Declaration and initialization of public global variables]=============



//=====[Declarations (prototypes) of public functions]=========================


//=====[Main function, the program entry point after power on or reset]========

int main() {
    heartMonitorSystemInit();
    while (true) {
        heartMonitorSystemUpdate();
    }
}

