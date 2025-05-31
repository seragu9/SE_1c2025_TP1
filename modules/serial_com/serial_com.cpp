/** @file serial_com.cpp
 *  @brief Módulo para enviar mensajes por UART.
 *
 */
 
 
 //=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "serial_com.h"



//=====[Declaration of external public global variables]=======================


UnbufferedSerial uartUsb(USBTX, USBRX, 115200);


void sendUartMessage(const char * tosend) {
    //  enviar el mensaje init por UART
    char str[100];
    int stringLength;

    sprintf(str,"%s\n", tosend);
    stringLength = strlen(str);
    uartUsb.write(str, stringLength);
}
