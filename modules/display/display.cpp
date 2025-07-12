/** @file display.cpp
 *  @brief Módulo para control de display OLED SSD1306.
 *
 *  Este módulo controla la escritura del display.
 *  
 */
 
 //=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "font5x8.h"

#define SSD1306_I2C_ADDR 0x3C
#define SSD1306_CMD 0x00
#define SSD1306_DATA 0x40



//=====[Declaration of external public global variables]=======================


I2C i2c(D14, D15); // Pines SDA y SCL

static void ssd1306_draw_char(uint8_t x, uint8_t y, char c);
static void ssd1306_send_command(uint8_t cmd);
static void ssd1306_set_cursor(uint8_t x, uint8_t y);


static void ssd1306_send_command(uint8_t cmd) {
    char data[2] = {SSD1306_CMD, cmd};
    i2c.write(SSD1306_I2C_ADDR << 1, data, 2);
}

void ssd1306_init() {
    ssd1306_send_command(0xAE); // Apagar pantalla
    ssd1306_send_command(0xD5);
    ssd1306_send_command(0x80);
    ssd1306_send_command(0xA8);
    ssd1306_send_command(0x3F); // Ajustar multiplex según altura
    ssd1306_send_command(0xD3);
    ssd1306_send_command(0x00);
    ssd1306_send_command(0x40);
    ssd1306_send_command(0x8D);
    ssd1306_send_command(0x14); // Habilitar carga interna
    ssd1306_send_command(0x20);
    ssd1306_send_command(0x00);
    ssd1306_send_command(0xA1);
    ssd1306_send_command(0xC8);
    ssd1306_send_command(0xDA);
    ssd1306_send_command(0x12);
    ssd1306_send_command(0x81);
    ssd1306_send_command(0x7F);
    ssd1306_send_command(0xD9);
    ssd1306_send_command(0xF1);
    ssd1306_send_command(0xDB);
    ssd1306_send_command(0x40);
    ssd1306_send_command(0xA4);
    ssd1306_send_command(0xA6);
    ssd1306_send_command(0xAF); // Encender pantalla
}

void ssd1306_clear_display() {
    ssd1306_set_cursor(0, 0);  // Asegurar posición en la primera página
    for (int page = 0; page < 8; page++) { // Limpiar todas las páginas
        ssd1306_set_cursor(0, page);
        char clear_data[129] = {SSD1306_DATA}; // 128 bytes de datos + byte de control
        memset(&clear_data[1], 0x00, 128); // Llenar con ceros
        i2c.write(SSD1306_I2C_ADDR << 1, clear_data, sizeof(clear_data));
    }
}

void ssd1306_clear_display_middle() {
    for (int page = 2; page <= 5; page++) {  // Saltear páginas 0,1 y 6,7
        ssd1306_set_cursor(0, page);

        char clear_data[129] = {SSD1306_DATA};  // Byte de control + 128 bytes de datos
        memset(&clear_data[1], 0x00, 128);      // Limpiar con ceros

        i2c.write(SSD1306_I2C_ADDR << 1, clear_data, sizeof(clear_data));
    }
}

void ssd1306_clear_top_rows() {
    for (int page = 0; page <= 1; page++) {
        ssd1306_set_cursor(0, page);

        char clear_data[129] = {SSD1306_DATA};  // Byte de control + 128 bytes de datos
        memset(&clear_data[1], 0x00, 128);      // Llenar con ceros

        i2c.write(SSD1306_I2C_ADDR << 1, clear_data, sizeof(clear_data));
    }
}


static void ssd1306_draw_char(uint8_t x, uint8_t y, char c) {
    
    uint8_t index = c;
    ssd1306_set_cursor(x, y); // Fijar posición exacta antes de escribir

    char data[6] = {SSD1306_DATA}; // Primer byte indica que son datos
    for (int i = 0; i < 5; i++) {
        data[i + 1] = font5x8[index][i]; // Cargar datos de la fuente
    }

    i2c.write(SSD1306_I2C_ADDR << 1, data, sizeof(data));
}

void ssd1306_print(uint8_t x, uint8_t y, const char* text) {
    uint8_t max_chars = 21; // Límite de caracteres por fila
    uint8_t count = 0;

    while (*text) {
        ssd1306_draw_char(x, y, *text);
        x += 6; // Avanzar a la siguiente posición

        count++;
        if (count >= max_chars) { // Si llegamos al límite, pasamos a la siguiente línea
            count = 0;
            x = 0;   // Reiniciar la posición X
            y += 1;  // Ir a la siguiente línea
            if (y > 7) break; // No salir de la pantalla
        }

        text++;
    }
}

static void ssd1306_set_cursor(uint8_t x, uint8_t y) {
    ssd1306_send_command(0x21); // Configurar columna
    ssd1306_send_command(x);    // Inicio de columna
    ssd1306_send_command(127);  // Fin de columna

    ssd1306_send_command(0x22); // Configurar página
    ssd1306_send_command(y);    // Inicio de página
    ssd1306_send_command(7);    // Fin de página
}