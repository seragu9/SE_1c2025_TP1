/** @file button.cpp
 *  @brief Módulo para la lectura del boton 1.
 *
 *  Este módulo controla estados sobre el boton 1.
 *  
 */
 
 //=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "button.h"


#define DEBOUNCE_BUTTON_TIME_MS                 40
//=====[Declaration of external public global variables]=======================


DigitalIn button(BUTTON1);


typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

int accumulatedDebounceButtonTime     = 0;
int numberOfEnterButtonReleasedEvents = 0;

buttonState_t enterButtonState;


void debounceButtonInit()
{
    if( button == 1) {
        enterButtonState = BUTTON_UP;
    } else {
        enterButtonState = BUTTON_DOWN;
    }
}

bool debounceButtonUpdate()
{
    bool enterButtonReleasedEvent = false;
    switch( enterButtonState ) {

    case BUTTON_UP:
        if( button ) {
            enterButtonState = BUTTON_FALLING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_FALLING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( button ) {
                enterButtonState = BUTTON_DOWN;
            } else {
                enterButtonState = BUTTON_UP;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !button ) {
            enterButtonState = BUTTON_RISING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_RISING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( !button ) {
                enterButtonState = BUTTON_UP;
                enterButtonReleasedEvent = true;
            } else {
                enterButtonState = BUTTON_DOWN;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    default:
        debounceButtonInit();
        break;
    }
    return enterButtonReleasedEvent;
}
