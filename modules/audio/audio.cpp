/** @file audio.cpp
 *  @brief Módulo para reproductor de audio con PWM.
 *
 *  Este módulo controla el PWM para reproducir un 
 *  mensaje inicial de audio.
 *  
 */

 //=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "audio.h"
#include "message_init.h"

#define AUDIO_SAMPLE_DURATION           125

//=====[Declaration of external public global variables]=======================


PwmOut audioOut(PA_5);


//=====[Declarations (prototypes) of public functions]=========================



static void messageInit();

static void finishAudio();

//=====[Implementations of public functions]===================================


void audioInit()
{
    messageInit(); 
    finishAudio();
}



static void messageInit()
{
    float audioDutyCycle = 0.0;

    audioOut.period(0.000025f);

    int i = 0;
    for(i=1; i<messageLength; i++){
        audioDutyCycle = (float) messageData[i]/255;
        audioOut.write(audioDutyCycle);
        wait_us(AUDIO_SAMPLE_DURATION);
    }

}


static void finishAudio(){

    audioOut.write(0.0f); // Apaga la salida PWM
}