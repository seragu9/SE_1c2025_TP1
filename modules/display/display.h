//=====[#include guards - begin]===============================================

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//extern const uint8_t font5x8[][5];

//=====[Declarations (prototypes) of public functions]=========================


void ssd1306_init();
void ssd1306_clear_display();
void ssd1306_print(uint8_t x, uint8_t y, const char* text);

//=====[#include guards - end]=================================================

#endif // _DISPLAY_H_