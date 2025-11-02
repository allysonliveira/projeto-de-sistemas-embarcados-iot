#include "ssd1306.h"
#include "font.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

// Definições do I2C (TWI)
#define F_CPU 16000000UL // 16MHz (Clock do Uno)
#define F_SCL 100000UL   // 100kHz I2C Clock
#define TWI_ADDR 0x3D    // Endereço I2C do display

// Funções internas do I2C (baseadas nos registradores do Atmega328)
static void i2c_init(void) {
    // ATIVA OS PULL-UPS INTERNOS PARA I2C (PINOS A4 e A5)
    PORTC |= (1 << PC4) | (1 << PC5);

    TWSR = 0; // Prescaler
    TWBR = ((F_CPU / F_SCL) - 16) / 2; // Bit rate
}

static void i2c_start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

static void i2c_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

static void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

// Envia um comando para o display
static void ssd1306_cmd(uint8_t cmd) {
    i2c_start();
    i2c_write(TWI_ADDR << 1 | 0); // Endereço + Escrita (0)
    i2c_write(0x00); // Modo Comando
    i2c_write(cmd);
    i2c_stop();
}

// Envia um dado (pixel) para o display
static void ssd1306_data(uint8_t data) {
    i2c_start();
    i2c_write(TWI_ADDR << 1 | 0); // Endereço + Escrita (0)
    i2c_write(0x40); // Modo Dado
    i2c_write(data);
    i2c_stop();
}

// --- Funções Públicas ---

void ssd1306_init(void) {
    i2c_init();
    _delay_ms(100);

    ssd1306_cmd(0xAE); // Display OFF
    ssd1306_cmd(0xD5); // Set Display Clock Divide Ratio
    ssd1306_cmd(0x80);
    ssd1306_cmd(0xA8); // Set MUX Ratio
    ssd1306_cmd(0x3F); // 64 lines
    ssd1306_cmd(0xD3); // Set Display Offset
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x40); // Set Start Line
    ssd1306_cmd(0x8D); // Charge Pump
    ssd1306_cmd(0x14); // Enable Charge Pump
    ssd1306_cmd(0x20); // Memory Mode
    ssd1306_cmd(0x00); // Horizontal
    ssd1306_cmd(0xA1); // Seg Remap
    ssd1306_cmd(0xC8); // COM Scan Dec
    ssd1306_cmd(0xDA); // COM Pins
    ssd1306_cmd(0x12);
    ssd1306_cmd(0x81); // Contrast
    ssd1306_cmd(0xCF);
    ssd1306_cmd(0xD9); // Pre-charge
    ssd1306_cmd(0xF1);
    ssd1306_cmd(0xDB); // VCOMH Deselect
    ssd1306_cmd(0x40);
    ssd1306_cmd(0xA4); // Entire Display ON
    ssd1306_cmd(0xA6); // Normal Display
    ssd1306_cmd(0x2E); // Deactivate scroll
    ssd1306_cmd(0xAF); // Display ON

    ssd1306_clear();
}

void ssd1306_clear(void) {
    for (uint8_t y = 0; y < 8; y++) {
        ssd1306_cmd(0xB0 + y);
        ssd1306_cmd(0x00);
        ssd1306_cmd(0x10);
        for (uint8_t x = 0; x < 128; x++) {
            ssd1306_data(0x00);
        }
    }
    ssd1306_goto(0, 0);
}

void ssd1306_goto(uint8_t x_col, uint8_t y_page) {
    ssd1306_cmd(0xB0 + y_page);
    ssd1306_cmd(0x00 + (x_col & 0x0F));
    ssd1306_cmd(0x10 + (x_col >> 4));
}

// Desenha um caractere
static void ssd1306_char(char c) {
    for (uint8_t i = 0; i < 5; i++) {
        ssd1306_data(pgm_read_byte(&font[(c - 32) * 5 + i]));
    }
    ssd1306_data(0x00); // Espaçamento
}

void ssd1306_string(const char *str) {
    while (*str) {
        ssd1306_char(*str++);
    }
}

void ssd1306_string_xy(uint8_t x, uint8_t y, const char *str) {
    ssd1306_goto(x * 6, y); // Converte (coluna, linha) para (pixel, pagina)
    ssd1306_string(str);
}